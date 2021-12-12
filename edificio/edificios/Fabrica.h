#ifndef EDIFICIOS_FABRICA_H_
#define EDIFICIOS_FABRICA_H_

#include <iostream>
#include "../Productor.h"

class Fabrica : public Productor{
public:
	//PRE: -
	//POST: se construye una fabrica vacia
	Fabrica();

	//PRE: -
	//POST: se construye una fabrica con los datos ingresados
	Fabrica(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();

	//PRE: -
	//POST: Devuelve NO_REPARABLE en caso de que vida = MAX_VIDA. Devuelve REPARABLE y suma 1 de vida.en caso contrario.
	Resultado_Chequeos reparar(bool reparar_edificio = true) override;

};

#endif /* EDIFICIOS_FABRICA_H_ */
