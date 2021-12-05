#ifndef JUGADOR_JUGADORES_JUGADORDOS_H_
#define JUGADOR_JUGADORES_JUGADORDOS_H_

#include "../Jugador.h"

class Jugador_Dos : public Jugador{
public:
	Jugador_Dos(Almacen *inventario);
	~Jugador_Dos();
	bool mover(const Coordenada& coordenada, const Mapa& mapa);
};

#endif /* JUGADOR_JUGADORES_JUGADORDOS_H_ */
