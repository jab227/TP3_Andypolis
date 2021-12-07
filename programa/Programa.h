#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include "../empresa/EmpresaConstructora.h"
#include "../jugador/Jugador.h"
#include "../utils/Lista.h"

enum Instancia {INICIO, JUEGO};
const int JUGADOR_UNO = 1, JUGADOR_DOS = 2;

class Programa {
//Atributos:
private:
	Empresa_Constructora* empresa_constructora;
	Instancia instancia;
	size_t jugador_activo;
	Lista<Jugador*> jugadores;
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
	bool procesar_opcion(int opcion_elegida);

	//PRE: -
	//POST: devuelve si la opcion ingresada es valida segun si es el inicio o dentro del juego
	bool es_opcion_valida(std::string opcion);

	//PRE: -
	//POST: se limpia la pantalla
	void limpiar_pantalla();

	//PRE: las rutas deben ser a archivos existentes
	//POST: se guardan los cambios modificados
	void guardar_archivos(std::string ruta_materiales, std::string ruta_ubicaciones);

private:
	//PRE: -
	//POST: muestra el menu del juego por terminal
	void mostrar_menu_juego();

	//PRE: -
	//POST: muestra el menu de inicio de partida por terminal
	void mostrar_menu_inicio();

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada
	bool procesar_opcion_juego(int opcion_elegida);

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada
	bool procesar_opcion_inicio(int opcion_elegida);
};

#endif /* PROGRAMA_H_ */
