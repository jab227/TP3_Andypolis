#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"

#include "Letrado.h"

const std::string NOMBRE = "Letrado";

Letrado::Letrado(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE,jugador), mapa(mapa) {
	cumplido = estan_construidos(jugador->obtener_edificios());
}

// Haber construido el maximo de escuelas
bool Letrado::actualizar() {
	if(!cumplido) {
		cumplido = estan_construidos(jugador->obtener_edificios()) ;
	}
	return cumplido;
}

bool Letrado::estan_construidos(const Lista<Coordenada>& edificios) {
	std::string nombre_edificio;
	std::size_t contador = 0;
	for (std::size_t i = 1; i <= edificios.consulta_largo(); ++i) {
		nombre_edificio = mapa->obtener_contenido_ubicacion(edificios.consulta(i));
		if(nombre_edificio == "escuela") contador++;
	}
	return (contador == Planos::cantidad_permitida("escuela"));
}