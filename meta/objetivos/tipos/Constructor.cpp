#include "Constructor.h"
#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"


const std::string NOMBRE = "Constructor";
Constructor::Constructor(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE, jugador), mapa(mapa), claves(Planos::edificios_disponibles()) {
	claves.baja(6); // doy de baja el obelisco
	cumplido = estan_construidos(jugador->obtener_edificios());
}

Constructor::~Constructor(){ }

bool Constructor::actualizar() {
	if(!cumplido) {
		cumplido = estan_construidos(jugador->obtener_edificios());
	}
	return cumplido;
}

bool Constructor::estan_construidos(const Lista<Coordenada>& edificios) {
	std::string nombre_edificio;

	for (std::size_t i = 1; i <= edificios.consulta_largo(); ++i) {
		bool encontrado = false;
		for(std::size_t j = 1; j <= claves.consulta_largo() && !encontrado; ++j) {
			nombre_edificio = mapa->obtener_contenido_ubicacion(edificios.consulta(i));
			if(nombre_edificio == claves.consulta(j)) {
				encontrado = true;
				claves.baja(j);
			}
		}
	}
	cumplido = (claves.consulta_largo() == 0);
	return cumplido;
}
	