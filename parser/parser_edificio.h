#ifndef PARSER_EDIFICIO_H_
#define PARSER_EDIFICIO_H_

#include <regex>

#include "../edificio/Edificio.h"
#include "parser.h"

class ParserEdificio final : public Parser<Edificio*> {
       private:
	// Pre: -
	// Pos:	Devuelve un string con el nombre del edifico
	std::string nombre(const std::smatch& match) const;
	// Pre: -
	// Pos:	Devuelve un size_t con el costo de piedra
	std::size_t piedra(const std::smatch& match) const;
	// Pre: -
	// Pos:	Devuelve un size_t con el costo de madera
	std::size_t madera(const std::smatch& match) const;
	// Pre: -
	// Pos:	Devuelve un size_t con el costo de metal
	std::size_t metal(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con la cantidad de edificios
	// iguales permitidos
	std::size_t permitidos(const std::smatch& match) const;

       public:
	// Constructor por defecto
	ParserEdificio() = default;
	// Constructor de copia por defecto
	ParserEdificio(const ParserEdificio& rhs) = default;
	// Operador de asignacion por defecto
	ParserEdificio& operator=(const ParserEdificio& rhs) = default;
	// Destructor por defecto
	~ParserEdificio() = default;
	// Pre: -
	// Pos: Parsea el string input, y devuelve un puntero a edificio
	// por referencia.
	void parse(const std::string& input, Edificio*& edificio) override;
};

#endif
