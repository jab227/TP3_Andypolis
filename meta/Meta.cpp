#include <random>
#include "Meta.h"

Meta::Meta(Jugador* jugador) {
	this -> objetivos = new Lista<Objetivo*>;
	Lista<Objetivo*>* listado = crear_listado(jugador);
	std::size_t n;
	for(int i = 0; i < CANTIDAD_OBJETIVOS; i++){
		n = rand() % (listado -> consulta_largo()) + 1;
		this -> objetivos -> alta_al_final(listado -> baja(n));
	}
	this -> eliminar_listado(listado);

}

Meta::~Meta(){
	eliminar_listado(this -> objetivos);
}

bool Meta::actualizar_objetivos(){
	bool cumplidos = true;
	for(std::size_t i = 1; i <= this -> objetivos -> consulta_largo(); i++)
		cumplidos &= this -> objetivos -> consulta(i) -> actualizar();

	return cumplidos;
}

bool Meta::objetivos_cumplidos(){
	bool cumplidos = true;
	for(std::size_t i = 1; i <= this -> objetivos -> consulta_largo(); i++)
		cumplidos &= this -> objetivos -> consulta(i) -> esta_cumplido();

	return cumplidos;
}

void Meta::mostrar_objetivos(){
	std::cout << "Los objetivos son: " << std::endl;
	for(std::size_t i = 1; i <= this -> objetivos -> consulta_largo(); i++){
		std::cout << "- " << this -> objetivos -> consulta(i) -> obtener_titulo() << std::endl;
	}
}

Lista<Objetivo*>* Meta::crear_listado(Jugador* jugador){

	Lista<Objetivo*>* listado = new Lista<Objetivo*>;
	listado -> alta_al_final(new Armado(jugador));
	listado -> alta_al_final(new Bombardero(jugador));
	listado -> alta_al_final(new Cansado(jugador));
	listado -> alta_al_final(new Constructor(jugador));
	listado -> alta_al_final(new Energetico(jugador));
	listado -> alta_al_final(new Extremista(jugador));
	listado -> alta_al_final(new Letrado(jugador));
	listado -> alta_al_final(new Minero(jugador));
	listado -> alta_al_final(new Monedas(jugador));
	listado -> alta_al_final(new Piedras(jugador));

	return listado;
}

void Meta::eliminar_listado(Lista<Objetivo*>* &listado){
	while(!listado -> vacia())
		delete listado -> baja(1);
	delete listado;
	listado = nullptr;
}
