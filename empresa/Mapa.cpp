#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"
#include "../Casillero/CasilleroTransitable.h"
#include "../Casillero/Casillero.h"
#include "../utils/LecturaArchivos.h"

const string UBICACION_VACIA = "X", TIPO_TERRENO_VACIO = "";
const std::size_t PIEDRA_MINIMO = 1, PIEDRA_MAXIMO = 2;
const std::size_t MADERA_MINIMO = 0, MADERA_MAXIMO = 1;
const std::size_t METAL_MINIMO = 2, METAL_MAXIMO = 4;

//TODO: Adaptar al parser.
Mapa::Mapa(string ruta) {
	this -> columnas = 0;
	this -> filas = 0;
	this -> terreno = nullptr;
	this -> cargar_terreno(ruta);
 
	srand((unsigned int) time(0)); 	//Genero una semilla aleatoria
}

Mapa::~Mapa() {
	for(std::size_t i = 0; i < this -> filas; i++){
		for(std::size_t j = 0; j < this -> columnas; j++){
			delete this -> terreno[i][j];
		}
		delete [] this -> terreno[i];
	}
	delete [] this -> terreno;
}

//TODO: Adaptar al parser.
void Mapa::cargar_terreno(string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		getline(archivo, lectura, ENTER);
		cargar_fila_columna(lectura, this -> filas, this -> columnas);
		this -> terreno = new Casillero** [this -> filas];
        for(std::size_t i = 0; i < this -> filas; i++){
            getline(archivo, lectura, ENTER);
            this -> iniciar_filas_casilleros(i,  lectura);
        }
        archivo.close();
    }
    
}

//TODO: Adaptar al parser.
void Mapa::iniciar_filas_casilleros(std::size_t filas, string lectura){
	this -> terreno[filas] = new Casillero* [this -> columnas];
	for(std::size_t columnas = 0; columnas < this -> columnas; columnas++){
        this -> terreno[filas][columnas] = traductor_casillero(lectura[2*columnas]);
	}
}


bool Mapa::es_cordenada_valida(std::size_t fila, std::size_t columna){
	return (fila < this -> filas && columna < this -> columnas);
}

void Mapa::mostrar_mapa(){
	cout << "Mapa:" << endl;
	cout << "   ";
	for(std::size_t columnas = 0; columnas < this -> columnas; columnas++)
		cout << ' ' << columnas/10 << ' ';
	cout << endl << "   ";
	for(std::size_t columnas = 0; columnas < this -> columnas; columnas++)
		cout << ' ' << columnas%10 << ' ';
	cout << endl;
	for(std::size_t filas = 0; filas < this -> filas; filas++){
		cout << filas/10 << filas%10 << ' ';
		for(std::size_t columnas = 0; columnas < this -> columnas; columnas++){
			cout << this -> terreno[filas][columnas] -> obtener_color() << ' '
					<< this -> identificador_ocupados(this -> terreno[filas][columnas] -> obtener_contenido()) << ' ';
		}
		cout << endl << FIN_COLOR;
	}
	cout << FIN_COLOR;
}

