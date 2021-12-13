#ifndef OBJETIVOS_TIPOS_CANSADO_H_
#define OBJETIVOS_TIPOS_CANSADO_H_

#include "../Objetivo.h"

class Cansado : public Objetivo{
public:
	// Pre: jugador != nullptr
	// Pos: Construye el objetivo Cansado.
	Cansado(Jugador* jugador);
	// Destructor por defecto.
	~Cansado() = default;
	// Pre:  -
    // Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_CANSADO_H_ */
