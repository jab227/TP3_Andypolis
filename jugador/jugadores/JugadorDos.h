#ifndef JUGADOR_JUGADORES_JUGADORDOS_H_
#define JUGADOR_JUGADORES_JUGADORDOS_H_

#include "../Jugador.h"

class Jugador_Dos final : public Jugador{
public:	
	Jugador_Dos(Almacen *inventario, Lista<Coordenada*>* edificios);
	Jugador_Dos(Almacen *inventario);
	~Jugador_Dos();
	bool mover(const Coordenada& coordenada, const Mapa& mapa) override;
};

#endif /* JUGADOR_JUGADORES_JUGADORDOS_H_ */
