#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"

#include "Letrado.h"

const std::string NOMBRE = "Letrado";

Letrado::Letrado(Jugador* jugador, Mapa* mapa) : Objetivo(NOMBRE,jugador), mapa(mapa) {}

Letrado::~Letrado(){ }

// Haber construido el maximo de escuelas
bool Letrado::actualizar() {
	Lista<Coordenada> coord = jugador->obtener_edificios();
	std::size_t contador = 0;
	std::string nombre_edificio;
	for (std::size_t i = 1; i <= coord.consulta_largo(); ++i) {
		nombre_edificio = mapa->obtener_contenido_ubicacion(coord.consulta(i));
		std::cout << nombre_edificio << endl;
		if(nombre_edificio == "escuela") {
		contador++;
				//DEBUG
			std::cout << contador << std::endl;
		}
	}
	cumplido = (contador == Planos::cantidad_permitida("escuela"));
	return cumplido;
}

