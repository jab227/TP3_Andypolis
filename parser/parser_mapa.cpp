
#include "parser_mapa.h"


void ParserMapa::parse(const std::string& input, Mapa*& terrenos) {
	std::regex pattern("(\\d+) (\\d+)\\s*([\\w\\s]+)");
	std::smatch match;
	std::regex_search(input, match, pattern);

	terrenos = mapa(match);
}


Mapa* ParserMapa::mapa(const std::smatch& match) const {
	std::string aux;
	std::string resultado = "";
	std::stringstream ss(match.str(3));
	while(getline(ss,aux,' '))
		resultado+=aux;
	

				
}

std::size_t ParserMapa::filas(const std::smatch& match) const { return std::stoul(match[1]);}//stoul(match[1]); }

std::size_t ParserMapa::columnas(const std::smatch& match) const { return std::stoul(match[2]);}//stoul(match[2]); }
