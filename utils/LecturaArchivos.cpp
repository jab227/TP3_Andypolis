#include "LecturaArchivos.h"

#include <ctype.h>
#include "../edificio/edificios/Mina.h"
#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Fabrica.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Obelisco.h"
#include "../edificio/edificios/PlantaElectrica.h"
#include "../Casillero/CasilleroTransitable.h"
#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"

//PRE: -
//POST: parte la linea en el delimitador, devuelve la primera mitad por la salida y la segunda mitad
//se iguala a linea
string dividir_linea(string &linea, char delimitador);

//PRE: c debe ser el caracter correspondiente a un numero
//POST: devuelve el numero entero
std::size_t char_a_int(char c);

bool es_numero(std::string palabra){
	bool resultado = true;
	std::size_t i = 0;
	if(palabra.size() == 0)
		resultado = false;
	while (i < palabra.length() && resultado){
		resultado = isdigit(palabra[i]);
		i++;
	}
	return resultado;
}

string dividir_linea(string &linea, char delimitador){
	std::size_t pos = linea.find(delimitador);
	string dato = linea.substr(0, pos);
	linea.erase(0, pos+1);
	return dato;
}

Edificio* procesar_edificio(string linea){
	string nombre = dividir_linea(linea, ESPACIO);
	string dato_sig;
	while(!es_numero(dato_sig = dividir_linea(linea, ESPACIO))){
		nombre += ' ';
		nombre += dato_sig;
	}
	std::size_t materiales[CANT_MATERIALES_EDIFICIOS];
	materiales[0] = stoi(dato_sig);
	for (std::size_t j = 1; j < CANT_MATERIALES_EDIFICIOS; j++){
		materiales[j] = stoi(dividir_linea(linea, ESPACIO));
	}
	std::size_t max_permitidos = stoi(linea);
	return traductor_edificios(nombre, materiales[0], materiales[1], materiales[2], max_permitidos, NINGUNO);
}

Edificio* traductor_edificios(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t max_permitidos, std::size_t propietario){
	Edificio* edificio = nullptr;
	if(nombre == "mina")
		edificio = new Mina(piedra, madera, metal, max_permitidos, propietario);
	else if (nombre == "aserradero")
		edificio = new Aserradero(piedra, madera, metal, max_permitidos, propietario);
	else if(nombre == "fabrica")
		edificio = new Fabrica(piedra, madera, metal, max_permitidos, propietario);
	else if(nombre == "escuela")
		edificio = new Escuela(piedra, madera, metal, max_permitidos, propietario);
	else if(nombre == "obelisco")
		edificio = new Obelisco(piedra, madera, metal, max_permitidos, propietario);
	else if(nombre == "planta electrica")
		edificio = new Planta_Electrica(piedra, madera, metal, max_permitidos, propietario);
	return edificio;
}

Casillero* traductor_casillero(char nombre){
    Casillero* casillero;
    if(nombre == TRANSITABLE)
        casillero = new Casillero_Transitable();
    else if (nombre == INACCESIBLE)
        casillero = new Casillero_Inaccesible();
    else if(nombre == CONSTRUIBLE)
        casillero = new Casillero_Construible();
    return casillero;
}

Material* traductor_materiales(string nombre, std::size_t cantidad){
	return new Material(nombre, cantidad);
}

Material procesar_material(string linea){
	string nombre = dividir_linea(linea, ESPACIO);
	string dato_sig;
	while(!es_numero(dato_sig = dividir_linea(linea, ESPACIO))){
		nombre += ' ';
		nombre += dato_sig;
	}
	std::size_t cantidad = stoi(dato_sig);
	return Material(nombre, cantidad);
}

void cargar_fila_columna(string linea, std::size_t& filas, std::size_t& columnas){
	filas = stoi(dividir_linea(linea, ESPACIO));
	columnas = stoi(dividir_linea(linea, ESPACIO));
}

string procesar_ubicacion(string linea, std::size_t &fila, std::size_t &columna, size_t &propietario){
	string edificio = dividir_linea(linea, DELIMITADOR_UBICACION);
	edificio.erase(edificio.size()-1, 1); //Le saco el espcio final
	fila = char_a_int(linea[0]);
	columna = char_a_int(linea[3]);
	propietario = 1;					//Elegir bien el propietario
	return edificio;
}

std::size_t char_a_int(char c){
	return (c - '0');
}

string espaciado(string palabra, std::size_t largo){
	string espacio = "";
	std::size_t largo_final = palabra.size();
	while(largo_final < largo){
		espacio += "\t";
		largo_final += 7;
	}
	espacio += "|";
	return espacio;
}

