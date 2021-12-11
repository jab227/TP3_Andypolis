#include "Meta.h"

#include <random>

#include "../utils/colors.h"

const std::string VERDE_META = BGND_GREEN_118, ROJO_META = BGND_RED_196;

Meta::Meta(Jugador* jugador, Mapa* mapa) : objetivos(Lista<Objetivo*>()) {
	Lista<Objetivo*> listado = crear_listado(jugador, mapa);
	std::size_t n;
	for (int i = 0; i < CANTIDAD_OBJETIVOS; i++) {
		n = (rand() % (listado.consulta_largo())) + 1;
		this->objetivos.alta_al_final(listado.baja(n));
	}
	this->eliminar_listado(listado);
}

Meta::~Meta() { eliminar_listado(this->objetivos); }

bool Meta::actualizar_objetivos() {
	bool cumplidos = true;
	for (std::size_t i = 1; i <= this->objetivos.consulta_largo(); i++) {
		cumplidos = (cumplidos && this->objetivos.consulta(i)->actualizar());
	}
	return cumplidos;
}

bool Meta::objetivos_cumplidos() {
	bool cumplidos = true;
	for (std::size_t i = 1; i <= this->objetivos.consulta_largo(); i++)
		cumplidos = (cumplidos && this->objetivos.consulta(i)->esta_cumplido());

	return cumplidos;
}

void Meta::mostrar_objetivos() {
	std::cout << "Los objetivos son: " << std::endl;
	std::string color;
  Objetivo* objetivo;
	for (std::size_t i = 1; i <= this -> objetivos.consulta_largo(); i++) {
		color = "  ";
		objetivo = this->objetivos.consulta(i);
		(objetivo->esta_cumplido()) ? color += VERDE_META
					    : color += ROJO_META;
		std::cout << color << "  " << END_COLOR << std::endl;
		std::cout << "  " << objetivo -> obtener_titulo();
	}
}

Lista<Objetivo*> Meta::crear_listado(Jugador* jugador, Mapa* mapa) {
	Lista<Objetivo*> listado;
	listado.alta_al_final(new Armado(jugador));
	listado.alta_al_final(new Bombardero(jugador));
	listado.alta_al_final(new Cansado(jugador));
	listado.alta_al_final(new Constructor(jugador, mapa));
	listado.alta_al_final(new Energetico(jugador));
	listado.alta_al_final(new Extremista(jugador));
	listado.alta_al_final(new Letrado(jugador, mapa));
	listado.alta_al_final(new Minero(jugador, mapa));
	listado.alta_al_final(new Monedas(jugador));
	listado.alta_al_final(new Piedras(jugador));

	return listado;
}

void Meta::eliminar_listado(Lista<Objetivo*>& listado) {
	while (!listado.vacia()) delete listado.baja(1);
}
