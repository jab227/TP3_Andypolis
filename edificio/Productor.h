#ifndef EDIFICIOS_PRODUCTOR_H_
#define EDIFICIOS_PRODUCTOR_H_

#include "../edificio/Edificio.h"

class Productor : public Edificio{
protected:
	Material producir;
public:
	//PRE: -
	//POST: se construye un edificio productor vacio
	Productor();

	//PRE: -
	//POST: se construye un edificio productor con los datos ingresados
	Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, Material producir);

	//PRE: -
	//POST: devuelve el material que produce este edificio
	Material producir_material();

	//PRE: -
	//POST: devuelve si el edificio es productor o no. en este caso devuelve siempre true.
	bool es_productor();
};
#endif /* EDIFICIOS_PRODUCTOR_H_ */
