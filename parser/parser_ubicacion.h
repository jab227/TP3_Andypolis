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
	Coordenada edificio(
	    const smatch& match, Mapa*& mapa,
	    const Diccionario<std::string, Edificio*>& edificios);
	void material(const smatch& match, Mapa*& mapa);
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
	// Pre: -
	// Pos: Parsea el string input, y devuelve un Cell*
	void parse(const std::string& input, Mapa*&) override;
	void parse(const std::string& input, Mapa*& mapa,
		   const Diccionario<std::string, Edificio*>& edificios,
		   Jugador* jugador_uno, Jugador* jugador_dos);
};

#endif
