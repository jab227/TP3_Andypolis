#include "Jugador.h"

Jugador::Jugador(std::size_t id, Almacen *inventario, Lista<Coordenada*>* edificios)
    : id_(id), energia_(0), inventario_(inventario), edificios_(edificios){}

Jugador::Jugador(std::size_t id, Almacen *inventario)
    : id_(id), energia_(0), inventario_(inventario), edificios_(nullptr){}

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

bool Jugador::es_energia_maxima(const std::size_t &energia_recuperada) const {
	return ((energia_ + energia_recuperada) >= ENERGIA_MAXIMA);
}

bool Jugador::recuperar_energia(const std::size_t &valor) {
	bool es_maxima = es_energia_maxima(valor);
	if (es_maxima) energia_ = ENERGIA_MAXIMA;
	else energia_ += valor;
	return es_maxima;
}

void Jugador::mostrar_construidos(const Mapa* mapa) const{
	if( !this -> ubicaciones_.vacia() ){
		//TablePrinter printer = TablePrinter();
		//printer.print_row( mapa , ubicaciones_.consulta(i), std::cout); //lo comento por ahora
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
