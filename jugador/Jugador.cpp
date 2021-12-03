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

Almacen* Jugador::obtener_inventario(){
	return this -> inventario;
}

void Jugador::agregar_ubicacion(int fila, int columna){
	this -> ubicaciones_fila.alta_al_final(fila);
	this -> ubicaciones_columna.alta_al_final(columna);
}

int Jugador::obtener_largo_ubicaciones(){
	return this -> ubicaciones_fila.consulta_largo();
}

void Jugador::obtener_ubicacion(int ubicacion, int &fila, int &columna){
	fila = this -> ubicaciones_fila.consulta(ubicacion);
	columna = this -> ubicaciones_columna.consulta(ubicacion);
}

void Jugador::eliminar_ubicacion(int fila, int columna){
	for(int i = 1; i <= this -> ubicaciones_fila.consulta_largo(); i++)
		if(this -> ubicaciones_fila.consulta(i) == fila && this -> ubicaciones_columna.consulta(i) == columna){
			this -> ubicaciones_fila.baja(i);
			this -> ubicaciones_columna.baja(i);
		}
}

void Jugador::comprar_bombas(){
	std::size_t cantidad = this -> pedir_bombas_validas();
	if(this -> inventario -> comprar_bombas(cantidad) == EXITO){
		modificar_energia(-ENERGIA_COMPRAR_BOMBAS);
	}else{
		std::cout << "No se compraron bombas." << std::endl;
	}
}

std::size_t Jugador::pedir_bombas_validas(){
	string opcion;
	std::size_t bombas = 0;
	cout << "Cantidad de bombas:   " ;
	getline(cin, opcion);
	if(es_numero(opcion)){
		bombas = stoul(opcion);
	}
	return bombas;
}