#include "Minero.h"

const std::string NOMBRE = "Minero";
Minero::Minero(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE,jugador), mapa(mapa) {
	cumplido = estan_construidos(jugador->obtener_edificios());
}

bool Minero::actualizar() {
	if (!cumplido) {
		cumplido = estan_construidos(jugador->obtener_edificios());
	}
	return cumplido;
}

bool Minero::estan_construidos(const Lista<Coordenada>& edificios) {
	std::string nombre_edificio;
	for (std::size_t i = 1; i <= edificios.consulta_largo() && !(mina&&mina_oro); ++i) {
		nombre_edificio = mapa->obtener_contenido_ubicacion(edificios.consulta(i));
		if(!mina) mina = (nombre_edificio == "mina");
		if(!mina_oro) mina_oro = (nombre_edificio == "mina oro");
	}
	return (mina && mina_oro);
}