#ifndef JUGADOR_JUGADORES_JUGADORDOS_H_
#define JUGADOR_JUGADORES_JUGADORDOS_H_

#include "../Jugador.h"

class Jugador_Dos final : public Jugador {
       private:
	static const std::size_t costo_camino = 4;
	static const std::size_t costo_betun = 0;
	static const std::size_t costo_lago = 5;
	static const std::size_t costo_muelle = 2;
	static const std::size_t costo_terreno = 25;

public:
	Jugador_Dos(const Coordenada& coordenada);
	~Jugador_Dos() override;
private:
	std::size_t obtener_costo_terreno(Coordenada coordenada, Mapa* mapa);
};

#endif /* JUGADOR_JUGADORES_JUGADORDOS_H_ */
