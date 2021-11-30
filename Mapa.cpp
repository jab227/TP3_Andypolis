#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include "Casillero/CasilleroConstruible.h"
#include "Casillero/CasilleroInaccesible.h"
#include "Casillero/CasilleroTransitable.h"
#include "Casillero.h"
#include "LecturaArchivos.h"

const string UBICACION_VACIA = "X", TIPO_TERRENO_VACIO = "";
const int PIEDRA_MINIMO = 1, PIEDRA_MAXIMO = 2;
const int MADERA_MINIMO = 0, MADERA_MAXIMO = 1;
const int METAL_MINIMO = 2, METAL_MAXIMO = 4;

Mapa::Mapa(string ruta) {
	this -> columnas = 0;
	this -> filas = 0;
	this -> terreno = nullptr;
	this -> cargar_terreno(ruta);
	srand((unsigned int) time(0)); 						//Genero una semilla aleatoria
}

Mapa::~Mapa() {
	for(int i = 0; i < this -> filas; i++){
		for(int j = 0; j < this -> columnas; j++){
			delete this -> terreno[i][j];
		}
		delete [] this -> terreno[i];
	}
	delete [] this -> terreno;
}

void Mapa::cargar_terreno(string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		getline(archivo, lectura, ENTER);
		cargar_fila_columna(lectura, this -> filas, this -> columnas);
		this -> terreno = new Casillero** [this -> filas];
        for(int i = 0; i < this -> filas; i++){
            getline(archivo, lectura, ENTER);
            this -> iniciar_filas_casilleros(i,  lectura);
        }
        archivo.close();
    }
    
}

void Mapa::iniciar_filas_casilleros(int filas, string lectura){
	this -> terreno[filas] = new Casillero* [this -> columnas];
	for(int columnas = 0; columnas < this -> columnas; columnas++){
        this -> terreno[filas][columnas] = traductor_casillero(lectura[2*columnas]);
	}
}


bool Mapa::es_cordenada_valida(int fila, int columna){
	return fila < this -> filas && columna < this -> columnas;
}

Resultado_Chequeos Mapa::chequeo_ubicar_edificio(int fila, int columna){
	Resultado_Chequeos resultado = EXITO;
	if(!this -> es_cordenada_valida(fila, columna))
		resultado = FUERA_RANGO;
	else if(!(this -> terreno[fila][columna] -> es_casillero_construible()))
		resultado = CASILLERO_NO_CONSTRUIBLE;
	else if(this -> terreno[fila][columna] -> esta_ocupado())
		resultado = CASILLERO_OCUPADO;
	return resultado;

}

Resultado_Chequeos Mapa::chequeo_demoler_edificio(int fila, int columna, string &edificio){
	Resultado_Chequeos resultado = EXITO;
	if(!this -> es_cordenada_valida(fila, columna))
		resultado = FUERA_RANGO;
	else if(!(this -> terreno[fila][columna] -> es_casillero_construible()))
		resultado = CASILLERO_NO_CONSTRUIBLE;
	else if(!this -> terreno[fila][columna] -> esta_ocupado())
		resultado = CASILLERO_LIBRE;
	else
		edificio = this -> terreno[fila][columna] -> obtener_contenido();
	return resultado;
}

void Mapa::mostrar_mapa(){
	cout << "El mapa del terreno es el siguiente:" << endl;
	cout << "   ";
	for(int columnas = 0; columnas < this -> columnas; columnas++)
		cout << ' ' << columnas/10 << ' ';
	cout << endl << "   ";
	for(int columnas = 0; columnas < this -> columnas; columnas++)
		cout << ' ' << columnas%10 << ' ';
	cout << endl;
	for(int filas = 0; filas < this -> filas; filas++){
		cout << filas/10 << filas%10 << ' ';
		for(int columnas = 0; columnas < this -> columnas; columnas++){
			cout << this -> terreno[filas][columnas] -> obtener_color() << ' '
					<< this -> identificador_ocupados(this -> terreno[filas][columnas] -> obtener_contenido()) << ' ';
		}
		cout << endl << FIN_COLOR;
	}
	cout << FIN_COLOR;
}

