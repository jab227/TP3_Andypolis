#ifndef OBJETIVO_H_
#define OBJETIVO_H_

#include "../jugador/Jugador.h"

class Objetivo {
//Atributos
private:
	std::string titulo;

protected:
	bool cumplido;
	Jugador* jugador;

public:
	Objetivo(std::string titulo, Jugador* jugador);

	virtual ~Objetivo(){ delete jugador;};

	bool esta_cumplido();

	virtual bool actualizar() = 0;
};

#endif /* OBJETIVO_H_ */
