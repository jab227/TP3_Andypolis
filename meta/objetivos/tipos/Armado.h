#ifndef OBJETIVOS_TIPOS_ARMADO_H_
#define OBJETIVOS_TIPOS_ARMADO_H_

#include "../Objetivo.h"

class Armado : public Objetivo{
	public:
		// Pre: jugador != nullptr
		// Pos: Construye el objetivo Armado.
		Armado(Jugador* jugador);
		// Pre:  -
    	// Pos: se actualiza el objetivo, True si esta
		// cumplido, false en otro caso.
		bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_ARMADO_H_ */
