#include "Productor.h"

Productor::Productor() {
}

Productor::Productor(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, Material producto):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos){
	this->producto = producto;
}

Productor::Productor(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t vida, Material producto):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos, vida){
	this->producto = producto;
}


Material Productor::producir_material(){
	return this->producto;
}

std::string Productor::info_producto() const{
	return std::to_string(this->producto.obtener_cantidad()) + " de " + this->producto.obtener_nombre();
}
