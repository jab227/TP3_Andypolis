#include "parser_ubicacion.h"

#include "../jugador/jugadores/JugadorDos.h"
#include "../jugador/jugadores/JugadorUno.h"

std::string ParserUbicacion::nombre(const std::smatch& match) const {
	return match.str(1);
}

std::size_t ParserUbicacion::x(const std::smatch& match) const {
	return std::stoul(match.str(2));
}

std::size_t ParserUbicacion::y(const std::smatch& match) const {
	return std::stoul(match.str(3));
}

void ParserUbicacion::material(const std::smatch& match, Mapa*& mapa) {
	Coordenada coordenada = Coordenada(x(match), y(match));
	mapa->poner_material_ubicacion(nombre(match), coordenada);
}

Coordenada ParserUbicacion::edificio(const std::smatch& match, Mapa*& mapa) {
	Coordenada coordenada = Coordenada(x(match), y(match));
	mapa->construir_edificio_ubicacion(nombre(match), coordenada);
	return coordenada;
}

std::smatch ParserUbicacion::conseguir_coincidencia(const std::string& str) {
	std::regex pattern("(\\w+|\\w+ \\w+) \\((\\d+), (\\d+)\\)");
	std::smatch match;
	std::regex_search(str, match, pattern);
	return match;
}

void ParserUbicacion::parse(const std::string& input, Mapa*& casillero) {}

void ParserUbicacion::parse(const std::string& input, Mapa*& mapa,
			    Lista<Jugador*>& jugadores) {
	std::string aux;
	std::stringstream ss(input);
	enum {
		JUGADOR_UNO,
		JUGADOR_DOS,
		MATERIAL,
		VACIO
	} ubicacion = MATERIAL;	 // Lo primero que leo son materiales
	while (getline(ss, aux, '\n')) {
		std::smatch match = conseguir_coincidencia(aux);
		if (nombre(match) == "1") {
			ubicacion = JUGADOR_UNO;
			jugadores.alta_al_final(
			    new Jugador_Uno(Coordenada(x(match), y(match))));
			// Busco la siguiente linea
			getline(ss, aux, '\n');
			match = conseguir_coincidencia(aux);
		}
		if (nombre(match) == "2") {
			ubicacion = JUGADOR_DOS;
			jugadores.alta_al_final(
			    new Jugador_Dos(Coordenada(x(match), y(match))));
			// Busco la siguiente linea, si llegue al final del
			// archivo quiero que no haga nada.
			if (!(getline(ss, aux, '\n'))) ubicacion = VACIO;
			else match = conseguir_coincidencia(aux);
		}

		switch (ubicacion) {
			case JUGADOR_UNO: {
				jugadores.consulta(1)->agregar_ubicacion(
				    edificio(match, mapa));
				break;
			}
			case JUGADOR_DOS: {
				jugadores.consulta(2)->agregar_ubicacion(
				    edificio(match, mapa));
				break;
			}
			case MATERIAL: {
			material(match, mapa);
				break;
			}
			default:;
		}
	}
}
