#include "Jugador.h"

Jugador::Jugador(size_t jugador) {
	this -> jugador = jugador;
	this -> energia = 0;
	this -> inventario = new Almacen();
}

Jugador::~Jugador() {
	delete this -> inventario;
}

size_t Jugador::obtener_jugador(){
	return this -> jugador;
}

int Jugador::obtener_energia(){
	return this -> energia;
}

int Jugador::energia_suficiente(int energia_necesaria){
	return this -> energia - energia_necesaria;
}

int Jugador::modificar_energia(int valor){
	return this -> energia += valor;
}
