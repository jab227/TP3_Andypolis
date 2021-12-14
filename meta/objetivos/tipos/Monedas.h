#ifndef OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_
#define OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_

#include "../Objetivo.h"

class Monedas : public Objetivo{
private:
	std::size_t monedas_juntadas;
	std::size_t monedas_actuales;
public:
	// Pre: jugador != nullptr
	// Pos: Construye el objetivo Monedas.
	Monedas(Jugador* jugador);
	// Pre:  -
    // Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_MONEDAS_H_ */
