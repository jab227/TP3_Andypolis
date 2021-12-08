#include "Almacen.h"

#include <fstream>
#include <iostream>

#include "../utils/LecturaArchivos.h"

const int CANTIDAD_MATERIALES_DISTINTOS = 5, CANTIDAD_INICIAL = 0;
const std::size_t PRECIO_BOMBA = 100, BOMBAS_VACIAS = 0;

Almacen::Almacen() : lista_materiales_(Lista<Material>()) {}

Almacen::Almacen(const Lista<Material>& lista) : lista_materiales_(lista) {}

Almacen::~Almacen() {}

void Almacen::agregar_material(const Material& material) {
	lista_materiales_.alta_al_final(material);
}

std::size_t Almacen::buscar_material(const Material& material) const {
	bool encontrado = false;
	std::size_t indice;
	for (indice = 1;
	     indice <= lista_materiales_.consulta_largo() && !encontrado;
	     ++indice)
		encontrado = (lista_materiales_.consulta(indice) == material);

	return encontrado ? indice : NO_ENCONTRADO;
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
	cout << "Los materiales que hay son:" << endl;
	for (std::size_t i = 1; i <= lista_materiales_.consulta_largo(); i++) {
		cout << "- " << lista_materiales_.consulta(i).obtener_cantidad()
		     << " de " << lista_materiales_.consulta(i).obtener_nombre()
		     << endl;
	}
}

// TODO: Remover ahora esto no es responsabilidad del almacen
bool Almacen::guardar_materiales(const std::string& ruta) {
	ofstream archivo(ruta);
	bool salida = false;
	if (archivo.is_open()) {
		salida = true;
		for (std::size_t i = 1; i <= lista_materiales_.consulta_largo();
		     i++)
			archivo
			    << lista_materiales_.consulta(i).obtener_nombre()
			    << " "
			    << lista_materiales_.consulta(i).obtener_cantidad()
			    << endl;
	}
	archivo.close();
	return salida;
}

bool Almacen::hay_material_suficiente(const Material& material, std::size_t porcentaje) const{
	bool suficiente = false;
	std::size_t proporcion = porcentaje/100;
	std::size_t indice = buscar_material(material);
	if (indice) {
		suficiente =
		    lista_materiales_.consulta(indice).obtener_cantidad() * proporcion >=
		    material.obtener_cantidad() ;
	}
	return suficiente;
}

Resultado_Chequeos Almacen::hay_lista_materiales(const Lista<Material> &materiales_consultados, std::size_t porcentaje) const{
	bool fin = false;
	Resultado_Chequeos suficiente = EXITO;
	std::size_t i = 1;
	if(!this -> hay_material_suficiente(materiales_consultados.consulta(i), porcentaje)){
		for(std::size_t i = 1; i <= lista_materiales_.consulta_largo() && !fin; ++i){
		// Es necesario? No es mejor que hay_material_suficiente() devuelva un Resultado_Chequeos?
			if (!hay_material_suficiente(
				materiales_consultados.consulta(i), porcentaje)) {
				suficiente = NO_MATERIALES;
				fin = true;
				}
		}
	}
	return suficiente;
}

void Almacen::descontar_lista_materiales(const Lista<Material>& materiales_usados,
					 std::size_t porcentaje) {
	std::size_t proporcion = porcentaje / 100;
	for (std::size_t i = 1; i <= materiales_usados.consulta_largo(); i++) {
		Material material = materiales_usados.consulta(i);
		sumar_cantidad_material(
		    material.obtener_nombre(),
		    -material.obtener_cantidad() * proporcion);
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

// Se puede mejorar pero es lo mas comodo.
Resultado_Chequeos Almacen::comprar_bombas(std::size_t cantidad_bombas) {
	Resultado_Chequeos resultado = NO_MATERIALES;
	Material andycoins = Material(NOMBRES_MATERIALES[3], 0);
	buscar_material(andycoins);
	std::size_t gasto = cantidad_bombas * PRECIO_BOMBA;
	if (andycoins.obtener_cantidad() < gasto) {
		cout << "Compraste " << cantidad_bombas
		     << " bombas exitosamente." << endl;
		sumar_cantidad_material(NOMBRES_MATERIALES[4], cantidad_bombas);
		sumar_cantidad_material(NOMBRES_MATERIALES[3], -gasto);
		resultado = EXITO;
		Material bombas = Material(NOMBRES_MATERIALES[4], 0);
		buscar_material(bombas);  // Busca y devuelve por interfaz la
					  // cantidad de bombas.
		std::cout << "Cantidad de bombas: "
			  << andycoins.obtener_cantidad() << std::endl;
		std::cout << "Andycoins restantes: "
			  << bombas.obtener_cantidad() << std::endl;
	}
	return resultado;
}