//TODO: Responsabilidad del jugador. 
void Mapa::mostrar_construidos(){
	Lista<string> lista_nombres;
	Lista<Lista<std::size_t*>*> lista_coordenadas;
	for(std::size_t fila = 0; fila < this -> filas; fila++){
		for(std::size_t columna = 0; columna < this -> columnas; columna++){
			//Dame el edificio. No es null pointer
			//De quien es la responsabilidad de agregarse a la lista?
			(this -> terreno[fila][columna]) -> agregar_lista_edificio(fila, columna, lista_nombres, lista_coordenadas);
		}
/*
void Mapa::mostrar_construidos(Jugador* jugador){
	Lista<string> lista_nombres;
	Lista<Lista<int*>*> lista_coordenadas;
	int* coordenadas;
	for(int i = 1; i <= jugador -> obtener_largo_ubicaciones(); i++){
		coordenadas = new int[2];
		jugador -> obtener_ubicacion(i, coordenadas[0], coordenadas[1]);
		agregar_edificio_a_listas(this -> terreno[coordenadas[0]][coordenadas[1]], coordenadas, lista_nombres, lista_coordenadas);
	}
	this -> mostrar_edificios(lista_nombres, lista_coordenadas);
}
*/

//TODO: Responsabilidad del jugador. 
void Mapa::mostrar_edificios(Lista<string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas){
	if(lista_nombres.consulta_largo() > 0){
		std::size_t* coordenadas;
		cout << "|Edificio\t\t|Cantidad\t|Ubicaciones\t" << endl;
		for(std::size_t i = 1; ! lista_coordenadas.vacia(); i++){
			cout << '|' << lista_nombres.consulta(i) << espaciado(lista_nombres.consulta(i), 21)
					<< lista_coordenadas.consulta(1) -> consulta_largo() << "\t\t|";
			for(std::size_t j = 1; ! lista_coordenadas.consulta(1) -> vacia(); j++){
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

void Mapa::mostrar_posicion(std::size_t fila, std::size_t columna){
	this -> terreno[fila][columna] -> saludar();
}

bool Mapa::construir_edificio_ubicacion(Edificio* edificio, std::size_t fila, std::size_t columna, size_t propietario){
	edificio = traductor_edificios(edificio->obtener_nombre(), 0, 0, 0, 0, propietario);
	return this -> terreno[fila][columna] -> construir_edificio(edificio);
}

string Mapa::demoler_edificio_ubicacion(std::size_t fila, std::size_t columna){
	std::string edificio_demolido = (this -> terreno[fila][columna]) -> demoler_edificio();
	return edificio_demolido;
}

//TODO: Si castea es porque antes pregunto que casillero. Rompe el Tell Don't Ask.
void Mapa::poner_material_ubicacion(string material, std::size_t fila, std::size_t columna){
	( (Casillero_Transitable*) this -> terreno[fila][columna] ) ->
			agregar_material(traductor_materiales(material, 0));
}

//TODO: Si castea es porque antes pregunto que casillero. Rompe el Tell Don't Ask.
string Mapa::sacar_material_ubicacion(std::size_t fila, std::size_t columna){
	string material_quitado = this -> terreno[fila][columna] -> obtener_contenido();
	delete ( (Casillero_Transitable*) this -> terreno[fila][columna] ) -> eliminar_material();
	return material_quitado;
}

string Mapa::obtener_contenido_ubicacion(std::size_t fila, std::size_t columna){
	string contenido = CONTENIDO_VACIO;
	if(this -> terreno[fila][columna] -> esta_ocupado())
		contenido = terreno[fila][columna] -> obtener_contenido();
	return contenido;
}

bool Mapa::generar_materiales_aleatorios(){
	//Chequea cuando casilleros libres y transitables hay.
	std::size_t casilleros_libres = this -> casilleros_libres_transitables();
	//Genera los numeros aleatorios dentro de los rangos [MINIMO,MAXIMO]
	std::size_t piedra_a_generar = this -> numero_aleatorio(PIEDRA_MINIMO, PIEDRA_MAXIMO);
	std::size_t madera_a_generar = this -> numero_aleatorio(MADERA_MINIMO, MADERA_MAXIMO);
	std::size_t metal_a_generar = this -> numero_aleatorio(METAL_MINIMO, METAL_MAXIMO);
	std::size_t a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar);

	while(a_generar > 0 && (casilleros_libres > 0)){
		if((piedra_a_generar > 0) && (casilleros_libres > 0)){
			generar_material(MATERTIALES_EDIFICIOS[PIEDRA], numero_aleatorio(1, casilleros_libres));
			piedra_a_generar--;
			casilleros_libres--;
		}
		if((madera_a_generar > 0) && (casilleros_libres > 0)){
			generar_material(MATERTIALES_EDIFICIOS[MADERA], numero_aleatorio(1, casilleros_libres));
			madera_a_generar--;
			casilleros_libres--;
		}
		if((metal_a_generar > 0) && (casilleros_libres > 0)){
			generar_material(MATERTIALES_EDIFICIOS[METAL], numero_aleatorio(1, casilleros_libres));
			metal_a_generar--;
			casilleros_libres--;
		}
		//TODO: Ver como utiliza el boolean que retorna.
		a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar);
	}

	return (casilleros_libres == 0);
}

//TODO:Quitarme la dependencia. TellDontAsk
void Mapa::generar_material(string material, std::size_t numero_casillero){
	bool generado = false;
	std::size_t fila = 0, columna = 0;
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

std::size_t Mapa::numero_aleatorio(std::size_t minimo, std::size_t maximo){
	std::size_t numero = rand() % (maximo - minimo + 1) + minimo;
	return numero;
}

//TODO:Quitarme la dependencia. TellDontAsk
std::size_t Mapa::casilleros_libres_transitables(){
	std::size_t casilleros_libres = 0;
	for(std::size_t fila = 0; fila <  this -> filas; fila++)
		for(std::size_t columna = 0; columna < this -> columnas; columna++)
			if(this -> terreno[fila][columna] -> es_casillero_transitable() && !this -> terreno[fila][columna] -> esta_ocupado())
				casilleros_libres++;

	return casilleros_libres;
}

void Mapa::vaciar_materiales(){
	for(std::size_t fila = 0; fila < this -> filas; fila++)
		for(std::size_t columna = 0; columna < this -> columnas; columna++){
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
	else if(ocupador == "mina oro")
		identificador = "G";
	return identificador;
}
