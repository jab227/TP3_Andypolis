#ifndef EDIFICIOS_PRODUCTOR_H_
#define EDIFICIOS_PRODUCTOR_H_

#include "../edificio/Edificio.h"

class Productor : public Edificio{
private:
	Material producto;
public:
	//PRE: -
	//POST: se construye un edificio productor vacio
	Productor();

	//PRE: -
	//POST: se construye un edificio productor con los datos ingresados
	Productor(string nombre, int piedra, int madera, int metal, int maximo_permitidos, Material producto, std::size_t propietario);

	//PRE: -
	//POST: devuelve el material que produce este edificio
	Material producir_material();

	//PRE: -
	//POST: Retorna el nombre y la cantidad del producto en un string.
	string info_producto() override;
};

#endif /* EDIFICIOS_PRODUCTOR_H_ */
