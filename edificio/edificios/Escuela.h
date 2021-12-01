#ifndef EDIFICIOS_ESCUELA_H_
#define EDIFICIOS_ESCUELA_H_

#include "../Productor.h"

class Escuela : public Productor{
public:
	//PRE: -
	//POST: se construye una escuela vacia
	Escuela();

	//PRE: -
	//POST: se construye una escuela con los datos ingresados
	Escuela(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un saludo por terminal
	void saludar();
};

#endif /* EDIFICIOS_ESCUELA_H_ */
