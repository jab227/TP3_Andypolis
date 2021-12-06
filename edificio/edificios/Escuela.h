#ifndef EDIFICIOS_ESCUELA_H_
#define EDIFICIOS_ESCUELA_H_

#include "../Productor.h"

class Escuela : public Productor{
public:
	//PRE: -
	//POST: se construye una escuela vacia
	Escuela(std::size_t propietario);

	//PRE: -
	//POST: se construye una escuela con los datos ingresados
	Escuela(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos);

	//PRE: -
	//POST: imprime un saludo por terminal
	void saludar();
};

#endif /* EDIFICIOS_ESCUELA_H_ */
