#include "parser_edificio.h"

#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Fabrica.h"
#include "../edificio/edificios/Mina.h"
#include "../edificio/edificios/MinaOro.h"
#include "../edificio/edificios/Obelisco.h"
#include "../edificio/edificios/PlantaElectrica.h"

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

	std::string nombre_edificio = nombre();
	if (nombre_edificio == "aserradero") {
		edificio =
		    new Aserradero(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "escuela") {
		edificio =
		    new Escuela(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "fabrica") {
		edificio =
		    new Fabrica(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "mina") {
		edificio = new Mina(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "mina oro") {
		edificio =
		    new Mina_Oro(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "obelisco") {
		edificio =
		    new Obelisco(piedra(), madera(), metal(), permitidos());
	} else if (nombre_edificio == "planta electrica") {
		edificio = new Planta_Electrica(piedra(), madera(), metal(),
						permitidos());
	} else {
		edificio = nullptr;
	}
}
