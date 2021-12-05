#ifndef OBJETIVO_OBJETIVOS_OBJETIVO_H_
#define OBJETIVO_OBJETIVOS_OBJETIVO_H_

#include "../../jugador/Jugador.h"

class Objetivo {
//Atributos
protected:
	bool cumplido;
	Jugador* jugador;
public:
	Objetivo(Jugador* jugador);

	virtual ~Objetivo() = 0;

	bool esta_cumplido();

	virtual bool actualizar() = 0;
};

#endif /* OBJETIVO_OBJETIVOS_OBJETIVO_H_ */
