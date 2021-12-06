#include "Jugador.h"
#include "../empresa/Planos.h"

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
	if( !this -> edificios_ -> vacia() ){
		//TablePrinter printer = TablePrinter();
		//printer.print_row( mapa , ubicaciones_.consulta(i), std::cout); //lo comento por ahora
	}
}

void Jugador::agregar_ubicacion( Coordenada* coordenada) {
	edificios_->alta_al_final(coordenada);
}

std::size_t Jugador::cantidad_ubicaciones() const {
	return edificios_->consulta_largo();
}

Coordenada* Jugador::obtener_ubicacion(const std::size_t indice) const {
	return edificios_->consulta(indice);
}

void Jugador::eliminar_ubicacion(const Coordenada& coordenada) {
	std::size_t indice = existe_ubicacion(coordenada);
	if(indice){
		edificios_->baja(indice);
	}
}

Resultado_Chequeos Jugador::tiene_materiales( Lista<Material>* materiales) const{
	//Hacer sobrecarga.
	return this -> inventario_ -> hay_lista_materiales(materiales);
}

std::size_t Jugador::cantidad_edificios(const std::string &nombre_edificio,  Mapa* mapa) const{
	std::size_t construidos;
	for(std::size_t i = 1; i < edificios_ -> consulta_largo() + 1; i++){
		Coordenada* ubicacion = this -> obtener_ubicacion(i);
		std::string edificio = mapa -> obtener_contenido_ubicacion( *ubicacion );
		if(edificio == nombre_edificio) construidos++;
	}
	return construidos;
}

//TODO: Constantes
void Jugador::usar_lista_materiales( Lista<Material>* materiales){
	this -> inventario_ -> descontar_lista_materiales(materiales,100);
}

void Jugador::recuperar_lista_materiales( Lista<Material>* materiales){
	this -> inventario_ -> sumar_lista_materiales(materiales,25);
}

void Jugador::sumar_lista_materiales( Lista<Material>* materiales){
	this -> inventario_ -> sumar_lista_materiales(materiales,100);
}

Lista<Material>* Jugador::obtener_recursos_producidos( Mapa* mapa){
	std::string nombre_edificio;
	Edificio* edificio;
	Lista<Material>* listado = new Lista<Material>;
	Material material_producido;
	std::size_t agregados = 0;
	Coordenada* coordenada;

	for(std::size_t i = 1; i <= this -> edificios_->consulta_largo(); i++){
		coordenada = obtener_ubicacion(i);
		//No necesito chequear si esta construido.
		nombre_edificio = mapa -> obtener_contenido_ubicacion(*coordenada);
		edificio = Planos::buscar(nombre_edificio);
		material_producido = edificio -> producir_material();
		//Si no tengo construidos, el material que se sume va a ser 0.
		material_producido.cambiar_cantidad( material_producido.obtener_cantidad() * cantidad_edificios(nombre_edificio,mapa) );
		//TODO: Comparador de Material.
		if(material_producido.obtener_nombre() != "ninguno") //provisorio.
			listado -> alta(material_producido, ++agregados);
	}
	return listado;
}

std::size_t Jugador::existe_ubicacion( Coordenada coordenada) const{
	std::size_t i = 1;
	std::size_t indice = 0;
	Coordenada* tmp;
	while(i <= edificios_ -> consulta_largo() || !indice){
		tmp = obtener_ubicacion(i);
		if( coordenada == *tmp) indice = i;
		else i++;
	}
	return indice;
}

void Jugador::mostrar_inventario() const{
	this -> inventario_ -> mostrar_materiales();
}