#ifndef PARSER_INVENTARIO_H_
#define PARSER_INVENTARIO_H_

#include "../utils/Lista.h"
#include "../material/Material.h"
#include "../empresa/Almacen.h"
#include "parser.h"
#include <regex>
#include <string>

class ParserInventario final : Parser<Lista<Material>> {
       private:
	// Pre: -
	// Pos: Devuelve un string con el nombre del material
	std::string nombre(const std::smatch& match) const;
	// Pre: -
	// Pos: Devuelve un size_t con la cantidad del material
	std::size_t cantidad(const std::smatch& match, std::size_t jugador) const;
       public:
	// Constructor por defecto 
	ParserInventario() = default;
	// Constructor de copia por defecto
	ParserInventario(const ParserInventario& rhs) = default;
	// Operador de asignacion por defecto
	ParserInventario& operator=(const ParserInventario& rhs) = default;
	// Destructor por defectp
	~ParserInventario() = default;
	// Pre: -
	// Pos: Parsea el string input, y devuelve un elemento de tipo T
	void parse(const std::string& input, Lista<Material>& inventario) override;
	// Pre: -
	// Pos: Parsea el string input, y devuelve por interfaz los inventarios de cada jugador.
	void parse(const std::string& input, Lista<Material>& inventario_p1, Lista<Material>& inventario_p2);
};

#endif
