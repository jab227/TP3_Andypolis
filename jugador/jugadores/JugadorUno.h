#ifndef JUGADOR_JUGADORES_JUGADORUNO_H_
#define JUGADOR_JUGADORES_JUGADORUNO_H_

#include "../Jugador.h"

class Jugador_Uno final : public Jugador{
public:
	Jugador_Uno(Almacen *inventario, Lista<Coordenada*>* edificios);
	~Jugador_Uno();
	bool mover(const Coordenada& coordenada, const Mapa& mapa) override;
};

#endif /* JUGADOR_JUGADORES_JUGADORUNO_H_ */
