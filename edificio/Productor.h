#ifndef EDIFICIOS_PRODUCTOR_H_
#define EDIFICIOS_PRODUCTOR_H_

#include "../edificio/Edificio.h"

class Productor: public Edificio{
private:
	Material producto;
public:
	//PRE: -
	//POST: se construye un edificio productor vacio
	Productor();

	//PRE: -
	//POST: se construye un edificio productor con los datos ingresados
	Productor(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, Material producto);


	//PRE: -
	//POST: devuelve el material que produce este edificio
	Material producir_material();

	//PRE: -
	//POST: Retorna el nombre y la cantidad del producto en un string.
	std::string info_producto() const override;
};

#endif /* EDIFICIOS_PRODUCTOR_H_ */
