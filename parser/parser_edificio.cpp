#include "parser_edificio.h"
#include "../utils/LecturaArchivos.h"

std::string ParserEdificio::nombre(const std::smatch& match) const {
	return match.str(1);
}

std::size_t ParserEdificio::piedra(const std::smatch& match) const {
	return std::stoul(match.str(2));
}

std::size_t ParserEdificio::madera(const std::smatch& match) const {
	return std::stoul(match.str(3));
}

std::size_t ParserEdificio::metal(const std::smatch& match) const {
	return std::stoul(match.str(4));
}

std::size_t ParserEdificio::permitidos(const std::smatch& match) const {
	return std::stoul(match[5]);
}

void ParserEdificio::parse(const std::string& input, Edificio*& edificio) {
	std::regex pattern("(\\w+|\\w+\\s\\w+) (\\d+) (\\d+) (\\d+) (\\d+)");
	std::smatch match;
	std::regex_search(input, match, pattern);

	edificio = traductor_edificios(nombre(match), piedra(match), madera(match), metal(match), permitidos(match));
}
