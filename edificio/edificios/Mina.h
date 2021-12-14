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
	
	//PRE: -
	//POST: Devuelve NO_REPARABLE en caso de que vida = MAX_VIDA. Devuelve REPARABLE y suma 1 de vida.en caso contrario.
	Resultado_Chequeos reparar(bool reparar_edificio = true) override;
};

#endif /* EDIFICIOS_MINA_H_ */
