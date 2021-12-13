#ifndef OBJETIVOS_TIPOS_LETRADO_H_
#define OBJETIVOS_TIPOS_LETRADO_H_

#include "../Objetivo.h"

class Letrado : public Objetivo{
	const Mapa* mapa;
	// Pre: -
	// Pos: True si el jugador construyo el maximo de escuelas;
	// False en otro caso
	bool estan_construidos(const Lista<Coordenada>& edificios);
public:
    // Pre: jugador != nullptr y mapa != nullptr
    // Pos: Construye el objetivo Letrado.
	Letrado(Jugador* jugador, Mapa* mapa);
	// Pre: -
    // Pos: se actualiza el objetivo, True si esta
	// cumplido, false en otro caso.
	bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_LETRADO_H_ */
