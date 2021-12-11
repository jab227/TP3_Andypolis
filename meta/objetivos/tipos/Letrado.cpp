#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"

#include "Letrado.h"

const std::string NOMBRE = "Letrado.h";

Letrado::Letrado(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE,jugador), mapa(mapa) {}

Letrado::~Letrado(){ }

// Haber construido el maximo de escuelas
bool Letrado::actualizar() {
	Lista<Coordenada> coord = jugador->obtener_edificios();
	std::size_t contador = 0;
	std::string nombre_edificio;
	for (std::size_t i = 0; i <= coord.consulta_largo(); ++i) {
		nombre_edificio = mapa->obtener_contenido_ubicacion(coord.consulta(i));
		if(nombre_edificio == "escuela") contador++;
	}
	return (contador == Planos::cantidad_permitida("escuela"));
}

