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

const string UBICACION_VACIA = " ", TIPO_TERRENO_VACIO = "";
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

bool Mapa::es_cordenada_valida(const Coordenada& coordenada){
	return (coordenada.x() < this -> filas && coordenada.y() < this -> columnas);
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
			//TODO: Corregir. Es necesario el indentificador? El edificio, material, etc, no podrian tener su icono?
			//RTA: Yo lo hice que cada edif y mat tiene nombre y para el identif uso un traduct. se puede cambiar el traductor o agregar un identif a cada mat/edif.
			cout << this -> terreno[filas][columnas] -> obtener_color() << ' '
					<< this -> identificador_ocupados(this -> terreno[filas][columnas] -> obtener_contenido()) << ' ';
		}
		cout << endl << FIN_COLOR;
	}
	cout << FIN_COLOR;
}

void Mapa::mostrar_posicion(const Coordenada& coordenada){
	this -> terreno[coordenada.x()][coordenada.y()] -> saludar();
}

bool Mapa::construir_edificio_ubicacion(Edificio* edificio, const Coordenada& coordenada){
	//Fuera el mapa debemos agregar la coordenada de la lista del jugador? O dentro?
	std::size_t propietario = 1; //TODO: Corregir.
	edificio = traductor_edificios(edificio->obtener_nombre(), 0, 0, 0, 0, propietario);
	return this -> terreno[coordenada.x()][coordenada.y()] -> construir_edificio(edificio);
}

string Mapa::demoler_edificio_ubicacion(const Coordenada& coordenada){
	//Fuera el mapa debemos eliminar la coordenada de la lista del jugador? O dentro?
	std::string edificio_demolido = (this -> terreno[coordenada.x()][coordenada.y()]) -> demoler_edificio();
	return edificio_demolido;
}

//TODO: Si castea es porque antes pregunto que casillero. Rompe el Tell Don't Ask.
void Mapa::poner_material_ubicacion(string material,const Coordenada& coordenada){
	( (Casillero_Transitable*) this -> terreno[coordenada.x()][coordenada.y()] ) ->
			agregar_material(traductor_materiales(material, 0));
}

//OBS: Si es casillero Construible, solo recoge el producto. Si es Transitable recoge y libera memoria.
void Mapa::recolectar_material_ubicacion(const Coordenada& coordenada, Almacen* inventario){
	 this -> terreno[coordenada.x()][coordenada.y()] -> recoger_material(inventario);
}

//WHY: Se usa?
string Mapa::obtener_contenido_ubicacion(const Coordenada& coordenada) const{
	string contenido = CONTENIDO_VACIO;
	//Depende para que lo usemos. Hay una sobrecarga de obtener_contenido. Una para edificios y otra para materiales.
	//contenido = terreno[coordenada.x()][coordenada.y()] -> obtener_contenido();
	return contenido;
}

//TODO: REVISAR que no haya hecho cagadas con la logica.
bool Mapa::generar_materiales_aleatorios(){
	//Chequea cuando casilleros libres y transitables hay. Hace una lista.
	Lista<Coordenada>* casilleros_libres = new Lista<Coordenada>;
	casilleros_libres_transitables(casilleros_libres);
	//Genera los numeros aleatorios dentro de los rangos [MINIMO,MAXIMO]
	std::size_t piedra_a_generar = this -> numero_aleatorio(PIEDRA_MINIMO, PIEDRA_MAXIMO);
	std::size_t madera_a_generar = this -> numero_aleatorio(MADERA_MINIMO, MADERA_MAXIMO);
	std::size_t metal_a_generar = this -> numero_aleatorio(METAL_MINIMO, METAL_MAXIMO);
	std::size_t a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar);
	std::size_t n_casillero = 0;
	bool mapa_ocupado = casilleros_libres->vacia();
	while(a_generar > 0 && !(casilleros_libres->vacia())){
		if((piedra_a_generar > 0)){
			n_casillero = this -> numero_aleatorio(1, casilleros_libres->consulta_largo());
			generar_material(MATERTIALES_EDIFICIOS[PIEDRA], casilleros_libres -> consulta(n_casillero));
			piedra_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		if((madera_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this -> numero_aleatorio(1, casilleros_libres->consulta_largo());
			generar_material(MATERTIALES_EDIFICIOS[MADERA], casilleros_libres->consulta(n_casillero));
			madera_a_generar--;
			casilleros_libres -> baja(n_casillero);

		}
		if((metal_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this->numero_aleatorio(1,casilleros_libres->consulta_largo());
			generar_material(MATERTIALES_EDIFICIOS[METAL], casilleros_libres->consulta(n_casillero));
			metal_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar);
		mapa_ocupado = casilleros_libres -> vacia();
	}
	delete casilleros_libres;
	return mapa_ocupado;
}

void Mapa::generar_material(string material, Coordenada coordenada){
	this -> poner_material_ubicacion(material, coordenada);	
}

std::size_t Mapa::numero_aleatorio(std::size_t minimo, std::size_t maximo){
	std::size_t numero = rand() % (maximo - minimo + 1) + minimo;
	return numero;
}

//TODO:Quitarme la dependencia. TellDontAsk.
//TODO: Constructor de copia?? Asi no lo creamos fuera a la lista.
void Mapa::casilleros_libres_transitables(Lista<Coordenada>* &lista_desocupados){
	for(std::size_t fila = 0; fila <  this -> filas; fila++)
		for(std::size_t columna = 0; columna < this -> columnas; columna++)
			if(this -> terreno[fila][columna] -> es_casillero_transitable() && !this -> terreno[fila][columna] -> esta_ocupado())
				lista_desocupados -> alta_al_final(Coordenada(fila, columna));
}

//OBS: Va a juntar todos los materiales del piso pero tmb los productos. 
//OBS2: solamente estaba para sacar los materiales si el mapa se llenaba, es inutil en este tp
void Mapa::vaciar_materiales(){
	Almacen * materiales_basura = new Almacen();
	Coordenada coordenada = Coordenada(0,0);
	for(std::size_t fila = 0; fila < this -> filas; fila++)
		for(std::size_t columna = 0; columna < this -> columnas; columna++){
			coordenada =  Coordenada(fila,columna);
			recolectar_material_ubicacion(coordenada, materiales_basura);
		}
	delete materiales_basura;
}

//TODO: Modificar la logica para que no sea necesario.
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
