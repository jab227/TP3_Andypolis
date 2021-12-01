#include <iostream>

#include "utils/LecturaArchivos.h"
#include "programa/Programa.h"


const string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

//PRE: programa tiene que ser un objeto bien cargado
//POST: se pide al usuario una opcion valida
int pedir_opcion_valida(Programa &programa);

//PRE: programa tiene que ser un objeto bien cargado
//POST: imprime un mensaje de bienvenida
void mensaje_bienvenida(Programa &programa);

int main() {
	Programa programa(RUTA_MATERIALES, RUTA_EDIFICIOS, RUTA_MAPA, RUTA_UBICACIONES);
	int opcion;

	mensaje_bienvenida(programa);
	do{
		programa.mostrar_menu();
		opcion = pedir_opcion_valida(programa);
		programa.limpiar_pantalla();
	}while(!programa.procesar_opcion(opcion));
	programa.guardar_archivos(RUTA_MATERIALES, RUTA_UBICACIONES);
	return 0;
}

void mensaje_bienvenida(Programa &programa){
	programa.limpiar_pantalla();
	cout << "Bienvenido!" << endl;
}

int pedir_opcion_valida(Programa &programa){
	string opcion;

	cout << "Opcion:   " ;
	getline(cin, opcion);
	while(!programa.es_opcion_valida(opcion)){
		cout << "La opcion ingresada no es valida." << endl;
		cout << "Opcion:   " ;
		getline(cin, opcion);
	}
	return stoi(opcion);
}
