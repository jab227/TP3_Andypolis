#ifndef EDIFICIOS_NOPRODUCTOR_H_
#define EDIFICIOS_NOPRODUCTOR_H_

#include "Edificio.h"

class No_Productor : public Edificio{
public:
	//PRE: -
	//POST: se construye un edificio que no produce nada
	No_Productor();

	//PRE: -
	//POST: se construye un edificio con los datos ingresados que no produce nada
	No_Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario);

	//PRE: -
	//POST: dado que no es un productor devuelve un material vacio
	Material producir_material();

	//PRE: -
	//POST: retorna "ninguno".
	string info_producto() override;
};

#endif /* EDIFICIOS_NOPRODUCTOR_H_ */
