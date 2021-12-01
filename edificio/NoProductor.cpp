#include "NoProductor.h"

No_Productor::No_Productor() {
}

No_Productor::No_Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos):
	Edificio(nombre, piedra, madera, metal, maximo_permitidos){
}

Material No_Productor::producir_material(){
	return Material();
}

string No_Productor::info_producto(){
	return "ninguno";
}

