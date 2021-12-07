#ifndef OBJETIVOS_TIPOS_MINERO_H_
#define OBJETIVOS_TIPOS_MINERO_H_

#include "../Objetivo.h"

class Minero : public Objetivo{
public:
	Minero(Jugador* jugador);
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_MINERO_H_ */
