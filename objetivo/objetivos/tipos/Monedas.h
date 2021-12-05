#ifndef OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_
#define OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_

#include "../Objetivo.h"

class Monedas : public Objetivo{
private:
	int monedas_juntadas;
	int monedas_actual;
public:
	Monedas(Jugador* jugador);
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_ */
