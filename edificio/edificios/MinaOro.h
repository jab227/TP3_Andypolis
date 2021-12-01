#ifndef EDIFICIOS_MINA_ORO_H_
#define EDIFICIOS_MINA_ORO_H_

#include "../Productor.h"

class MinaOro : public Productor{
public:
	//PRE: -
	//POST: se construye una mina vacio
	MinaOro();

	//PRE: -
	//POST: se construye una mina con los datos ingresados aserradero vacio
	MinaOro(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};

#endif /* EDIFICIOS_MINA_ORO_H_ */
