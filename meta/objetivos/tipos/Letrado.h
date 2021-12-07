#ifndef OBJETIVOS_TIPOS_LETRADO_H_
#define OBJETIVOS_TIPOS_LETRADO_H_

#include "../Objetivo.h"

class Letrado : public Objetivo{
public:
	Letrado(Jugador* jugador);
	~Letrado();
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_LETRADO_H_ */
