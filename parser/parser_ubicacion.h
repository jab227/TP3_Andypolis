#ifndef PARSER_UBICACION_H_
#define PARSER_UBICACION_H_

#include <regex>

#include "../Casillero/Casillero.h"
#include "../diccionario/diccionario.h"
#include "../empresa/Mapa.h"
#include "../jugador/Jugador.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"
#include "parser.h"
class ParserUbicacion final : public Parser<Mapa*> {
       private:
	// Pre: -
	// Pos: Devuelve un string con el nombre del edificio/material
	std::string nombre(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con la coordenada x del edificio/
	// material
	std::size_t x(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con la coordenada y del edificio/
	// material
	std::size_t y(const std::smatch& match) const;
	// Pre: -
	// Pos: Crea un edificio en la coordenada leida, 
	// devuelve la coordenada.
	Coordenada edificio(const std::smatch& match, Mapa*& mapa);
	// Pre: -
	// Pos: Coloca el material en el mapa, en la coordenada
	// leida.
	void material(const std::smatch& match, Mapa*& mapa);
	// Pre: -
	// Pos: Busca coincidencias en el string segun el patron 
	// implmentado, devuelve un smatch.
	std::smatch conseguir_coincidencia(const std::string& str);

       public:
	// Constructor por defecto
	ParserUbicacion() = default;
	// Constructor de copia por defecto
	ParserUbicacion(const ParserUbicacion& rhs) = default;
	// Operador de asignacion por defecto
	ParserUbicacion& operator=(const ParserUbicacion& rhs) = default;
	// Destructor por defecto
	~ParserUbicacion() = default;
	// Pre: Mapa ya inicializado.
	// Pos: Parsea el string input, y devuelve un por referencia
	// un puntero a Mapa.
	void parse(const std::string& input, Mapa*&) override;
	// Pre: Mapa ya inicializado.
	// Pos: Parsea el string input, y carga mapa con las ubicaciones
	// obtenidas a partir del input y e inicializa los 
	// jugadores con sus posiciones; a menos que el archivo este vacio.
	void parse(const std::string& input, Mapa*& mapa,
		   Lista<Jugador*>& jugadores);
};

#endif
