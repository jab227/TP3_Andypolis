#include "JugadorDos.h"

Jugador_Dos::Jugador_Dos(const Coordenada& coordenada)
    : Jugador(2, coordenada){}

Jugador_Dos::~Jugador_Dos() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

std::size_t Jugador_Dos::obtener_costo_terreno(Coordenada coordenada, Mapa* mapa){
	std::size_t costo;
	char casillero = mapa -> obtener_identificador_casillero(coordenada);
	switch(casillero){
	case CAMINO:
		costo = costo_camino;
		break;
	case BETUN:
		costo = costo_betun;
		break;
	case MUELLE:
		costo = costo_muelle;
		break;
	case TERRENO:
		if(mapa -> obtener_contenido_ubicacion(coordenada) == CONTENIDO_VACIO)
			costo = costo_terreno;
		else
			costo = INFINITO;
		break;
	case LAGO:
		costo = costo_lago;
		break;
	default:
		costo = INFINITO;
	}
	return costo;
}
