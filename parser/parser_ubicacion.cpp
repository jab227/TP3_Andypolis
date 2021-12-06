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

void ParserUbicacion::material(const smatch& match, Mapa*& mapa) {
	mapa->poner_material_ubicacion(nombre(match), x(match), y(match));
}
Coordenada ParserUbicacion::edificio(const std::smatch& match, Mapa*& mapa,
		    const Diccionario<std::string, Edificio*>& edificios) {	
		    mapa->construir_edificio_ubicacion(edificios[nombre(match)], x(match), y(match));
		    return Coordenada(x(match), y(match));
}

std::smatch ParserUbicacion::conseguir_coincidencia(const std::string& str) {	
	std::regex pattern("(\\w+|\\w+ \\w+) \\((\\d+), (\\d+)\\)");
	std::smatch match;
	std::regex_search(str, match, pattern);
	return match;
}

void ParserUbicacion::parse(const std::string& input, Mapa*& casillero) {}

void ParserUbicacion::parse(
    const std::string& input, Mapa*& mapa,
    const Diccionario<std::string, Edificio*>& edificios, Jugador* jugador_uno,
    Jugador* jugador_dos) {
	std::string aux;
	std::stringstream ss(input);
	enum { JUGADOR_UNO, JUGADOR_DOS, MATERIAL, VACIO } ubicacion = MATERIAL; // Lo primero que leo son materiales
	while (getline(ss, aux, '\n')) {
		std::smatch match = conseguir_coincidencia(aux);
		if (nombre(match) == "1") {
			ubicacion = JUGADOR_UNO;
			jugador_uno =
			    new Jugador_Uno(Coordenada(x(match), y(match)));
			// Busco la siguiente linea
			getline(ss, aux, '\n');
		}
		if (nombre(match) == "2") {
			ubicacion = JUGADOR_DOS;
			jugador_dos =
			    new Jugador_Dos(Coordenada(x(match), y(match)));
			// Busco la siguiente linea, si llegue al final del archivo
			// quiero que no haga nada.
			if (!(getline(ss, aux, '\n'))) ubicacion = VACIO;
		}
		
		switch (ubicacion) {
			case JUGADOR_UNO: {
				jugador_uno->agregar_ubicacion(
				    edificio(match, mapa, edificios));
				break;
			}
			case JUGADOR_DOS: {
				jugador_uno->agregar_ubicacion(
				    edificio(match, mapa, edificios));
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
