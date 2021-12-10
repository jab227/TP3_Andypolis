#include "LecturaArchivos.h"

#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"
#include "../Casillero/casilleros/Betun.h"
#include "../Casillero/casilleros/Camino.h"
#include "../Casillero/casilleros/Muelle.h"
#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Fabrica.h"
#include "../edificio/edificios/Mina.h"
#include "../edificio/edificios/MinaOro.h"
#include "../edificio/edificios/Obelisco.h"
#include "../edificio/edificios/PlantaElectrica.h"
#include "../jugador/Jugador.h"
#include "../empresa/Planos.h"
#include "../empresa/Mapa.h"

#include <fstream>
bool es_numero(std::string palabra){
	bool resultado = true;
	int i = 0;
	if(palabra.size() == 0)
		resultado = false;
	while (i < (int) palabra.length() && resultado){
		resultado = isdigit(palabra[i]);
		i++;
	}
	return resultado;
}

Edificio* traductor_edificios(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t max_permitidos){
	Edificio* edificio = nullptr;
	if(nombre == "mina")
		edificio = new Mina(piedra, madera, metal, max_permitidos);
	else if (nombre == "aserradero")
		edificio = new Aserradero(piedra, madera, metal, max_permitidos);
	else if(nombre == "fabrica")
		edificio = new Fabrica(piedra, madera, metal, max_permitidos);
	else if(nombre == "escuela")
		edificio = new Escuela(piedra, madera, metal, max_permitidos);
	else if(nombre == "obelisco")
		edificio = new Obelisco(piedra, madera, metal, max_permitidos);
	else if(nombre == "planta electrica")
		edificio = new Planta_Electrica(piedra, madera, metal, max_permitidos);
	else if(nombre == "mina oro")
		edificio = new Mina_Oro(piedra, madera, metal, max_permitidos);
	return edificio;
}

/* Ahora estan los valores por default.
Edificio* traductor_edificios(std::string nombre){
	Edificio* edificio = nullptr;
	if(nombre == "mina")
		edificio = new Mina();
	else if (nombre == "aserradero")
		edificio = new Aserradero();
	else if(nombre == "fabrica")
		edificio = new Fabrica();
	else if(nombre == "escuela")
		edificio = new Escuela();
	else if(nombre == "obelisco")
		edificio = new Obelisco();
	else if(nombre == "planta electrica")
		edificio = new Planta_Electrica();
	else if(nombre == "mina oro")
		edificio = new Mina_Oro();
	return edificio;
}
*/

Casillero* traductor_casillero(char nombre) {
	Casillero* casillero;
	if (nombre == BETUN)
		casillero = new Betun();
	else if (nombre == CAMINO)
		casillero = new Camino();
	else if (nombre == LAGO)
		casillero = new Casillero_Inaccesible();
	else if (nombre == MUELLE)
		casillero = new Muelle();
	else if (nombre == TERRENO)
		casillero = new Casillero_Construible();
	return casillero;
}

Material* traductor_materiales(std::string nombre, std::size_t cantidad) {
	return new Material(nombre, cantidad);
}

Diccionario<std::string, Edificio*> leer_de_archivo(
    const std::string& ruta, ParserEdificio parser) {
	std::ifstream fin(ruta);
	std::string input;
	Edificio* edificio;
	Diccionario<std::string, Edificio*> diccionario;
	while (getline(fin, input)) {
		parser.parse(input, edificio);
		diccionario.insertar(edificio->obtener_nombre(), edificio);
	}
	fin.close();
	return diccionario;
};

Mapa* leer_de_archivo(const std::string& ruta, ParserMapa parser) {
	std::ifstream fin(ruta);
	std::string input;
	Mapa* mapa;
	getline(fin, input, '|');
	parser.parse(input, mapa);
	fin.close();
	return mapa;
}

void leer_de_archivo(const std::string& ruta, ParserUbicacion parser,
		     Mapa*& mapa, Lista<Jugador*>& jugadores) {
	std::ifstream fin(ruta);
	std::string input;
	getline(fin, input, '|');
	parser.parse(input, mapa, jugadores);
	fin.close();
}
void leer_de_archivo(const std::string& ruta, ParserInventario parser, Lista<Jugador*>& jugadores) {
	Lista<Material> j1_inventario, j2_inventario;
	std::ifstream fin(ruta);
	std::string input;
	while (getline(fin, input)) {
		// TODO: Emprolijar esto, helpers
		parser.parse(input, jugadores.consulta(1)->obtener_inventario().obtener_materiales(), jugadores.consulta(2)->obtener_inventario().obtener_materiales());
	}
	fin.close();
}

