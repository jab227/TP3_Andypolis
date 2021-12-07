#ifndef OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_
#define OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_

#include "../Objetivo.h"

class Energetico : public Objetivo{
public:
	Energetico(Jugador* jugador);
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_ */
