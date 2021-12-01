#ifndef EDIFICIOS_MINAORO_H_
#define EDIFICIOS_MINAORO_H_

#include "./Productor.h"

class Mina_Oro : public Productor{
public:
	//PRE: -
	//POST: se construye una mina vacio
	Mina_Oro();

	//PRE: -
	//POST: se construye una mina con los datos ingresados aserradero vacio
	Mina_Oro(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};

#endif /* EDIFICIOS_MINAORO_H_ */
