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
	Escuela(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos);

	//PRE: -
	//POST: imprime un saludo por terminal
	void saludar();
		
	//PRE: -
	//POST: Devuelve NO_REPARABLE
	Resultado_Chequeos reparar() override;

};

#endif /* EDIFICIOS_ESCUELA_H_ */
