#include "Jugador.h"

Jugador::Jugador(std::size_t id, Almacen *inventario)
    : id_(id), energia_(0), inventario_(inventario) {}

Jugador::~Jugador() {
	delete inventario_;
	inventario_ = nullptr;
}

std::size_t Jugador::obtener_jugador() const { return id_; }

std::size_t Jugador::obtener_energia() const { return energia_; }

Almacen *Jugador::obtener_inventario() const { return inventario_; }

bool Jugador::energia_suficiente(const std::size_t &energia_requerida) const {
	return (energia_ >= energia_requerida);
}

bool Jugador::usar_energia(const std::size_t &valor) {
	bool es_suficiente = energia_suficiente(valor);
	if (es_suficiente) energia_ -= valor;
	return es_suficiente;
}

void Jugador::agregar_ubicacion(Coordenada* coordenada,
				const std::string &nombre_edificio) {
	Lista<Coordenada*> aux;
	if(edificios_.buscar(nombre_edificio, aux)) {
		aux.alta_al_final(coordenada);
	} else {
		edificios_.insertar(nombre_edificio, Lista<Coordenada*>());
	}
}
