#ifndef LECTURAARCHIVOS_H_
#define LECTURAARCHIVOS_H_

#include <string>

#include "../Casillero/Casillero.h"
#include "../diccionario/diccionario.h"
#include "../edificio/Edificio.h"
#include "../parser/parser_edificio.h"
#include "../parser/parser_inventario.h"
#include "../parser/parser_mapa.h"
#include "../parser/parser_ubicacion.h"
#include "../utils/coordenada.h"

enum Partida {NUEVA, CONTINUACION};

const char ESPACIO = ' ', ENTER = 10, DELIMITADOR_UBICACION = '(';

// PRE: -
// POST: devuelve si la palabra esta compuesta por todos numeros o no.
bool es_numero(std::string palabra);

// PRE: nombre debe ser un edificio valido
// POST: devuelve el edificio cargado con los datos
Edificio* traductor_edificios(std::string nombre, std::size_t piedra = 0,
			      std::size_t madera = 0, std::size_t metal = 0,
			      std::size_t max_permitidos = 0);

// PRE: nombre debe corresponder a un casillero
// POST: se devuelve el casillero vacio correspondiente a nombre creado en
// memoria dinamica
Casillero* traductor_casillero(char nombre);

// PRE: nombre debe ser un material valido
// POST: devuelve el material cargado con los datos
Material* traductor_materiales(std::string nombre, std::size_t cantidad);

Diccionario<std::string, Edificio*> leer_de_archivo(const std::string& ruta,
						    ParserEdificio parser);

Mapa* leer_de_archivo(const std::string& ruta, ParserMapa parser);

Partida leer_de_archivo(const std::string& ruta, ParserUbicacion parser,
		     Mapa*& mapa, Lista<Jugador*>& jugadores);

void leer_de_archivo(const std::string& ruta, ParserInventario parser, Lista<Jugador*>& jugadores, Partida partida); 

void inicializar_inventario_nueva_partida(Jugador* jugador);

#endif /* LECTURAARCHIVOS_H_ */
