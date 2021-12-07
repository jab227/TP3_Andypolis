#ifndef OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_
#define OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_

#include "../Objetivo.h"

class Piedras : public Objetivo{
public:
	Piedras(Jugador* jugador);
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_ */
