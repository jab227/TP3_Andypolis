#include "Productor.h"

Productor::Productor() {
}

Productor::Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, Material producto):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos){
	this->producto = producto;
}

Material Productor::producir_material(){
	return this->producto;
}

bool Productor::es_productor(){
	return true;
}

string Productor::info_producto(){
	return to_string(this->producto.obtener_cantidad()) + " de " + this->producto.obtener_nombre();
}