void Mapa::mostrar_construidos(){
	Lista<string> lista_nombres;
	Lista<Lista<int*>*> lista_coordenadas;
	int* coordenadas;
	for(int fila = 0; fila < this -> filas; fila++){
		for(int columna = 0; columna < this -> columnas; columna++){
			if(this -> terreno[fila][columna] -> es_casillero_construible() && this -> terreno[fila][columna] -> esta_ocupado()){
				coordenadas = new int[2];
				coordenadas[0] = fila;
				coordenadas[1] = columna;
				agregar_edificio_a_listas(this -> terreno[fila][columna], coordenadas, lista_nombres, lista_coordenadas);
			}
		}
	}
	this -> mostrar_edificios(lista_nombres, lista_coordenadas);
}

void Mapa::agregar_edificio_a_listas(Casillero* casillero, int* coordenadas, Lista<string> &lista_nombres, Lista<Lista<int*>*> &lista_coordenadas){
	Lista<int*>* auxiliar;
	string edificio = casillero -> obtener_contenido();
	int indice = lista_nombres.buscar_indice(edificio);
	if(indice == NO_ESTA){
		lista_nombres.alta_al_final(edificio);
		auxiliar = new Lista<int*>;
		lista_coordenadas.alta_al_final(auxiliar);
		indice = lista_nombres.consulta_largo();
	}
	lista_coordenadas.consulta(indice) -> alta_al_final(coordenadas);
}

void Mapa::mostrar_edificios(Lista<string> &lista_nombres, Lista<Lista<int*>*> &lista_coordenadas){
	if(lista_nombres.consulta_largo() > 0){
		int* coordenadas;
		cout << "|Edificio\t\t|Cantidad\t|Ubicaciones\t" << endl;
		for(int i = 1; ! lista_coordenadas.vacia(); i++){
			cout << '|' << lista_nombres.consulta(i) << espaciado(lista_nombres.consulta(i), 21)
					<< lista_coordenadas.consulta(1) -> consulta_largo() << "\t\t|";
			for(int j = 1; ! lista_coordenadas.consulta(1) -> vacia(); j++){
				coordenadas = lista_coordenadas.consulta(1) -> baja(1);
				cout << '(' << coordenadas[0] << ", " << coordenadas[1] << ") ";
				delete [] coordenadas;
			}
			cout << endl;
			delete lista_coordenadas.baja(1);
		}
	}else
		cout << "No hay ningun edificio construido en el mapa." << endl;
}

void Mapa::mostrar_posicion(int fila, int columna){
	this -> terreno[fila][columna] -> saludar();
}

void Mapa::construir_edificio_ubicacion(string edificio, int fila, int columna){
	( (Casillero_Construible*) this -> terreno[fila][columna] ) ->
			construir_edificio(traductor_edificios(edificio, 0, 0, 0, 0));
}

string Mapa::demoler_edificio_ubicacion(int fila, int columna){
	string edificio_demolido = this -> terreno[fila][columna] -> obtener_contenido();
	delete ( (Casillero_Construible*) this -> terreno[fila][columna] ) -> demoler_edificio();
	return edificio_demolido;
}

void Mapa::poner_material_ubicacion(string material, int fila, int columna){
	( (Casillero_Transitable*) this -> terreno[fila][columna] ) ->
			agregar_material(traductor_materiales(material, 0));
}
string Mapa::sacar_material_ubicacion(int fila, int columna){
	string material_quitado = this -> terreno[fila][columna] -> obtener_contenido();
	delete ( (Casillero_Transitable*) this -> terreno[fila][columna] ) -> eliminar_material();
	return material_quitado;
}
Resultado_Chequeos Mapa::chequeo_poner_material(int fila, int columna){
	Resultado_Chequeos resultado = EXITO;
	if(!this -> es_cordenada_valida(fila, columna))
		resultado = FUERA_RANGO;
	else if(!(this -> terreno[fila][columna] -> es_casillero_transitable()))
		resultado = CASILLERO_NO_TRANSITABLE;
	else if(this -> terreno[fila][columna] -> esta_ocupado())
		resultado = CASILLERO_OCUPADO;
	return resultado;
}
Resultado_Chequeos Mapa::chequeo_sacar_material(int fila, int columna){
	Resultado_Chequeos resultado = EXITO;
	if(!this -> es_cordenada_valida(fila, columna))
		resultado = FUERA_RANGO;
	else if(!(this -> terreno[fila][columna] -> es_casillero_transitable()))
		resultado = CASILLERO_NO_TRANSITABLE;
	else if(!this -> terreno[fila][columna] -> esta_ocupado())
		resultado = CASILLERO_LIBRE;
	return resultado;
}

