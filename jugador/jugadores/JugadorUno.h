#ifndef JUGADOR_JUGADORES_JUGADORUNO_H_
#define JUGADOR_JUGADORES_JUGADORUNO_H_

#include "../Jugador.h"

class Jugador_Uno : public Jugador{
public:
	Jugador_Uno(Almacen *inventario);
	~Jugador_Uno();
	bool mover(const Coordenada& coordenada, const Mapa& mapa);
};

#endif /* JUGADOR_JUGADORES_JUGADORUNO_H_ */
