#include "Jugador.h"
#include "../empresa/Planos.h"
#include "../printer/table_printer.h"
#include "../utils/LecturaArchivos.h"
#include "../printer/color_printer.h"

Jugador::Jugador(std::size_t id, const Coordenada& coordenada)
    : id_(id),
      energia_(0),
      inventario_(Almacen()),
      posicion_(coordenada),
      edificios_(Lista<Coordenada>()) {}

std::size_t Jugador::obtener_jugador() const { return id_; }

std::size_t Jugador::obtener_energia() const { return energia_; }

Almacen& Jugador::obtener_inventario() { return inventario_; }

void Jugador::colocar_almacen(const Almacen& inventario) {
	inventario_ = inventario;
}

std::size_t Jugador::energia_suficiente(const std::size_t& energia_requerida) const {
	return (energia_ - energia_requerida);
}

bool Jugador::usar_energia(const std::size_t& valor) {
	std::size_t es_suficiente = (energia_suficiente(valor) <= 100);
	if (es_suficiente) energia_ -= valor;
	return es_suficiente;
}

bool Jugador::es_energia_maxima(const std::size_t& energia_recuperada) const {
	return ((energia_ + energia_recuperada) >= ENERGIA_MAXIMA);
}

bool Jugador::recuperar_energia(const std::size_t& valor) {
	bool es_maxima = es_energia_maxima(valor);
	if (es_maxima)
		energia_ = ENERGIA_MAXIMA;
	else
		energia_ += valor;
	return es_maxima;
}

void Jugador::mostrar_construidos(const Mapa* mapa) const {
	if (!this->edificios_.vacia()) {
		 TablePrinter printer = TablePrinter();
		 Lista<std::string> lista = Lista<std::string>();
		 lista.alta_al_final("Edificio");
		 lista.alta_al_final("Coordenada");
		 lista.alta_al_final("Dañado");
		 printer.print_row(lista, std::cout );
		 for(std::size_t i = 1; i <= edificios_.consulta_largo(); i++)
			 printer.print_row( mapa , edificios_.consulta(i), std::cout);
		}
}

void Jugador::agregar_ubicacion(const Coordenada& coordenada) {
	edificios_.alta_al_final(coordenada);
}

std::size_t Jugador::cantidad_ubicaciones() const {
	return edificios_.consulta_largo();
}

const Lista<Coordenada>& Jugador::obtener_edificios() const {
	return edificios_;
}

Coordenada Jugador::obtener_ubicacion(const std::size_t indice) const {
	return edificios_.consulta(indice);
}

void Jugador::eliminar_ubicacion(const Coordenada& coordenada) {
	std::size_t indice = existe_ubicacion(coordenada);
	if (indice) {
		edificios_.baja(indice);
	}
}


Resultado_Chequeos Jugador::tiene_materiales( Lista<Material> materiales) const{
	//Hacer sobrecarga. Hay_lista_materiales con hay_materiales en almacen
	return this -> inventario_.hay_lista_materiales(materiales);
}

Resultado_Chequeos Jugador::tiene_materiales_reparar( Lista<Material> materiales) const{
	//Hacer sobrecarga. Hay_lista_materiales con hay_materiales en almacen
	return this -> inventario_.hay_lista_materiales(materiales, 25);
}

std::size_t Jugador::cantidad_edificios(const std::string &nombre_edificio,  Mapa* mapa) const{
	std::size_t construidos = 0;
	for (std::size_t i = 1; i <= edificios_.consulta_largo(); i++) {
		Coordenada ubicacion = this->obtener_ubicacion(i);
		std::string edificio = mapa->obtener_contenido_ubicacion(ubicacion);
		if (edificio == nombre_edificio) construidos++;
	}
	return construidos;
}

//TODO: Constantes
void Jugador::usar_lista_materiales( Lista<Material> materiales){
	this -> inventario_.descontar_lista_materiales(materiales,100);
}

void Jugador::cobrar_reparacion( Lista<Material> materiales){
	this -> inventario_.descontar_lista_materiales(materiales,25);
}

void Jugador::recuperar_lista_materiales( Lista<Material> materiales){
	this -> inventario_.sumar_lista_materiales(materiales,50);
}

void Jugador::sumar_lista_materiales( Lista<Material> materiales){
	this -> inventario_.sumar_lista_materiales(materiales,100);
}

Lista<Material> Jugador::obtener_recursos_producidos( Mapa* mapa){
	std::string nombre_edificio;
	Edificio* edificio;
	Lista<Material> listado;
	Material material_producido;
	std::size_t agregados = 0;
	Coordenada coordenada;

	for (std::size_t i = 1; i <= this->edificios_.consulta_largo(); i++) {

		coordenada = obtener_ubicacion(i);
		nombre_edificio = mapa->obtener_contenido_ubicacion(coordenada);
		edificio = Planos::buscar(nombre_edificio);
		material_producido = edificio -> producir_material();
		material_producido.cambiar_cantidad(
		    material_producido.obtener_cantidad());
		if (material_producido.obtener_nombre() != "ninguno")	// Es por si consultamos al Obelisco, pero tiene sentido?
			listado.alta(material_producido, ++agregados);
	}
	return listado;
}

std::size_t Jugador::existe_ubicacion(Coordenada coordenada) const {
	std::size_t indice = 0;
	Coordenada tmp;
	for(std::size_t i = 1; i <= edificios_.consulta_largo() && !indice; i++) {
		tmp = obtener_ubicacion(i);
		if (coordenada == tmp) indice = i;
	}
	return indice;
}

void Jugador::mostrar_inventario() const {
	this->inventario_.mostrar_materiales();
}

