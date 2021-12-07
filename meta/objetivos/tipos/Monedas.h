#ifndef OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_
#define OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_

#include "../Objetivo.h"

class Monedas : public Objetivo{
private:
	std::size_t monedas_juntadas;
	std::size_t monedas_actuales;
public:
	Monedas(Jugador* jugador);
	~Monedas();
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_ */
