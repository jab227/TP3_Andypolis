
#include "parser_mapa.h"

#include "../lib/utils.h"
#include "../map/buildable_cell.h"
#include "../map/inaccesible_cell.h"
#include "../map/transitable_cell.h"

CityMap* ParserMapa::parse(const std::string& input) {
	std::regex pattern("(\\d+) (\\d+)\\s*([\\w\\s]+)");
	std::smatch match;
	std::regex_search(input, match, pattern);

	Citymapa* mapa_ptr = new CityMap(mapa(match), rows(match), cols(match)); 	
	return mapa_ptr;
}

Cell* ParserMapa::select_cell(std::size_t x, std::size_t y,
				 Icon cell_icon) const {
	Cell* cell = nullptr;
	switch (cell_icon) {
		case ROAD:
			cell = new TransitableCell(x, y, nullptr, ROAD);
			break;
		case LAKE:
			cell = new InaccesibleCell(x, y, LAKE);
			break;
		case TERRAIN:
			cell = new BuildableCell(x, y, nullptr, TERRAIN);
			break;
		default:
			// Asumimos que los archivos estan bien formados
			break;
	};
	return cell;
}

Map ParserMapa::mapa(const std::smatch& match) const {
	std::string terrains = match[3].str();
	utils::remove_whitespace(terrains);

	Map terrain_mapa (rows(match));
	for (std::size_t i = 0; i < rows(match); ++i) {
		Vector<Cell*> aux;
		for (std::size_t j = 0; j < cols(match); ++j) {
			char c = terrains[j];
			aux.push_back(select_cell(i, j, (Icon)c));
		}
		terrain_map.push_back(aux);
	}

	return terrain_map;
}

std::size_t ParserMapa::filas(const std::smatch& match) const { return std::stoul(match[1]);}//stoul(match[1]); }

std::size_t ParserMapa::columnas(const std::smatch& match) const { return std::stoul(match[2]);}//stoul(match[2]); }
