#ifndef OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_
#define OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_

#include "../Objetivo.h"

class Energetico : public Objetivo{
	public:
		// Pre: jugador != nullptr
		// Pos: Construye el objetivo Energetico.
		Energetico(Jugador* jugador);
		// Destructor por defecto.
		~Energetico() = default;
		// Pre:  -
    	// Pos: se actualiza el objetivo, True si esta
		// cumplido, false en otro caso.
		bool actualizar() override;
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_ENERGETICO_H_ */
