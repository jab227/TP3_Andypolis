#ifndef JUGADOR_JUGADORES_JUGADORUNO_H_
#define JUGADOR_JUGADORES_JUGADORUNO_H_

#include "../Jugador.h"

class Jugador_Uno : public Jugador{
public:
	Jugador_Uno(std::size_t id, Almacen *inventario);
	~Jugador_Uno();
};

#endif /* JUGADOR_JUGADORES_JUGADORUNO_H_ */
