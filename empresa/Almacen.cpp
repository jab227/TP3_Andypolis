#include "Almacen.h"

#include <fstream>
#include <iostream>

#include "../utils/LecturaArchivos.h"
#include "../printer/table_printer.h"

const int CANTIDAD_MATERIALES_DISTINTOS = 5, CANTIDAD_INICIAL = 0;
const std::size_t PRECIO_BOMBA = 100, BOMBAS_VACIAS = 0;

Almacen::Almacen() : lista_materiales_(Lista<Material>()) {}

Almacen::Almacen(const Lista<Material>& lista) : lista_materiales_(lista) {}

Lista<Material>& Almacen::obtener_materiales() {
	return lista_materiales_;
}

Material Almacen::obtener_material(std::string material) const {
	Material material_buscado = Material(material,0);
	std::size_t indice = buscar_material(material_buscado);
	if(indice)
		material_buscado = lista_materiales_.consulta(indice);
	// Como chequeo que no esta trabajando con una copia y no la ref? 
	return material_buscado;
}

//El material al tener un size_t no puede ser negativo. Entonces debemos usar los metodos restar y sumar.
void Almacen::restar_cantidad_material(const std::string& nombre,
				      std::size_t cantidad) {
	Material material(nombre, cantidad);
	std::size_t index = buscar_material(material);
	if (index) {
		lista_materiales_.consulta(index).restar_cantidad(
		    material.obtener_cantidad());
	}
}

void Almacen::sumar_cantidad_material(const std::string& nombre,
				      std::size_t cantidad) {
	Material material(nombre, cantidad);
	std::size_t index = buscar_material(material);
	if (index) {
		lista_materiales_.consulta(index).sumar_cantidad(
		    material.obtener_cantidad());
	}
}

void Almacen::mostrar_materiales() const{
	TablePrinter printer;
	Lista<std::string> cabecera;
	cabecera.alta_al_final("Material");
	cabecera.alta_al_final("Cantidad");
	printer.print_row(cabecera, std::cout);
	for(std::size_t i = 1; i <= lista_materiales_.consulta_largo(); i++)
		printer.print_row(lista_materiales_.consulta(i), std::cout);
}

Resultado_Chequeos Almacen::hay_lista_materiales(const Lista<Material> &materiales_consultados, std::size_t porcentaje) const{
	bool fin = false;
	Resultado_Chequeos suficiente = EXITO;
		for(std::size_t i = 1; i <= materiales_consultados.consulta_largo() && !fin; ++i){
			if (!hay_material_suficiente(materiales_consultados.consulta(i), porcentaje)) {
					suficiente = NO_MATERIALES;
					fin = true;
				}
		}
	return suficiente;
}

void Almacen::descontar_lista_materiales(const Lista<Material>& materiales_usados,
					 std::size_t porcentaje) {
	std::size_t proporcion = porcentaje / 100;
	for (std::size_t i = 1; i <= materiales_usados.consulta_largo(); i++) {
		Material material = materiales_usados.consulta(i);
		restar_cantidad_material(
		    material.obtener_nombre(),
		    material.obtener_cantidad() * proporcion);
	}
}

void Almacen::sumar_lista_materiales(const Lista<Material>& materiales_obtenidos,
				     std::size_t porcentaje) {
	// TODO: Constantes.
	std::size_t proporcion = porcentaje / 100;
	for (std::size_t i = 1; i <= materiales_obtenidos.consulta_largo();
	     i++) {
		Material material = materiales_obtenidos.consulta(i);
		sumar_cantidad_material(
		    material.obtener_nombre(),
		    material.obtener_cantidad() * proporcion);
	}
}

Resultado_Chequeos Almacen::comprar_bombas(std::size_t cantidad_bombas) {
	Resultado_Chequeos resultado = NO_MATERIALES;
	Material andycoins  = obtener_material(NOMBRES_MATERIALES[ANDYCOINS]);
	std::size_t gasto = cantidad_bombas * PRECIO_BOMBA;
	if (gasto <= andycoins.obtener_cantidad()) {
		std::cout << "Compraste " << cantidad_bombas
		     << " bombas exitosamente." << std::endl;
		sumar_cantidad_material(NOMBRES_MATERIALES[BOMBAS], cantidad_bombas);
		restar_cantidad_material(NOMBRES_MATERIALES[ANDYCOINS], gasto);
		resultado = EXITO;
		Material bombas = obtener_material(NOMBRES_MATERIALES[BOMBAS]);
		std::cout << "Cantidad de bombas: "
			  << bombas.obtener_cantidad() << std::endl;
		std::cout << "Andycoins restantes: "
			  << andycoins.obtener_cantidad() << std::endl;
	}
	return resultado;
}

void Almacen::agregar_material(const Material& material) {
	lista_materiales_.alta_al_final(material);
}

std::size_t Almacen::buscar_material(const Material& material) const {
	bool encontrado = false;
	std::size_t indice;
	for (indice = 0; indice < lista_materiales_.consulta_largo() && !encontrado; indice++)
			encontrado = (lista_materiales_.consulta(indice + 1) == material);
		 
	return encontrado ? indice : NO_ENCONTRADO;
}

bool Almacen::hay_material_suficiente(const Material& material, std::size_t porcentaje) const{
	bool suficiente = false;
	std::size_t proporcion = porcentaje/100;
	std::size_t indice = buscar_material(material);
	if (indice) {
		suficiente =
		    (lista_materiales_.consulta(indice).obtener_cantidad() * proporcion >=
		    material.obtener_cantidad()) ;
	}
	return suficiente;
}