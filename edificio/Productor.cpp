#include "Productor.h"

Productor::Productor() {
}

Productor::Productor(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, Material producto, std::size_t propietario):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos, propietario){
	this->producto = producto;
}

Material Productor::producir_material(){
	return this->producto;
}

std::string Productor::info_producto() const{
	return to_string(this->producto.obtener_cantidad()) + " de " + this->producto.obtener_nombre();
}
