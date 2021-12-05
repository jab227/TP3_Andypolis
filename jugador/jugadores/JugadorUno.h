#ifndef JUGADOR_JUGADORES_JUGADORUNO_H_
#define JUGADOR_JUGADORES_JUGADORUNO_H_

#include "../Jugador.h"

class Jugador_Uno final : public Jugador {
       private:
	static const std::size_t costo_camino = 4;
	static const std::size_t costo_betun = 0;
	static const std::size_t costo_lago = 2;
	static const std::size_t costo_muelle = 5;
	static const std::size_t costo_terreno = 25;

       public:
	Jugador_Uno(Almacen* inventario, Lista<Coordenada*>* edificios);
	~Jugador_Uno() override;
	bool mover(const Coordenada& destino, const Mapa& mapa) override;
};

#endif /* JUGADOR_JUGADORES_JUGADORUNO_H_ */
