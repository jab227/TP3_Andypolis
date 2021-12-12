#include "Programa.h"

#include <ctime>
#include <fstream>
#include <iostream>

#include "../diccionario/diccionario.h"
#include "../jugador/jugadores/JugadorDos.h"
#include "../jugador/jugadores/JugadorUno.h"
#include "../parser/parser_edificio.h"
#include "../parser/parser_inventario.h"
#include "../parser/parser_mapa.h"
#include "../parser/parser_ubicacion.h"
#include "../printer/printer.h"
#include "../utils/LecturaArchivos.h"

const std::size_t CONSTRUIR = 1, LISTAR_CONSTRUIDOS = 2, DEMOLER = 3, ATACAR = 4,
	  REPARAR = 5, COMPRAR_BOMBAS = 6, CONSULTAR = 7, LISTAR_MATERIALES = 8,
	  OBJETIVOS = 9, RECOLECTAR = 10, MOVERSE = 11, FIN_TURNO = 12,
	  GUARDAR_SALIR = 13;
const std::size_t OPCION_MINIMA_JUEGO = CONSTRUIR, OPCION_MAXIMA_JUEGO = GUARDAR_SALIR;

const std::size_t MODIFICAR_EDIFICIO = 1, LISTAR_EDIFICIOS = 2, MOSTRAR_MAPA = 3,
	  COMENZAR = 4, GUARDAR_SALIR_INICIO = 5;
const std::size_t OPCION_MINIMA_INICIO = MODIFICAR_EDIFICIO,
	  OPCION_MAXIMA_INICIO = GUARDAR_SALIR_INICIO;

const std::size_t ENERGIA_INICIAL = 50, ENERGIA_SUMADA_FIN_TURNO = 20;
const std::size_t ENERGIA[] = {0,
		       ENERGIA_CONSTRUIR,
		       ENERGIA_LISTAR_CONSTRUIDOS,
		       ENERGIA_DEMOLER,
		       ENERGIA_ATACAR,
		       ENERGIA_REPARAR,
		       ENERGIA_COMPRAR_BOMBAS,
		       ENERGIA_CONSULTAR,
		       ENERGIA_LISTAR_MATERIALES,
		       ENERGIA_OBJETIVOS,
		       ENERGIA_RECOLECTAR,
		       ENERGIA_MOVERSE,
		       ENERGIA_FIN_TURNO,
		       ENERGIA_GUARDAR_SALIR};
// Limpiar un poco el constructor
Programa::Programa(std::string ruta_materiales, std::string ruta_edificios,
		   std::string ruta_mapa, std::string ruta_ubicaciones)
    : empresa_constructora(nullptr),
      instancia(INICIO),
      jugador_activo(0),
      jugadores(Lista<Jugador*>()),
      objetivos_jugadores(Lista<Meta*>()) {
	Planos* plano =
	    new Planos(leer_de_archivo(ruta_edificios, ParserEdificio()));
	//plano ->mostrar_edificios();	
	Mapa* mapa = leer_de_archivo(ruta_mapa, ParserMapa());
	leer_de_archivo(ruta_ubicaciones, ParserUbicacion(), mapa, jugadores);
	empresa_constructora = new Empresa_Constructora(plano, mapa);
	leer_de_archivo(ruta_materiales, ParserInventario(), jugadores);
	this->instancia = INICIO;
	objetivos_jugadores.alta_al_final(new Meta(jugadores.consulta(1), mapa));
	objetivos_jugadores.alta_al_final(new Meta(jugadores.consulta(2), mapa));
	srand((unsigned int)time(0));
	this->jugador_activo = rand() % 2 + 1;
}

Programa::~Programa() {
	delete this->empresa_constructora;
	while (!this->objetivos_jugadores.vacia()) delete this->objetivos_jugadores.baja(1);
	while (!this->jugadores.vacia()) delete this->jugadores.baja(1);
	while (!this->objetivos_jugadores.vacia()) delete this->objetivos_jugadores.baja(1);
}

void Programa::mostrar_menu() {
	if (this->instancia == INICIO)
		this->mostrar_menu_inicio();
	else
		this->mostrar_menu_juego();
}

