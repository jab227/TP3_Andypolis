#include "Minero.h"

const std::string NOMBRE = "Minero";
Minero::Minero(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE,jugador), mapa(mapa) {}

Minero::~Minero(){ }

bool Minero::actualizar() {
	Lista<Coordenada> coord = jugador->obtener_edificios();
	std::string nombre_edificio;
	bool mina = false;
	bool mina_oro = false;
	for (std::size_t i = 1; i <= coord.consulta_largo() && !(mina&&mina_oro); ++i) {
		nombre_edificio = mapa->obtener_contenido_ubicacion(coord.consulta(i));
		if(!mina) mina = (nombre_edificio == "mina");
		if(!mina_oro) mina_oro = (nombre_edificio == "mina_oro");
	}
	cumplido = (mina && mina_oro);
	return cumplido;
}
