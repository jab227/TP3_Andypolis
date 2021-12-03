#include "NoProductor.h"

No_Productor::No_Productor() {
}

No_Productor::No_Productor(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos, propietario){
}

Material No_Productor::producir_material(){
	return Material();
}

string No_Productor::info_producto(){
	return "ninguno";
}

