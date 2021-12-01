#ifndef EDIFICIOS_PLANTAELECTRICA_H_
#define EDIFICIOS_PLANTAELECTRICA_H_

#include "../NoProductor.h"

class Planta_Electrica : public No_Productor{
public:
	//PRE: -
	//POST: se construye una planta electrica vacia
	Planta_Electrica();

	//PRE: -
	//POST: se construye una planta electrica con los datos ingresados
	Planta_Electrica(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};

#endif /* EDIFICIOS_PLANTAELECTRICA_H_ */
