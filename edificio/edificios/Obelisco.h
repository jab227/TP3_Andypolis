#ifndef EDIFICIOS_OBELISCO_H_
#define EDIFICIOS_OBELISCO_H_

#include "../NoProductor.h"

class Obelisco : public No_Productor{
public:
	//PRE: -
	//POST: se construye un obelisco vacio
	Obelisco(std::size_t propietario);

	//PRE: -
	//POST: se construye un obelisco con los datos ingresados
 
	Obelisco(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario);
 

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
};
#endif /* EDIFICIOS_OBELISCO_H_ */
