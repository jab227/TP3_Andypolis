#ifndef OBJETIVOS_TIPOS_ARMADO_H_
#define OBJETIVOS_TIPOS_ARMADO_H_

#include "../Objetivo.h"

class Armado : public Objetivo{
public:
	Armado(Jugador* jugador);
	~Armado();
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_ARMADO_H_ */
