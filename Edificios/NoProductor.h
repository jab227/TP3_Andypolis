#ifndef EDIFICIOS_NOPRODUCTOR_H_
#define EDIFICIOS_NOPRODUCTOR_H_

#include "../Edificio.h"

class No_Productor : public Edificio{
public:
	//PRE: -
	//POST: se construye un edificio que no produce nada
	No_Productor();

	//PRE: -
	//POST: se construye un edificio con los datos ingresados que no produce nada
	No_Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: devuelve si el edificio es productor o no. en este caso devuelve siempre false.
	bool es_productor();

	//PRE: -
	//POST: dado que no es un productor devuelve un material vacio
	Material producir_material();
};

#endif /* EDIFICIOS_NOPRODUCTOR_H_ */