void Programa::mostrar_menu_juego() {
	cout << "Turno del jugador " << this -> jugador_activo << ". "
	     << "Tenes "
	     << jugadores.consulta(jugador_activo) -> obtener_energia()
	     << " de energia." << endl;
	this -> empresa_constructora -> mostrar_mapa(jugadores);
	cout << "--------------------------------------------------------------"
	     << endl;
	cout << "Elija una de las siguientes opciones ingresando solo el numero"
	     << endl;
	cout << "1. Construir edificio por nombre." << endl;
	cout << "2. Listar mis edificios construidos." << endl;
	cout << "3. Demoler un edificio por coordenada." << endl;
	cout << "4. Atacar un edificio por coordenada." << endl;
	cout << "5. Reparar un edificio por coordenada." << endl;
	cout << "6. Comprar bombas." << endl;
	cout << "7. Consultar coordenada." << endl;
	cout << "8. Mostrar inventario." << endl;
	cout << "9. Mostrar objetivos." << endl;
	cout << "10. Recolectar recursos producidos." << endl;
	cout << "11. Moverse a una coordenada." << endl;
	cout << "12. Finalizar turno." << endl;
	cout << "13. Guardar y salir." << endl;
	cout << "--------------------------------------------------------------"
	     << endl;
}

void Programa::mostrar_menu_inicio() {
	cout << "--------------------------------------------------------------"
	     << endl;
	cout << "Elija una de las siguientes opciones ingresando solo el numero"
	     << endl;
	cout << "1. Modificar edificio por nombre." << endl;
	cout << "2. Listar todos los edificios." << endl;
	cout << "3. Mostrar mapa." << endl;
	cout << "4. Comenzar partida." << endl;
	cout << "5. Guardar y salir." << endl;
	cout << "--------------------------------------------------------------"
	     << endl;
}

bool Programa::procesar_opcion(std::size_t opcion) {
	bool resultado;
	if (this->instancia == INICIO)
		resultado = this -> procesar_opcion_inicio(opcion);
	else {
		std::size_t energia_restante =
		    this->jugadores.consulta(this->jugador_activo)
			->energia_suficiente(ENERGIA[opcion]);
		if (energia_restante >= 0)
			resultado = this->procesar_opcion_juego(opcion);
		else
			cout << "Energia insuficiente, te faltan "
			     << -energia_restante
			     << " de energia para realizar esta accion."
			     << endl;
	}
	return resultado;
}

bool Programa::procesar_opcion_inicio(std::size_t opcion_elegida) {
	bool fin = false;
	switch (opcion_elegida) {
		case MODIFICAR_EDIFICIO:
			this->empresa_constructora->modificar_edificios();
			//this->limpiar_pantalla(); lo saque porque no se ve que mensaje te devuelve la funcion
			// break; Para que se listen los edificios post editar.
		case LISTAR_EDIFICIOS:
			this->empresa_constructora->mostrar_edificios();
			break;
		case MOSTRAR_MAPA:
			this->empresa_constructora->mostrar_mapa(jugadores);
			break;
		case COMENZAR:
			this -> comenzar_partida();
			break;
		case GUARDAR_SALIR_INICIO:
			fin = true;
			cout << "Implementar guardar y salir!" << endl;
			cout << "Adios!" << endl;
			break;
	}
	return fin;
}

