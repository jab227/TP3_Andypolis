#ifndef PARSER_MAPA_H_
#define PARSER_MAPA_H_

#include <regex>
#include "parser.h"
#include "../empresa/Mapa.h"

class ParserMapa final : public Parser<Mapa*> {
       private:
	// Pre: -
	// Pos: Devuelve un size_t con el numero de filas en el mapa
	std::size_t filas(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con el numero de columnas en el mapa
	std::size_t columnas(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un mapa de dimensiones: rows()xcols()
	Mapa* mapa(const std::smatch& match) const;
       public:
	// Constructor por defecto
	ParserMapa() = default;
	// Constructor de copia por defecto
	ParserMapa(const ParserMapa& rhs) = default;
	// Operador de asignacion por defecto
	ParserMapa& operator=(const ParserMapa& rhs) = default;
	// Destructor por defecto
	~ParserMapa() = default;
	// Pre: -
	// Pos: Parsea el string input, y devuelve un CityMap*
	void parse(const std::string& input, Mapa*&) override;
};

#endif
