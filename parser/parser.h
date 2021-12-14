#ifndef PARSER_H_
#define PARSER_H_

#include <string>

template <typename T>
class Parser {
       public:
	// Constructor por defecto 
	Parser() = default;
	// Constructor de copia por defecto
	Parser(const Parser& rhs) = default;
	// Operador de asignacion por defecto
	Parser& operator=(const Parser& rhs) = default;
	// Destructor por defectp
	virtual ~Parser() = default;
	// Pre: -
	// Pos: Parsea el string input, y devuelve un elemento de tipo T
	virtual void parse(const std::string& input, T& element) = 0;
};

#endif
