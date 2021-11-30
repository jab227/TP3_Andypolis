#include "Programa.h"

#include "LecturaArchivos.h"

const int CONSTRUIR = 1, LISTAR_CONSTRUIDOS = 2, LISTAR_EDIFICIOS = 3, DEMOLER = 4,
		  MOSTRAR_MAPA = 5, CONSULTAR = 6, LISTAR_MATERIALES = 7, RECOLECTAR = 8,
		  LLUVIA = 9, VACIAR_MAPA = 10, GUARDAR_SALIR = 11;
const int OPCION_MINIMA = CONSTRUIR, OPCION_MAXIMA = GUARDAR_SALIR;

Programa::Programa(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaciones) {
	this -> empresa_constructora = new Empresa_Constructora(ruta_materiales, ruta_edificios, ruta_mapa, ruta_ubicaciones);

}

Programa::~Programa() {
	delete this -> empresa_constructora;
}

void Programa::mostrar_menu(){
	cout << "--------------------------------------------------------------" <<endl;
	cout << "Elija una de las siguientes opciones ingresando solo el numero" << endl;
    cout << "1. Construir edificio por nombre." << endl;
    cout << "2. Listar edificios construidos." << endl;
	cout << "3. Listar todos los edificios." << endl;
	cout << "4. Demoler un edificio por coordenada." << endl;
	cout << "5. Mostrar mapa."  << endl;
	cout << "6. Consultar coordenada."  << endl;
	cout << "7. Mostrar inventario."  << endl;
	cout << "8. Recolectar recursos producidos."  << endl;
	cout << "9. Lluvia de recursos."  << endl;
	cout << "10. Eliminar materiales del mapa." << endl;
	cout << "11. Guardar y salir." << endl;
	cout << "--------------------------------------------------------------" <<endl;
}

bool Programa::procesar_opcion(int opcion_elegida) {
	bool fin = false;
    switch (opcion_elegida) {
        case CONSTRUIR:
            this -> empresa_constructora -> construir_edificio();
            break;
        case LISTAR_CONSTRUIDOS:
            this -> empresa_constructora -> mostrar_construidos();
            break;
        case LISTAR_EDIFICIOS:
            this -> empresa_constructora -> mostrar_edificios();
            break;
        case DEMOLER:
            this -> empresa_constructora -> demoler_edificio();
            break;
        case MOSTRAR_MAPA:
        	this -> empresa_constructora -> mostrar_mapa();
			break;
        case CONSULTAR:
			this -> empresa_constructora -> mostrar_coordenada();
			break;
        case LISTAR_MATERIALES:
			this -> empresa_constructora -> mostrar_materiales();
			break;
        case RECOLECTAR:
			this -> empresa_constructora -> producir_recursos();
			break;
        case LLUVIA:
			this -> empresa_constructora -> lluvia_de_recursos();
			break;
        case VACIAR_MAPA:
			this -> empresa_constructora -> vaciar_materiales();
			break;
        case GUARDAR_SALIR:
        	fin = true;
			cout << "Adios!"<< endl;
			break;
    }
    return fin;
}

bool Programa::es_opcion_valida(string opcion) {
	bool valida = true;
	if(!es_numero(opcion))
		valida = false;
	else
		valida = (stoi(opcion) >= OPCION_MINIMA && stoi(opcion) <= OPCION_MAXIMA);
    return valida;
}

void Programa::limpiar_pantalla(){
    system("cls||clear");
    cout << "--------------------------------------------------------------" <<endl;
}

void Programa::guardar_archivos(string ruta_materiales, string ruta_ubicaciones){
	this -> empresa_constructora -> guardar_archivos(ruta_materiales, ruta_ubicaciones);
}
