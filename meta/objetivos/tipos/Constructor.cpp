#include "Constructor.h"
#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"


const std::string NOMBRE = "Constructor";
Constructor::Constructor(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE, jugador), mapa(mapa) {}

Constructor::~Constructor(){ }

bool Constructor::actualizar() {
	Lista<Coordenada> coordenadas = jugador->obtener_edificios();
	Lista<std::string> claves = Planos::edificios_disponibles();
	
	std::size_t coincidencias = 0;
	std::string nombre_edificio;
	for (std::size_t i = 1; i <= coordenadas.consulta_largo(); ++i) {
		bool encontrado = false;
		for(std::size_t j = 1; j <= claves.consulta_largo() && !encontrado; ++j) {
			nombre_edificio = mapa->obtener_contenido_ubicacion(coordenadas.consulta(i));
			if(nombre_edificio == claves.consulta(j)) {
				coincidencias++;
				encontrado = true;
			}
		}
	}

	cumplido = (coincidencias == claves.consulta_largo());
	return cumplido;
}
	