string Mapa::obtener_contenido_ubicacion(int fila, int columna){
	string contenido = CONTENIDO_VACIO;
	if(this -> terreno[fila][columna] -> esta_ocupado())
		contenido = terreno[fila][columna] -> obtener_contenido();
	return contenido;
}

bool Mapa::generar_materiales_aleatorios(){
	int casilleros_libres = this -> casilleros_libres_transitables();
	int piedra_a_generar = this -> numero_aleatorio(PIEDRA_MINIMO, PIEDRA_MAXIMO);
	int madera_a_generar = this -> numero_aleatorio(MADERA_MINIMO, MADERA_MAXIMO);
	int metal_a_generar = this -> numero_aleatorio(METAL_MINIMO, METAL_MAXIMO);
	bool todo_ocupado = casilleros_libres == 0;
	while((piedra_a_generar + madera_a_generar + metal_a_generar) > 0 && casilleros_libres > 0){
		if(piedra_a_generar > 0 && casilleros_libres > 0){
			generar_material(MATERTIALES_EDIFICIOS[PIEDRA], numero_aleatorio(1, casilleros_libres));
			casilleros_libres--;
			piedra_a_generar--;
		}
		if(madera_a_generar > 0 && casilleros_libres > 0){
			generar_material(MATERTIALES_EDIFICIOS[MADERA], numero_aleatorio(1, casilleros_libres));
			casilleros_libres--;
			madera_a_generar--;
		}
		if(metal_a_generar > 0 && casilleros_libres > 0){
			generar_material(MATERTIALES_EDIFICIOS[METAL], numero_aleatorio(1, casilleros_libres));
			casilleros_libres--;
			metal_a_generar--;
		}
	}
	return todo_ocupado;
}

void Mapa::generar_material(string material, int numero_casillero){
	bool generado = false;
	int fila = 0, columna = 0;
	while(fila < this -> filas && !generado){
		while(columna < this -> columnas && !generado){
			if(this -> terreno[fila][columna] -> es_casillero_transitable() && !this -> terreno[fila][columna] -> esta_ocupado())
				numero_casillero--;
			if(numero_casillero == 0){
				this -> poner_material_ubicacion(material, fila, columna);
				generado = true;
			}
			columna++;
		}
		columna = 0;
		fila++;
	}
}

int Mapa::numero_aleatorio(int minimo, int maximo){
	int numero = rand() % (maximo - minimo + 1) + minimo;
	return numero;
}

int Mapa::casilleros_libres_transitables(){
	int casilleros_libres = 0;
	for(int fila = 0; fila <  this -> filas; fila++)
		for(int columna = 0; columna < this -> columnas; columna++)
			if(this -> terreno[fila][columna] -> es_casillero_transitable() && !this -> terreno[fila][columna] -> esta_ocupado())
				casilleros_libres++;

	return casilleros_libres;
}

void Mapa::vaciar_materiales(){
	for(int fila = 0; fila < this -> filas; fila++)
		for(int columna = 0; columna < this -> columnas; columna++){
			if(this -> terreno[fila][columna] -> es_casillero_transitable()
					&& this -> terreno[fila][columna] -> esta_ocupado())
				delete ( (Casillero_Transitable*) this -> terreno[fila][columna] ) -> eliminar_material();
		}
}

string Mapa::identificador_ocupados(string ocupador){
	string identificador = UBICACION_VACIA;
	if(ocupador == "mina")
		identificador = "M";
	else if(ocupador == "aserradero")
		identificador = "A";
	else if(ocupador == "fabrica")
		identificador = "F";
	else if(ocupador == "escuela")
		identificador = "E";
	else if(ocupador == "obelisco")
		identificador = "O";
	else if(ocupador == "planta electrica")
		identificador = "P";
	else if(ocupador == "madera")
		identificador = "W";
	else if(ocupador == "piedra")
		identificador = "S";
	else if(ocupador == "metal")
		identificador = "I";
	return identificador;
}
