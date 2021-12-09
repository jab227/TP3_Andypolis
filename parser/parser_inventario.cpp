#include "parser_inventario.h"

std::string ParserInventario::nombre(const std::smatch& match) const {
	return match[1];
}

std::size_t ParserInventario::cantidad(const std::smatch& match,
				       std::size_t jugador) const {
	// El indice de la cantidad correspondiente al jugador va
	// a tener un offset de 1
	return std::stoul(match[jugador + 1]);
}

void ParserInventario::parse(const std::string& input,
			     Lista<Material>& inventario) {}

void ParserInventario::parse(const std::string& input,
			     Lista<Material>& inventario_p1,
			     Lista<Material>& inventario_p2) {
	std::regex pattern("(\\w+) (\\d+) (\\d+)");
	std::smatch match;
	std::regex_search(input, match, pattern);

	Material p1 (nombre(match), cantidad(match, 1));
	inventario_p1.alta_al_final(p1);
	Material p2 (nombre(match), cantidad(match, 2));
	inventario_p2.alta_al_final(p2);
}
