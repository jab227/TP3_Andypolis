#ifndef PARSER_MAPA_H_
#define PARSER_MAPA_H_

#include <regex>

#include "../empresa/Mapa.h"
#include "parser.h"

class CityMapParser final : public Parser<CityMap*> {
       private:
	// Pre: -
	// Pos: Devuelve un size_t con el numero de filas en el mapa
	std::size_t rows(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con el numero de columnas en el mapa
	std::size_t cols(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un mapa de dimensiones: rows()xcols()
	Map map(const std::smatch& match) const;
	// Pre: 0 <= x, y <= rows(), cols()
	// Pos: Devuelve una celda con las coordenadas x e y, a partir del
	// icono en el mapa
	Cell* select_cell(std::size_t x, std::size_t y, Icon terrain) const;

       public:
	// Constructor por defecto
	CityMapParser() = default;
	// Constructor de copia por defecto
	CityMapParser(const CityMapParser& rhs) = default;
	// Operador de asignacion por defecto
	CityMapParser& operator=(const CityMapParser& rhs) = default;
	// Destructor por defecto
	~CityMapParser() = default;
	// Pre: -
	// Pos: Parsea el string input, y devuelve un CityMap*
	CityMap* parse(const std::string& input) override;
};

#endif
