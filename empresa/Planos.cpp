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
	Edificio* aux = lista_edificios[nombre];
	Planos::lista_edificios[nombre] = edificio_modificado;
	delete aux;
}

Edificio* Planos::buscar(std::string nombre_edificio){
	return lista_edificios[nombre_edificio];
}

std::size_t Planos::cantidad_permitida(const std::string& edificio){
	return lista_edificios[edificio]->obtener_max_permitidos();
}

Lista<std::string> Planos::edificios_disponibles(){
	return lista_edificios.claves();
}

std::string Planos::estado_actual_edificios(){
	Lista<std::string> claves = lista_edificios.claves();
	Edificio* edificio;
	std::string texto;
	for(std::size_t i = 1; i <= claves.consulta_largo(); i++){
		edificio = lista_edificios[claves.consulta(i)];
		texto += edificio -> a_string();
		if(i != claves.consulta_largo()) texto += "\n"; //Para evitar el salto de linea en la ult linea.
	}
	return texto;
}