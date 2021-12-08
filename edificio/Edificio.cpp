#include "Edificio.h"
#include <iostream>

Edificio::Edificio() {
	this->nombre = EDIFICIO_VACIO;
	this->materiales[0] = 0;
	this->materiales[1] = 0;
	this->materiales[2] = 0;
	this->maximo_permitidos = 0;
	this->construidos = 0;
	this->vida = 1; //Solo Mina y Fabrica poseen 2 de vida.
}

Edificio::Edificio(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos){
	this->nombre = nombre;
	this->materiales[PIEDRA] = piedra;
	this->materiales[MADERA] = madera;
	this->materiales[METAL] = metal;
	this->maximo_permitidos = maximo_permitidos;
	this->construidos = 0;
	this-> vida = 1;
}

//Constructor para Mina y Fabrica que tienen vida distinta.
Edificio::Edificio(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t vida){
	this->nombre = nombre;
	this->materiales[PIEDRA] = piedra;
	this->materiales[MADERA] = madera;
	this->materiales[METAL] = metal;
	this->maximo_permitidos = maximo_permitidos;
	this->construidos = 0;
	this-> vida = vida;
}

Edificio::~Edificio(){

}

std::string Edificio::obtener_nombre() const {
	return this->nombre;
}

std::size_t Edificio::obtener_cant_material(std::string material) const{
	std::size_t cantidad = 0, i = 0;
	bool fin = false;
	while(i < CANT_MATERIALES_EDIFICIOS && !fin){
		if(MATERIALES_EDIFICIOS[i] == material){
			cantidad = this->materiales[i];
			fin = true;
		}
		i++;
	}
	return cantidad;
}

std::size_t Edificio::obtener_max_permitidos() const{
	return this->maximo_permitidos;
}

//Q: se usa?
bool Edificio::vacio(){
	return this->nombre == EDIFICIO_VACIO;
}

//Q: Se usa? 
void Edificio::modificar_construidos(std::size_t n){
	if(n <= this->maximo_permitidos)
		this->construidos = n;
}
//Q: Se usa?
void Edificio::aumentar_construidos(){
	this->modificar_construidos(this -> construidos + 1);
}
//Q: Se usa?
void Edificio::disminuir_construidos(){
	this->modificar_construidos(this -> construidos - 1);	
}
//Q: Se usa?
std::size_t Edificio::obtener_construidos(){
	return this->construidos;
}

Edificio& Edificio::operator=(const Edificio &rhs){
	this->nombre = rhs.obtener_nombre();
	this->materiales[PIEDRA] = rhs.obtener_cant_material("piedra");
	this->materiales[MADERA] = rhs.obtener_cant_material("madera");
	this->materiales[METAL] = rhs.obtener_cant_material("metal");
	this->maximo_permitidos = rhs.maximo_permitidos;
	this->construidos = rhs.construidos;
	return *this;
}

Resultado_Chequeos Edificio::esta_maxima_capacidad(const std::size_t &construidos){
	Resultado_Chequeos resultado = EXITO;
	if(construidos >= this->maximo_permitidos) resultado = MAXIMA_CANTIDAD;
	return resultado;
}

bool Edificio::operator==(const Edificio &rhs){
	return this->nombre == rhs.obtener_nombre();
}

bool Edificio::operator!=(const Edificio &rhs){
	return this->nombre != rhs.obtener_nombre();
}

std::string Edificio::a_string(){
	//VER: devolver string con formato.
	//¿Necesario para imprimir cuando recorremos el diccionario?
	// Si tenemos la lista de claves, podriamos ahorrarnos imprmir dentro del diccionario.
	return "";
}

std::size_t Edificio::obtener_vida() const{
	return 	this -> vida;
}

void Edificio::recuperar_vida(){
	++(this -> vida);
}

Resultado_Chequeos Edificio::disminuir_vida(){
	Resultado_Chequeos resultado = DESTRUIDO;
	if(this->vida)	--(this->vida);
	if(this->vida) resultado = REPARABLE;
	return resultado;
}
