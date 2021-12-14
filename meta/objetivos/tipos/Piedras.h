#ifndef OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_
#define OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_

#include "../Objetivo.h"

class Piedras : public Objetivo{
public:
	// Pre: jugador != nullptr
	// Pos: Construye el objetivo Monedas.
	Piedras(Jugador* jugador);
	// Pre:  - 
	// Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_PIEDRAS_H_ */
