#ifndef EDIFICIOS_MINA_H_
#define EDIFICIOS_MINA_H_

#include "../Productor.h"

class Mina : public Productor{
public:
	//PRE: -
	//POST: se construye una mina vacio
	Mina();

	//PRE: -
	//POST: se construye una mina con los datos ingresados aserradero vacio
	Mina(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};

#endif /* EDIFICIOS_MINA_H_ */
