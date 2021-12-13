#include "Programa.h"

#include <random>
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

// Opciones Menu de juego.
const std::size_t CONSTRUIR = 1; 
const std::size_t LISTAR_CONSTRUIDOS = 2;
const std::size_t DEMOLER = 3; 
const std::size_t ATACAR = 4;
const std::size_t REPARAR = 5;
const std::size_t COMPRAR_BOMBAS = 6; 
const std::size_t CONSULTAR = 7; 
const std::size_t LISTAR_MATERIALES = 8;
const std::size_t OBJETIVOS = 9; 
const std::size_t RECOLECTAR = 10; 
const std::size_t MOVERSE = 11; 
const std::size_t FIN_TURNO = 12;
const std::size_t GUARDAR_SALIR = 13;
const std::size_t OPCION_MINIMA_JUEGO = CONSTRUIR;
const std::size_t OPCION_MAXIMA_JUEGO = GUARDAR_SALIR;
// Opciones Menu de inicio
const std::size_t MODIFICAR_EDIFICIO = 1; 
const std::size_t LISTAR_EDIFICIOS = 2; 
const std::size_t MOSTRAR_MAPA = 3;
const std::size_t COMENZAR = 4; 
const std::size_t GUARDAR_SALIR_INICIO = 5;
const std::size_t OPCION_MINIMA_INICIO = MODIFICAR_EDIFICIO;
const std::size_t OPCION_MAXIMA_INICIO = GUARDAR_SALIR_INICIO;
// Valores iniciales energia
const std::size_t ENERGIA_INICIAL = 50;
const std::size_t ENERGIA_SUMADA_FIN_TURNO = 20;
const std::size_t ENERGIA[] = {
				0,
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
		       ENERGIA_GUARDAR_SALIR
	};

Programa::Programa(std::string ruta_materiales, std::string ruta_edificios,
		   std::string ruta_mapa, std::string ruta_ubicaciones)
    : empresa_constructora(nullptr),
	  partida(NUEVA),
      jugador_activo(0),
      fin_ronda(false),
      jugadores(Lista<Jugador*>()),
      objetivos_jugadores(Lista<Meta*>()) {
	Planos* plano =
	    new Planos(leer_de_archivo(ruta_edificios, ParserEdificio()));
	Mapa* mapa = leer_de_archivo(ruta_mapa, ParserMapa());
	partida = leer_de_archivo(ruta_ubicaciones, ParserUbicacion(), mapa, jugadores);
	empresa_constructora = new Empresa_Constructora(plano, mapa);
	leer_de_archivo(ruta_materiales, ParserInventario(), jugadores, partida);
	inicializar_objetivos_jugadores(mapa);
	jugador_activo = generar_numero_aleatorio(1, 2);
}

Programa::~Programa() {
	delete empresa_constructora;
	while (!objetivos_jugadores.vacia()) delete objetivos_jugadores.baja(1);
	while (!jugadores.vacia()) delete jugadores.baja(1);
}

