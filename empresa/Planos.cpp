#include "Planos.h"
#include "../printer/table_printer.h"
#include "../edificio/Productor.h"
#include "../utils/LecturaArchivos.h"
#include "../parser/parser_edificio.h"
#include <fstream>

Diccionario<std::string, Edificio*> Planos::lista_edificios = Diccionario<std::string, Edificio*>();

Planos::Planos() {
}
Planos::Planos(Diccionario<std::string, Edificio*> diccionario) {
	Planos::lista_edificios = diccionario;
}

Planos::~Planos() {
	Lista<std::string> claves = lista_edificios.claves();
	while(!claves.vacia())
		delete lista_edificios[claves.baja(1)];
}



//EMBELLECER.
void Planos::mostrar_edificios(){
	TablePrinter printer = TablePrinter();
	Lista<std::string> header;  //feo pero comodo jaja
	header.alta_al_final("Edificio");
	header.alta_al_final("Piedra");
	header.alta_al_final("Madera");
	header.alta_al_final("Metal");
	header.alta_al_final("Cantidad permitida");
	header.alta_al_final("Material producido");
	printer.print_row(header, std::cout);
	Lista<std::string> claves = lista_edificios.claves();
	for(std::size_t i = 1; i <= claves.consulta_largo(); i++){
		Edificio* consultado = this -> lista_edificios[claves.consulta(i)];
		printer.print_row(consultado, std::cout);
	}
}

//Q: Se usa?
//std::string Planos::material_producido( Edificio* edificio){
//	return edificio -> info_producto();
//}

Resultado_Chequeos Planos::chequeo_construir(const std::string &nombre_edificio,  Jugador* jugador,  Mapa* mapa){
	Resultado_Chequeos resultado = NO_EXISTE;
	Lista<Material> materiales = materiales_necesarios(nombre_edificio);
	resultado = jugador -> tiene_materiales(materiales);
	if(resultado != NO_MATERIALES){
		Edificio* ptr_edificio = this -> lista_edificios[nombre_edificio];
		std::size_t construidos = jugador -> cantidad_edificios(nombre_edificio, mapa);
		resultado = ptr_edificio -> esta_maxima_capacidad(construidos);
	}
	return resultado;
}

Resultado_Chequeos Planos::existe(std::string nombre_edificio){
	Resultado_Chequeos resultado = NO_EXISTE;
	if(lista_edificios.existe(nombre_edificio)) resultado = EXITO;
	return resultado;
}

//Al tener el constructor de copia de LIsta, sobrevive el puntero retornado.
Lista<Material> Planos::materiales_necesarios(std::string nombre_edificio){
	Lista<Material> lista_materiales;
	Edificio* edificio = Planos::buscar(nombre_edificio);
	//Chequear que no haya roto al cambiar alta() por alta_al_final().
	for(std::size_t i = 0; i < CANT_MATERIALES_EDIFICIOS; i++)
		lista_materiales.alta_al_final(Material(MATERIALES_EDIFICIOS[i], edificio -> obtener_cant_material(MATERIALES_EDIFICIOS[i])));
	return lista_materiales;
}


void Planos::modificar_edificio(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal){

	Edificio* edificio_modificado = traductor_edificios(nombre, piedra, madera, metal,
			 Planos::lista_edificios[nombre]->obtener_max_permitidos());
	Planos::lista_edificios[nombre] = edificio_modificado;
}


/* WHY: Borrables?
void Planos::aumentar_construidos_edificio(const Edificio* &edificio){
	bool encontrado = false;
	std::size_t i = 1;
	Edificio* buscado;
	while(!encontrado && i <= this -> lista_edificios.consulta_largo()){
		buscado = this -> lista_edificios.consulta(i);
		if(*(buscado) == *edificio){
			encontrado = true;
			buscado -> aumentar_construidos();
		}
		i++;
	}
}

void Planos::disminuir_construidos_edificio(const std::string &edificio){
	bool encontrado = false;
	std::size_t i = 1;
	Edificio* buscado;
	while(!encontrado && i <= this -> lista_edificios.consulta_largo()){
		 buscado = this -> lista_edificios.consulta(i);
		if(buscado -> obtener_nombre() == edificio){
			encontrado = true;
			buscado -> disminuir_construidos();
		}
		i++;
	}
}
*/

void Planos::mostrar_materiales_producidos(Lista<Material> listado){
	//Podria reemplazarse por simple while, pero como aviso cuando no hay edif productor?
	if(listado.consulta_largo() > 0){
		TablePrinter printer; //Podria ser estatico?
		Lista<std::string> cabecera;
		cabecera.alta_al_final("Material producido");
		cabecera.alta_al_final("Cantidad");
		printer.print_row(cabecera, std::cout);
		for(std::size_t i = 1; i <= listado.consulta_largo(); i++)
			printer.print_row(listado.consulta(i), std::cout);
	}else
		std::cout << "No hay edificios construidos que produzcan materiales.\n"
				"Construya alguno para empezar a producir!" << std::endl;
}

Edificio* Planos::buscar(std::string nombre_edificio){
	return lista_edificios[nombre_edificio];
}
