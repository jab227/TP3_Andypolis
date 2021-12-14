#ifndef OBJETIVOS_TIPOS_EXTREMISTA_H_
#define OBJETIVOS_TIPOS_EXTREMISTA_H_

#include "../Objetivo.h"

class Extremista : public Objetivo{
private:
	std::size_t bombas_actuales;
	std::size_t bombas_compradas;
public:
	// Pre: jugador != nullptr
	// Pos: Construye el objetivo Energetico.
	Extremista(Jugador* jugador);
	// Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_EXTREMISTA_H_ */