void Jugador::recolectar(Mapa* mapa){
	Lista<Material> listado = obtener_recursos_producidos(mapa);
	sumar_lista_materiales(listado);
}

bool Jugador::mover(Mapa* mapa){
	bool exito = true;
	Coordenada a_moverse;
	Grafo* grafo = cargar_grafo(mapa);
	Resultado_Chequeos resultado;
	do{
		std::cout << "Elegi las coordenadas a donde moverse o salir \n Fila: " << std::endl;
		resultado = this -> pedir_coordenadas(a_moverse, mapa, grafo);
	}while(this -> mostrar_mensaje(resultado));
	if(a_moverse.x() != COORDENADA_VACIA){
		ColorPrinter::color_msg("Seguro que queres moverte a la ubicacion ingresasda? [si/no].", FIN_COLOR, std::cout);
		if( this -> pedir_si_no() == "si"){
			this -> usar_energia(grafo -> energiaCaminoMinimo(this -> posicion_, a_moverse));
			Lista<Coordenada>* pasos = grafo -> caminoMinimo(this -> posicion_, a_moverse);
			while(!pasos -> vacia())
				this -> mover_a_coordenada(pasos -> baja(1), mapa);
			delete pasos;
		}else
			ColorPrinter::color_msg("No se realizó ningún cambio.",	 ROJO, std::cout);
	}
	delete grafo;
	return exito;
}

bool Jugador::mostrar_mensaje(Resultado_Chequeos resultado){
	bool fin = false;
	switch(resultado){
	case SALIR:
		ColorPrinter::color_msg("No se realizo ninguna accion.", ROJO, std::cout); // @suppress("No break at end of case")
	case EXITO:
		fin = true;
		break;
	case NO_EXISTE:
		ColorPrinter::color_msg("La/s opcion/es ingresada/s no es/son valida/s.", ROJO, std::cout);
		break;
	case FUERA_RANGO:
		ColorPrinter::color_msg( "La ubicacion ingresada excede el rango del mapa.", ROJO, std::cout);
		break;
	case NO_ENERGIA:
		ColorPrinter::color_msg( "No tenes suficiente energia.", ROJO, std::cout);
		ColorPrinter::color_msg( "Tenes " + to_string((int) this -> obtener_energia()) + " de energia.", ROJO, std::cout);
		break;
	default:
		break;
	}

	return fin;
}

Resultado_Chequeos Jugador::pedir_coordenadas(Coordenada& coordenada, Mapa* mapa, Grafo* grafo){
	std::string fila_ingresada, columna_ingresada;

	getline(std::cin, fila_ingresada);
	std::cout << "Columna: " << std::endl;
	getline(std::cin, columna_ingresada);

	return chequeo_coordenadas_moverse(fila_ingresada, columna_ingresada, coordenada, mapa, grafo);
}

Resultado_Chequeos Jugador::chequeo_coordenadas_moverse(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada, Mapa* mapa, Grafo* grafo){
	Resultado_Chequeos resultado = EXITO;
	coordenada = Coordenada(COORDENADA_VACIA, COORDENADA_VACIA);

	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR) resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada)) resultado = NO_EXISTE;
	else if(!(mapa -> es_cordenada_valida(Coordenada(stoul(fila_ingresada), stoul(columna_ingresada))))) resultado = FUERA_RANGO;
	else if((int) this -> obtener_energia() < grafo -> energiaCaminoMinimo(posicion_, Coordenada(stoul(fila_ingresada), stoul(columna_ingresada)))) resultado = NO_ENERGIA;
	else coordenada = Coordenada(stoul(fila_ingresada), stoul(columna_ingresada));

	return resultado;
}

std::string Jugador::pedir_si_no(){
	std::string respuesta;
	std::cout << "Respuesta:   ";
	getline(cin, respuesta);
	while(respuesta != "si" && respuesta != "no"){
		ColorPrinter::color_msg("La respuesta no es valida, solo se acepta si o no.", ROJO, std::cout);
		std::cout << "Respuesta:   ";
		getline(cin, respuesta);
	}
	return respuesta;
}

void Jugador::mover_a_coordenada(Coordenada coordenada, Mapa* mapa){
	this -> posicion_ = coordenada;
	mapa -> recolectar_material_ubicacion(coordenada, &(this -> inventario_));
}

Grafo* Jugador::cargar_grafo(Mapa* mapa){
	Grafo* grafo = new Grafo;
	std::size_t fila = 0, columna = 0;
	Coordenada coordenada_actual(fila, columna);
	while(mapa -> es_cordenada_valida(coordenada_actual)){
		while(mapa -> es_cordenada_valida(coordenada_actual)){
			grafo -> agregarVertice(coordenada_actual);
			if(columna != 0){
				grafo -> agregarCamino(Coordenada(fila, columna - 1), coordenada_actual, (int) obtener_costo_terreno(coordenada_actual, mapa));
				grafo -> agregarCamino(coordenada_actual, Coordenada(fila, columna - 1), (int) obtener_costo_terreno(Coordenada(fila, columna - 1), mapa));
			}
			if(fila != 0){
				grafo -> agregarCamino(Coordenada(fila - 1, columna), coordenada_actual, (int) obtener_costo_terreno(coordenada_actual, mapa));
				grafo -> agregarCamino(coordenada_actual, Coordenada(fila - 1, columna), (int) obtener_costo_terreno(Coordenada(fila - 1, columna), mapa));
			}
			columna++;
			coordenada_actual = Coordenada(fila, columna);
		}
		columna = 0;
		fila++;
		coordenada_actual = Coordenada(fila, columna);
	}
	grafo -> usarFloyd();
	return grafo;
}

std::string Jugador::a_string(){
	return id + " " + posicion_.a_string();
}
