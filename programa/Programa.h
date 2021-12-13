#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include "../empresa/EmpresaConstructora.h"
#include "../utils/LecturaArchivos.h"

#include "../jugador/Jugador.h"
#include "../utils/Lista.h"
#include "../meta/Meta.h"

enum Instancia {INICIO, JUEGO};
const int JUGADOR_UNO = 1, JUGADOR_DOS = 2;

class Programa {
//Atributos:
private:
	Empresa_Constructora* empresa_constructora;
	Instancia instancia;
	Partida partida;
	std::size_t jugador_activo;
	bool fin_ronda;
	Lista<Jugador*> jugadores;
	Lista<Meta*> objetivos_jugadores;
//Metodos:
public:
	//PRE: las rutas deben ser a archivos existentes y bien formados
	//POST: se carga el programa con los archivos de las rutas
	Programa(std::string ruta_materiales, std::string ruta_edificios, std::string ruta_mapa, std::string ruta_ubicaciones);

	//PRE: -
	//POST: se libera la memoria utilizada
	~Programa();

	//PRE: -
	//POST: muestra el menu del juego por terminal segun si es el inicio o en el juego
	void mostrar_menu();

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada segun si es el inicio o en el juego
	bool procesar_opcion(std::size_t opcion_elegida);

	//PRE: -
	//POST: devuelve si la opcion ingresada es valida segun si es el inicio o dentro del juego
	bool es_opcion_valida(std::string opcion);

	//PRE: -
	//POST: se limpia la pantalla
	void limpiar_pantalla();

	//PRE: las rutas deben ser a archivos existentes
	//POST: se guardan los cambios modificados
	void guardar_archivos(std::string ruta_ubicaciones, std::string ruta_materiales, std::string ruta_edificios);

private:
	//PRE: -
	//POST: muestra el menu del juego por terminal
	void mostrar_menu_juego();

	//PRE: -
	//POST: muestra el menu de inicio de partida por terminal
	void mostrar_menu_inicio();

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada
	bool procesar_opcion_juego(std::size_t opcion_elegida);

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada
	bool procesar_opcion_inicio(std::size_t opcion_elegida);

	//PRE: -
	//POST: se realizan inicializaciones del juego antes de iniciar por primera vez
	void comenzar_partida();

	//PRE: -
	//POS: True si se cumple alguna de las condiciones de victoria, False en otro
	//caso.
	bool victoria();

	//PRE: a > 0
	//POS: devuelve un numero aleatorio en el intervalo (a,b)
	std::size_t generar_numero_aleatorio(std::size_t a, std::size_t b);

	//PRE: -
	//POS: Inicializa los objetivo de cada jugador con 3 objetivos al azar.
	void inicializar_objetivos_jugadores(Mapa* mapa);

	std::string estado_actual_materiales_jugadores();
};

#endif /* PROGRAMA_H_ */
