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
	Mina(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos);

	//PRE: -
	//POST: imprime un mensaje por consola
	void saludar();
	Resultado_Chequeos reparar() override;
};

#endif /* EDIFICIOS_MINA_H_ */
