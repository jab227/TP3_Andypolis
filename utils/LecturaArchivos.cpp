#include "LecturaArchivos.h"

#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"
#include "../Casillero/casilleros/Betun.h"
#include "../Casillero/casilleros/Camino.h"
#include "../Casillero/casilleros/Muelle.h"
#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Fabrica.h"
#include "../edificio/edificios/Mina.h"
#include "../edificio/edificios/MinaOro.h"
#include "../edificio/edificios/Obelisco.h"
#include "../edificio/edificios/PlantaElectrica.h"

bool es_numero(std::string palabra){
	bool resultado = true;
	int i = 0;
	if(palabra.size() == 0)
		resultado = false;
	while (i < (int) palabra.length() && resultado){
		resultado = isdigit(palabra[i]);
		i++;
	}
	return resultado;
}


Edificio* traductor_edificios(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t max_permitidos){
	Edificio* edificio = nullptr;
	if(nombre == "mina")
		edificio = new Mina(piedra, madera, metal, max_permitidos);
	else if (nombre == "aserradero")
		edificio = new Aserradero(piedra, madera, metal, max_permitidos);
	else if(nombre == "fabrica")
		edificio = new Fabrica(piedra, madera, metal, max_permitidos);
	else if(nombre == "escuela")
		edificio = new Escuela(piedra, madera, metal, max_permitidos);
	else if(nombre == "obelisco")
		edificio = new Obelisco(piedra, madera, metal, max_permitidos);
	else if(nombre == "planta electrica")
		edificio = new Planta_Electrica(piedra, madera, metal, max_permitidos);
	else if(nombre == "mina oro")
		edificio = new Mina_Oro(piedra, madera, metal, max_permitidos);
	return edificio;
}

//Sobrecarga para evitar tener que poner toda la info para crear edificios.
Edificio* traductor_edificios(std::string nombre){
	Edificio* edificio = nullptr;
	if(nombre == "mina")
		edificio = new Mina();
	else if (nombre == "aserradero")
		edificio = new Aserradero();
	else if(nombre == "fabrica")
		edificio = new Fabrica();
	else if(nombre == "escuela")
		edificio = new Escuela();
	else if(nombre == "obelisco")
		edificio = new Obelisco();
	else if(nombre == "planta electrica")
		edificio = new Planta_Electrica();
	else if(nombre == "mina oro")
		edificio = new Mina_Oro();
	return edificio;
}


Casillero* traductor_casillero(char nombre) {
	Casillero* casillero;
	if (nombre == BETUN)
		casillero = new Betun();
	else if (nombre == CAMINO)
		casillero = new Camino();
	else if (nombre == LAGO)
		casillero = new Casillero_Inaccesible();
	else if (nombre == MUELLE)
		casillero = new Muelle();
	else if (nombre == TERRENO)
		casillero = new Casillero_Construible();
	return casillero;
}

Material* traductor_materiales(std::string nombre, std::size_t cantidad) {
	return new Material(nombre, cantidad);
}

/* 
//Borrar cuando el parser este adaptado
//PRE: -
//POST: parte la linea en el delimitador, devuelve la primera mitad por la salida y la segunda mitad
//se iguala a linea
string dividir_linea(string &linea, char delimitador){
	std::size_t pos = linea.find(delimitador);
	string dato = linea.substr(0, pos);
	linea.erase(0, pos+1);
	return dato;
}
//Borrar cuando el parser este adaptado
void cargar_fila_columna(std::string linea, std::size_t& filas,
			 std::size_t& columnas) {
	filas = stoi(dividir_linea(linea, ESPACIO));
	columnas = stoi(dividir_linea(linea, ESPACIO));
}
//Borrar cuando el parser este adaptado
string procesar_ubicacion(string linea, Coordenada& coordenada){
	string edificio = dividir_linea(linea, DELIMITADOR_UBICACION);
	edificio.erase(edificio.size()-1, 1); //Le saco el espcio final
	std::size_t fila = char_a_int(linea[0]);
	std::size_t columna = char_a_int(linea[3]);
	coordenada = Coordenada(fila, columna);
	return edificio;
}

//Borrar cuando el parser este adaptado
std::size_t char_a_int(char c){
	return (c - '0');
}

*/
