#ifndef EDIFICIOS_PLANTAELECTRICA_H_
#define EDIFICIOS_PLANTAELECTRICA_H_

#include "../Productor.h"

class Planta_Electrica : public Productor{
public:
	//PRE: -
	//POST: se construye una planta electrica vacia
	Planta_Electrica(std::size_t propietario);

	//PRE: -
	//POST: se construye una planta electrica con los datos ingresados
	Planta_Electrica(int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};

#endif /* EDIFICIOS_PLANTAELECTRICA_H_ */
