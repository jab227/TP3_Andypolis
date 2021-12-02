#include "Productor.h"

Productor::Productor() {
}

Productor::Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, Material producto, std::size_t propietario):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos, propietario){
	this->producto = producto;
}

Material Productor::producir_material(){
	return this->producto;
}

string Productor::info_producto(){
	return to_string(this->producto.obtener_cantidad()) + " de " + this->producto.obtener_nombre();
}
