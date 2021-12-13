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
#include "../jugador/jugadores/JugadorDos.h"
#include "../jugador/jugadores/JugadorUno.h"
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

// Necesito una manera de avisarle al programa el comienzo de una nueva partida
Partida leer_de_archivo(const std::string& ruta, ParserUbicacion parser,
		     Mapa*& mapa, Lista<Jugador*>& jugadores) {
	std::ifstream fin(ruta);
	Partida partida = NUEVA;
	if (fin.is_open()) {
		std::string input;
		getline(fin, input, '|');
		if (input == "") {
			jugadores.alta_al_final(
			    new Jugador_Uno(Coordenada(0, 0)));
			jugadores.alta_al_final(
			    new Jugador_Dos(Coordenada(1, 1)));
			fin.close();
		} else {
			parser.parse(input, mapa, jugadores);
			partida = CONTINUACION;
			fin.close();
		}
	}else{
		jugadores.alta_al_final(new Jugador_Uno(Coordenada(0, 0)));
		jugadores.alta_al_final(new Jugador_Dos(Coordenada(0, 1)));
	}
	return partida;
}

void leer_de_archivo(const std::string& ruta, ParserInventario parser, Lista<Jugador*>& jugadores, Partida partida) {
	std::ifstream fin(ruta);
	std::string input;
	if (partida != NUEVA) {
		while (getline(fin, input)) {
			parser.parse(input, jugadores.consulta(1)->obtener_inventario().obtener_materiales(), jugadores.consulta(2)->obtener_inventario().obtener_materiales());
		}
	} else {
		inicializar_inventario_nueva_partida(jugadores.consulta(1));
		inicializar_inventario_nueva_partida(jugadores.consulta(2));
	}
	fin.close();
}

void inicializar_inventario_nueva_partida(Jugador* jugador) {
	jugador->obtener_inventario().obtener_materiales().alta_al_final(Material(NOMBRES_MATERIALES[PIEDRA], 0));
	jugador->obtener_inventario().obtener_materiales().alta_al_final(Material(NOMBRES_MATERIALES[MADERA], 0));
	jugador->obtener_inventario().obtener_materiales().alta_al_final(Material(NOMBRES_MATERIALES[METAL], 0));
	jugador->obtener_inventario().obtener_materiales().alta_al_final(Material(NOMBRES_MATERIALES[ANDYCOINS], 0));
	jugador->obtener_inventario().obtener_materiales().alta_al_final(Material(NOMBRES_MATERIALES[BOMBAS], 0));
}
