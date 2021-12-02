#ifndef EDIFICIOS_FABRICA_H_
#define EDIFICIOS_FABRICA_H_

#include <iostream>
#include "../Productor.h"

class Fabrica : public Productor{
public:
	//PRE: -
	//POST: se construye una fabrica vacia
	Fabrica(std::size_t propietario);

	//PRE: -
	//POST: se construye una fabrica con los datos ingresados
	Fabrica(int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();

};

#endif /* EDIFICIOS_FABRICA_H_ */
