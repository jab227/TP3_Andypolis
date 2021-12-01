#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include "../empresa/EmpresaConstructora.h"

class Programa {
//Atributos:
private:
	Empresa_Constructora* empresa_constructora;
//Metodos:
public:
	//PRE: las rutas deben ser a archivos existentes y bien formados
	//POST: se carga el programa con los archivos de las rutas
	Programa(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaciones);

	//PRE: -
	//POST: se libera la memoria utilizada
	~Programa();

	//PRE: -
	//POST: muestra el menu por terminal
	void mostrar_menu();

	//PRE: la opcion debe ser valida
	//POST: se pocesa la opcion ingresada
	bool procesar_opcion(int opcion_elegida);

	//PRE: -
	//POST: devuelve si la opcion ingresada es valida
	bool es_opcion_valida(string opcion);

	//PRE: -
	//POST: se limpia la pantalla
	void limpiar_pantalla();

	//PRE: las rutas deben ser a archivos existentes
	//POST: se guardan los cambios modificados
	void guardar_archivos(string ruta_materiales, string ruta_ubicaciones);
};

#endif /* PROGRAMA_H_ */