bool Programa::procesar_opcion_juego(std::size_t opcion_elegida) {
	bool fin = false;
	switch (opcion_elegida) {
		case CONSTRUIR:
			this->empresa_constructora->construir_edificio(
			    this->jugadores.consulta(
				this->jugador_activo));
			break;
		case LISTAR_CONSTRUIDOS:
			this->empresa_constructora->mostrar_construidos(
			    this->jugadores.consulta(
				this->jugador_activo));
			break;
		case DEMOLER:
			this->empresa_constructora->demoler_edificio(
			    this->jugadores.consulta(
				this->jugador_activo));
			break;
		case ATACAR:
			this->empresa_constructora->atacar_edificio(
			    jugadores.consulta(jugador_activo),
			    jugadores.consulta(3 - jugador_activo));
			break;
		case REPARAR:
			this->empresa_constructora->reparar_edificio(
			    jugadores.consulta(jugador_activo));
			break;
		case COMPRAR_BOMBAS:
			this->empresa_constructora->comprar_bombas(
			    this->jugadores.consulta(jugador_activo));
			break;
		case CONSULTAR:
			this->empresa_constructora->consultar_coordenada();
			break;
		case LISTAR_MATERIALES:
			this->empresa_constructora->mostrar_materiales(
			    this->jugadores.consulta(this->jugador_activo));
			break;
		case OBJETIVOS:
			this->objetivos_jugadores.consulta(this->jugador_activo)
			    ->mostrar_objetivos();
			break;
		case RECOLECTAR:
			// FER: Hice recoger_material() en los casilleros
			// Este sirve tanto para los edificios como para los
			// materiales. 	Edificios -> El jugador tiene una lista de
			//ubicaciones. Con pasarle el inventario le suma el
			//material producido. 	Materiales -> El jugador al
			//moverse por las celdas recoge_material() del
			//transitable con pasarle el inventario le suma el
			//material del suelo.
			this->empresa_constructora->recolectar_recursos(
			    this->jugadores.consulta(this->jugador_activo));
			break;
		case MOVERSE:
			this -> empresa_constructora -> mover_jugador(this -> jugadores.consulta(this -> jugador_activo));
			break;
		case FIN_TURNO:
			cout << "Turno del jugador " << this->jugador_activo
			     << " finalizado." << endl;
			this->jugadores.consulta(this->jugador_activo)
			    ->recuperar_energia(ENERGIA_SUMADA_FIN_TURNO);
			this->jugador_activo = 3 - this->jugador_activo;  // Cambio de jugador activo
			break;
		case GUARDAR_SALIR:
			fin = true;
			break;
	}
	this->objetivos_jugadores.consulta(this->jugador_activo)
	    ->actualizar_objetivos();
	this -> empresa_constructora -> producir_materiales(jugadores.consulta(jugador_activo));
	return fin;
}

void Programa::comenzar_partida(){
	this -> empresa_constructora -> mostrar_mapa(jugadores);
	this -> empresa_constructora -> iniciar_coordenadas_jugador(this -> jugadores.consulta(1));
	this -> empresa_constructora -> iniciar_coordenadas_jugador(this -> jugadores.consulta(2));
	cout << "Comienza la partida!" << endl;
	this -> instancia = JUEGO;
	this -> jugadores.consulta(1) -> recuperar_energia(
	    ENERGIA_INICIAL);
	this -> jugadores.consulta(2) -> recuperar_energia(
	    ENERGIA_INICIAL);
	this -> empresa_constructora -> lluvia_de_recursos();
}

bool Programa::es_opcion_valida(std::string opcion) {
	bool valida = true;
	if (!es_numero(opcion))
		valida = false;
	else if (this->instancia == INICIO)
		valida = (stoul(opcion) >= OPCION_MINIMA_INICIO &&
			  stoul(opcion) <= OPCION_MAXIMA_INICIO);
	else
		valida = (stoul(opcion) >= OPCION_MINIMA_JUEGO &&
			  stoul(opcion) <= OPCION_MAXIMA_JUEGO);
	return valida;
}

void Programa::limpiar_pantalla() { Printer::clear_screen(); }

void Programa::guardar_archivos(std::string ruta_ubicaciones, std::string ruta_materiales, std::string ruta_edificios) {
	std::ofstream fout_1(ruta_ubicaciones);
	if(fout_1.is_open()){
		fout_1 << empresa_constructora -> estado_actual_ubicaciones(jugadores);
	}else	std::cout << "Ubicacion error" << std::endl;


	std::ofstream fout_2(ruta_materiales);
	if(fout_2.is_open()){
		fout_2 << estado_actual_materiales_jugadores();
	}else	std::cout << "materiales error" << std::endl;
	
	std::ofstream fout_3(ruta_edificios);
	if(fout_3.is_open()){
		fout_3 << empresa_constructora -> estado_actual_planos();
	}else	std::cout << "planos error" << std::endl;
	
}


std::string Programa::estado_actual_materiales_jugadores(){
	std::string texto = "";
	Lista<Material> inventario = jugadores.consulta(1)->obtener_inventario().obtener_materiales();
	Material material;
	for(std::size_t i = 1; i <= inventario.consulta_largo(); i++){
		material = inventario.consulta(i);
		texto += material.obtener_nombre();
		texto += " ";
		for(std::size_t j = 1; j <= jugadores.consulta_largo(); j++){
				inventario = jugadores.consulta(j)->obtener_inventario().obtener_materiales();
				texto += std::to_string(inventario.consulta(i).obtener_cantidad());
				texto += " ";
		}
		if(i != inventario.consulta_largo()) texto += "\n";
	}
	return texto;
}