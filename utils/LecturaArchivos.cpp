#include "LecturaArchivos.h"

#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"
#include "../Casillero/CasilleroTransitable.h"
#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Fabrica.h"
#include "../edificio/edificios/Mina.h"
#include "../edificio/edificios/Obelisco.h"
#include "../edificio/edificios/PlantaElectrica.h"

Edificio* traductor_edificios(std::string nombre, std::size_t piedra,
			      std::size_t madera, std::size_t metal,
			      std::size_t max_permitidos) {
	Edificio* edificio = nullptr;
	if (nombre == "mina")
		edificio = new Mina(piedra, madera, metal, max_permitidos);
	else if (nombre == "aserradero")
		edificio =
		    new Aserradero(piedra, madera, metal, max_permitidos);
	else if (nombre == "fabrica")
		edificio = new Fabrica(piedra, madera, metal, max_permitidos);
	else if (nombre == "escuela")
		edificio = new Escuela(piedra, madera, metal, max_permitidos);
	else if (nombre == "obelisco")
		edificio = new Obelisco(piedra, madera, metal, max_permitidos);
	else if (nombre == "planta electrica")
		edificio =
		    new Planta_Electrica(piedra, madera, metal, max_permitidos);
	return edificio;
}

Casillero* traductor_casillero(char nombre) {
	Casillero* casillero;
	if (nombre == BETUN)
		casillero = new Betun();
	if (nombre == CAMINO)
		casillero = new Camino();
	else if (nombre == LAGO)
		casillero = new Lago();
	else if (nombre == MUELLE)
		casillero = new Muelle();
	else if (nombre == TERRENO)
		casillero = new Terreno();
	return casillero;
}

Material* traductor_materiales(std::string nombre, std::size_t cantidad) {
	return new Material(nombre, cantidad);
}

