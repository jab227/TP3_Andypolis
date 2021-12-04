#ifndef EDIFICIOS_NOPRODUCTOR_H_
#define EDIFICIOS_NOPRODUCTOR_H_

#include "Edificio.h"

class No_Productor: public Edificio{
public:
	//PRE: -
	//POST: se construye un edificio que no produce nada
	No_Productor();

	//PRE: -
	//POST: se construye un edificio con los datos ingresados que no produce nada
	No_Productor(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario);

	//PRE: -
	//POST: dado que no es un productor devuelve un material vacio
	Material producir_material();

	//PRE: -
	//POST: retorna "ninguno".
	std::string info_producto() const override;
};

#endif /* EDIFICIOS_NOPRODUCTOR_H_ */