void Programa::mostrar_menu_juego() const {
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

void Programa::mostrar_menu_inicio() const {
	cout << "--------------------------------------------------------------"
	     << endl;
	cout << "Elija una de las siguientes opciones ingresando solo el numero"
	     << endl;
	cout << "1. Modificar edificio por nombre." << endl;
	cout << "2. Listar todos los edificios." << endl;
	cout << "3. Mostrar mapa." << endl;
	if (partida == NUEVA) 
		cout << "4. Comenzar partida." << endl;
	else 
		cout << "4. Continuar partida." << endl;
	cout << "5. Guardar y salir." << endl;
	cout << "--------------------------------------------------------------"
	     << endl;
}

bool Programa::es_energia_suficiente(std::size_t opcion) const {
	return jugadores.consulta(jugador_activo)->es_energia_suficiente(ENERGIA[opcion]);
}

Salida Programa::procesar_opcion_inicio(std::size_t opcion_elegida) const {
	Salida salida = CONTINUAR;
	switch (opcion_elegida) {
		case MODIFICAR_EDIFICIO:
			limpiar_pantalla();
			empresa_constructora->modificar_edificios();
		case LISTAR_EDIFICIOS:
			empresa_constructora->mostrar_edificios();
			break;
		case MOSTRAR_MAPA:
			empresa_constructora->mostrar_mapa(jugadores);
			break;
		case COMENZAR:
			this -> comenzar_partida();
			salida = COMENZAR_JUEGO;
			break;
		case GUARDAR_SALIR_INICIO:
			salida = GUARDAR_Y_SALIR;
			break;
	}
	return salida;
}

Salida Programa::procesar_opcion_juego(std::size_t opcion_elegida)  {
	Salida salida = CONTINUAR;
	switch (opcion_elegida) {
		case CONSTRUIR:
			empresa_constructora->construir_edificio(
			    jugadores.consulta(
				jugador_activo));
			break;
		case LISTAR_CONSTRUIDOS:
			empresa_constructora->mostrar_construidos(
			    jugadores.consulta(
				jugador_activo));
			break;
		case DEMOLER:
			empresa_constructora->demoler_edificio(
			    jugadores.consulta(
				jugador_activo));
			break;
		case ATACAR:
			this->empresa_constructora->atacar_edificio(jugadores.consulta(jugador_activo), jugadores.consulta(3 - jugador_activo));
			break;
		case REPARAR:
			empresa_constructora->reparar_edificio(
			    jugadores.consulta(jugador_activo));
			break;
		case COMPRAR_BOMBAS:
			empresa_constructora->comprar_bombas(
			    jugadores.consulta(jugador_activo));
			break;
		case CONSULTAR:
			empresa_constructora->consultar_coordenada(jugadores.consulta(jugador_activo), jugadores.consulta(3 - jugador_activo));
			break;
		case LISTAR_MATERIALES:
			jugadores.consulta(jugador_activo) -> mostrar_inventario();
			break;
		case OBJETIVOS:
			objetivos_jugadores.consulta(jugador_activo)
			    ->mostrar_objetivos();
			break;
		case RECOLECTAR:
			empresa_constructora->recolectar_recursos(
			    jugadores.consulta(jugador_activo));
			break;
		case MOVERSE:
			this -> empresa_constructora -> mover_jugador(this -> jugadores.consulta(this -> jugador_activo));
			break;
		case FIN_TURNO:
			std::cout << "Turno del jugador " << jugador_activo << " finalizado." << endl;
			jugadores.consulta(this->jugador_activo) -> recuperar_energia(ENERGIA_SUMADA_FIN_TURNO);
			empresa_constructora -> producir_materiales(jugadores.consulta(jugador_activo));
			jugador_activo = 3 - jugador_activo;  // Cambio de jugador activo
			if(fin_ronda) empresa_constructora -> lluvia_de_recursos(jugadores.consulta(1) -> obtener_posicion(), jugadores.consulta(2) -> obtener_posicion()); 
			fin_ronda = !fin_ronda;
			break;
		case GUARDAR_SALIR:
			salida = GUARDAR_Y_SALIR;
			break;
	}
	objetivos_jugadores.consulta(jugador_activo)
	    ->actualizar_objetivos();
	return victoria() ? VICTORIA : salida;
}

void Programa::comenzar_partida() const {
  this -> empresa_constructora -> mostrar_mapa(jugadores);
	if (partida == NUEVA) {
		this -> empresa_constructora -> iniciar_coordenadas_jugador(this -> jugadores.consulta(1));
		this -> empresa_constructora -> iniciar_coordenadas_jugador(this -> jugadores.consulta(2));
	}
	cout << "Comienza la partida!" << endl;
	this -> jugadores.consulta(1) -> recuperar_energia(
	    ENERGIA_INICIAL);
	this -> jugadores.consulta(2) -> recuperar_energia(
	    ENERGIA_INICIAL);
	this -> empresa_constructora -> lluvia_de_recursos(jugadores.consulta(1) -> obtener_posicion(), jugadores.consulta(2) -> obtener_posicion());
}

bool Programa::es_opcion_valida_inicio(std::string opcion) const {
	bool valida = true;
	if (!es_numero(opcion))
		valida = false;
	else
		valida = (stoul(opcion) >= OPCION_MINIMA_INICIO &&
			  stoul(opcion) <= OPCION_MAXIMA_INICIO);
	return valida;
}
bool Programa::es_opcion_valida_juego(std::string opcion) const {
	bool valida = true;
	if (!es_numero(opcion))
		valida = false;
	else
		valida = (stoul(opcion) >= OPCION_MINIMA_JUEGO &&
			  stoul(opcion) <= OPCION_MAXIMA_JUEGO);
	return valida;
}

void Programa::limpiar_pantalla() const { Printer::clear_screen(); }

bool Programa::victoria() {
	// Es muy chico para ser un metodo, es solo para facilitar
	// lectura.
	auto chequear = [] (bool a, bool b, bool c) {
		return ((a && b) || (a && c) || (b && c));
	};
	Lista <Objetivo*> objetivos = objetivos_jugadores.consulta(jugador_activo)->obtener_objetivos();
	bool objetivos_cumplidos = chequear(objetivos.consulta(1)->esta_cumplido(), 
										objetivos.consulta(2)->esta_cumplido(), 
										objetivos.consulta(3)->esta_cumplido());
	bool obelisco_construido = objetivos.consulta(4)->esta_cumplido();
	return (objetivos_cumplidos || obelisco_construido);
}

std::size_t Programa::generar_numero_aleatorio(std::size_t a, std::size_t b) {
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> rango(a, b);
	return rango(rng);
}

void Programa::inicializar_objetivos_jugadores(Mapa* mapa) {
	objetivos_jugadores.alta_al_final(new Meta(jugadores.consulta(1), mapa));
	objetivos_jugadores.alta_al_final(new Meta(jugadores.consulta(2), mapa));
}

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
	
	fout_1.close();
	fout_2.close();
	fout_3.close();
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