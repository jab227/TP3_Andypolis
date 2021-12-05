#include "Jugador.h"

Jugador::Jugador(std::size_t id, Almacen *inventario, Lista<Coordenada*>* edificios)
    : id_(id), energia_(0), inventario_(inventario), edificios_(edificios){}

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

void Jugador::agregar_ubicacion(Coordenada* coordenada) {
	edificios_->alta_al_final(coordenada);
}

std::size_t Jugador::cantidad_ubicaciones() const {
	return edificios_->consulta_largo();
}

void Jugador::eliminar_ubicacion(Coordenada coordenada) {
	std::size_t indice = (std::size_t) edificios_->buscar_indice(coordenada);
}
