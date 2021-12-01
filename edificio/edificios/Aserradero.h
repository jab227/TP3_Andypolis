#ifndef EDIFICIOS_ASERRADERO_H_
#define EDIFICIOS_ASERRADERO_H_

#include "../Productor.h"

class Aserradero : public Productor{
public:
	//PRE: -
	//POST: se construye un aserradero vacio
	Aserradero();

	//PRE: -
	//POST: se construye un aserradero con los datos ingresados
	Aserradero(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un saludo por consola
	void saludar();
};

#endif /* EDIFICIOS_ASERRADERO_H_ */
