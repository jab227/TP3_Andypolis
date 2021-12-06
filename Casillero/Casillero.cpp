#include "Casillero.h"

const string VACIO = "";

Casillero::Casillero() {
	this -> color = VACIO;
}

Casillero::~Casillero() {}

Casillero::Casillero(std::string color){
	this -> color = color;
}

std::string Casillero::obtener_color(){
	return this -> color;
}

/*
std::string Casillero::obtener_contenido(){
	string contenido = VACIO;
	Edificio* edificio_contenido;
	Material* material_contenido;
	if(this -> esta_ocupado()){
		this -> obtener_contenido(edificio_contenido);
		this -> obtener_contenido(material_contenido);
	}
	if(edificio_contenido != nullptr)
		contenido = edificio_contenido -> obtener_nombre();
	else if(material_contenido != nullptr)
		contenido = material_contenido -> obtener_nombre();
	return contenido;
}
*/