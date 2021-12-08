#include "Mapa.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

#include "../Casillero/Casillero.h"
#include "../Casillero/CasilleroConstruible.h"
#include "../Casillero/CasilleroInaccesible.h"
#include "../Casillero/CasilleroTransitable.h"
#include "../utils/LecturaArchivos.h"

const std::string UBICACION_VACIA = " ", TIPO_TERRENO_VACIO = "";
const std::size_t PIEDRA_MINIMO = 1, PIEDRA_MAXIMO = 2;
const std::size_t MADERA_MINIMO = 0, MADERA_MAXIMO = 1;
const std::size_t METAL_MINIMO = 2, METAL_MAXIMO = 4;

Mapa::Mapa(const std::string& mapa, std::size_t filas, std::size_t columnas)
    : filas(filas), columnas(columnas), terreno(nullptr) {
	this->cargar_terreno(mapa);
	srand((unsigned int)time(0));  // Genero una semilla aleatoria
}

Mapa::~Mapa() {
	for (std::size_t i = 0; i < this->filas; i++) {
		for (std::size_t j = 0; j < this->columnas; j++) {
			delete this->terreno[i][j];
		}
		delete[] this->terreno[i];
	}
	delete[] this->terreno;
}

void Mapa::cargar_terreno(const std::string& mapa) {
	this->terreno = new Casillero**[this->filas];
	for (std::size_t fila = 0; fila < this->filas; fila++) {
		this->iniciar_filas_casilleros(fila, mapa);
	}
}

void Mapa::iniciar_filas_casilleros(std::size_t fila, const std::string& mapa) {
	this->terreno[filas] = new Casillero*[this->columnas];
	for (std::size_t columnas = 0; columnas < this->columnas; columnas++) {
		this->terreno[filas][columnas] =
		    traductor_casillero(mapa[columnas]);
	}
}

bool Mapa::es_cordenada_valida(const Coordenada& coordenada) {
	return (coordenada.x() < this->filas && coordenada.y() < this->columnas);
}

void Mapa::mostrar_mapa() {
	cout << "Mapa:" << endl;
	cout << "   ";
	for (std::size_t columnas = 0; columnas < this->columnas; columnas++)
		cout << ' ' << columnas / 10 << ' ';
	cout << endl << "   ";
	for (std::size_t columnas = 0; columnas < this->columnas; columnas++)
		cout << ' ' << columnas % 10 << ' ';
	cout << endl;
	for (std::size_t filas = 0; filas < this->filas; filas++) {
		cout << filas / 10 << filas % 10 << ' ';
		for (std::size_t columnas = 0; columnas < this->columnas;
		     columnas++) {
			cout << this->terreno[filas][columnas]->obtener_color()
			     << ' '
			     << this->identificador_ocupados(
				    this->terreno[filas][columnas]
					->obtener_contenido())
			     << ' ';
		}
		std::cout << std::endl << FIN_COLOR;
	}
	std::cout << FIN_COLOR;
}

void Mapa::saludar_coordenada(const Coordenada& coordenada){
	this -> terreno[coordenada.x()][coordenada.y()] -> saludar();
}

Resultado_Chequeos Mapa::construir_edificio_ubicacion(const std::string &edificio, const Coordenada& coordenada){
	//TODO: reemplazar por el diccionario o adaptar traductor al diccionario?
	Edificio* edificio_mapa = traductor_edificios(edificio);
	return this -> terreno[coordenada.x()][coordenada.y()] -> construir_edificio(edificio_mapa);
}

Resultado_Chequeos Mapa::demoler_edificio_ubicacion(std::string& edificio, const Coordenada& coordenada){
	edificio = (this -> terreno[coordenada.x()][coordenada.y()]) -> obtener_contenido();
	return (this -> terreno[coordenada.x()][coordenada.y()]) -> demoler_edificio();

}

Resultado_Chequeos Mapa::reparar_edificio_ubicacion(const Coordenada& coordenada){
	return (this -> terreno[coordenada.x()][coordenada.y()]) -> reparar_edificio();

}

//TODO: Si castea es porque antes pregunto que casillero. Rompe el Tell Don't Ask.
void Mapa::poner_material_ubicacion(std::string material,const Coordenada& coordenada){
	( (Casillero_Transitable*) this -> terreno[coordenada.x()][coordenada.y()] ) ->
			agregar_material(traductor_materiales(material, 0));
}


//OBS: Si es casillero Construible, solo recoge el producto. Si es Transitable recoge y libera memoria.
void Mapa::recolectar_material_ubicacion(const Coordenada& coordenada, Almacen* inventario){
	 this -> terreno[coordenada.x()][coordenada.y()] -> recoger_material(inventario);
}

//WHY: Se usa?
//RTA: sep
std::string Mapa::obtener_contenido_ubicacion(const Coordenada& coordenada) const{
	std::string contenido = CONTENIDO_VACIO;
	//Depende para que lo usemos. Hay una sobrecarga de obtener_contenido. Una para edificios y otra para materiales.
	contenido = terreno[coordenada.x()][coordenada.y()] -> obtener_contenido();
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
			generar_material(MATERIALES_EDIFICIOS[PIEDRA], casilleros_libres -> consulta(n_casillero));
			piedra_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		if((madera_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this -> numero_aleatorio(1, casilleros_libres->consulta_largo());
			generar_material(MATERIALES_EDIFICIOS[MADERA], casilleros_libres->consulta(n_casillero));

			madera_a_generar--;
			casilleros_libres -> baja(n_casillero);

		}
		if((metal_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this->numero_aleatorio(1,casilleros_libres->consulta_largo());
			generar_material(MATERIALES_EDIFICIOS[METAL], casilleros_libres->consulta(n_casillero));

			metal_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar);
		mapa_ocupado = casilleros_libres -> vacia();
		a_generar =
		    piedra_a_generar + madera_a_generar + metal_a_generar;
	}
	delete casilleros_libres;
	return mapa_ocupado;
}

// Ver si es necesario.
void Mapa::generar_material(std::string material, Coordenada coordenada){
	this -> poner_material_ubicacion(material, coordenada);	
}

std::size_t Mapa::numero_aleatorio(std::size_t minimo, std::size_t maximo) {
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

bool Mapa::explota_bomba(std::string &edificio, Coordenada coordenada){
	Resultado_Chequeos resultado = this -> terreno[coordenada.x][coordenada.y] -> atacar_edificio();
	if(resultado == DESTRUIDO)
		this -> demoler_edificio_ubicacion(edificio, coordenada);
	return (resultado == DESTRUIDO);
}

//TODO: Modificar la logica para que no sea necesario.
std::string Mapa::identificador_ocupados(std::string ocupador){
	std::string identificador = UBICACION_VACIA;
	if(ocupador == "mina")
		identificador = "M";
	else if (ocupador == "aserradero")
		identificador = "A";
	else if (ocupador == "fabrica")
		identificador = "F";
	else if (ocupador == "escuela")
		identificador = "E";
	else if (ocupador == "obelisco")
		identificador = "O";
	else if (ocupador == "planta electrica")
		identificador = "P";
	else if (ocupador == "madera")
		identificador = "W";
	else if (ocupador == "piedra")
		identificador = "S";
	else if (ocupador == "metal")
		identificador = "I";
	else if (ocupador == "mina oro")
		identificador = "G";
	return identificador;
}
