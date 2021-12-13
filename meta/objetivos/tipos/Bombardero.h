#ifndef OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_
#define OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_

#include "../Objetivo.h"

class Bombardero : public Objetivo{
private:
	std::size_t bombas_actuales;
	std::size_t bombas_usadas;
public:
	// Pre: jugador != nullptr
	// Pos: Construye el objetivo Bombardero.
	Bombardero(Jugador* jugador);
	// Pre:  -
    // Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_ */
