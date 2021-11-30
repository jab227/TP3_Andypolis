#include "Productor.h"

Productor::Productor() {
}

Productor::Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, Material producir):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos){
	this -> producir = producir;
}

Material Productor::producir_material(){
	return this -> producir;
}

bool Productor::es_productor(){
	return true;
}
