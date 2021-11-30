#ifndef EDIFICIOS_OBELISCO_H_
#define EDIFICIOS_OBELISCO_H_

#include "NoProductor.h"

class Obelisco : public No_Productor{
public:
	//PRE: -
	//POST: se construye un obelisco vacio
	Obelisco();

	//PRE: -
	//POST: se construye un obelisco con los datos ingresados
	Obelisco(int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};
#endif /* EDIFICIOS_OBELISCO_H_ */
