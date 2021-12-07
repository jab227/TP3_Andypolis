#ifndef OBJETIVOS_TIPOS_CONSTRUCTOR_H_
#define OBJETIVOS_TIPOS_CONSTRUCTOR_H_

#include "../Objetivo.h"

class Constructor : public Objetivo{
public:
	Constructor(Jugador* jugador);
	~Constructor();
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_CONSTRUCTOR_H_ */
