#ifndef OBJETIVO_H_
#define OBJETIVO_H_

#include "../../jugador/Jugador.h"

class Objetivo {
//Atributos
protected:
	std::string titulo;
	Jugador* jugador;
	bool cumplido;
public:
	//PRE: el jugador debe estar bien cargado
	//POST: se crea un objetivo para el jugador
	Objetivo(std::string titulo, Jugador* jugador);

	//PRE: -
	//POST: se destruye el objetivo
	virtual ~Objetivo(); //{ delete jugador;} lo saque porque es el mismo jugador del programa

	//PRE: -
	//POST: devuelve si el objetivo esta cumplido o no
	bool esta_cumplido();

	//PRE: -
	//POST: se actualiza el objetivo y devuelve si esta cumplido o no.
	virtual bool actualizar() = 0;

	//PRE: -
	//POST: devuelve el titulo del objetivo
	std::string obtener_titulo();
};

#endif /* OBJETIVO_H_ */
