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
const std::size_t ANDYCOINS_MINIMO = 0, ANDYCOINS_MAXIMO = 1;
const std::size_t CONJUNTO[] = {100, 50, 50, 250}, CANTIDAD_CONJUNTOS = 4;

Mapa::Mapa(const std::string& mapa, std::size_t filas, std::size_t columnas)
    : filas(filas), columnas(columnas), terreno(nullptr) {
	this -> cargar_terreno(mapa);
}

Mapa::~Mapa() {
	for (std::size_t i = 0; i < this -> filas; i++) {
		for (std::size_t j = 0; j < this -> columnas; j++) {
			delete this -> terreno[i][j];
		}
		delete[] this -> terreno[i];
	}
	delete[] this -> terreno;
}

void Mapa::cargar_terreno(const std::string& mapa) {
	this -> terreno = new Casillero**[this -> filas];
	for (std::size_t fila = 0; fila < this -> filas; fila++) {
		this -> iniciar_filas_casilleros(fila, mapa);
	}
}

void Mapa::iniciar_filas_casilleros(std::size_t fila, const std::string& mapa) {
	this -> terreno[fila] = new Casillero*[this -> columnas];
	for (std::size_t columna = 0; columna < this -> columnas; columna++) {
		this -> terreno[fila][columna] =
		    traductor_casillero(mapa[columna + fila * this -> columnas + fila]);
	}
}

bool Mapa::es_coordenada_valida(const Coordenada& coordenada) {
	return (coordenada.x() < this->filas && coordenada.y() < this->columnas);
}

void Mapa::mostrar_casillero(Coordenada coordenada, std::string contenido){
	std::cout << this->terreno[coordenada.x()][coordenada.y()]->obtener_color();
	std::cout << ' ' << this->identificador_ocupados( contenido )<< ' ';
	std::cout << FIN_COLOR;	
}

/*
void Mapa::mostrar_mapa() {
	std::cout << "Mapa:" << endl;
	std::cout << "   ";
	for (std::size_t columnas = 0; columnas < this->columnas; columnas++)
		std::cout << ' ' << columnas / 10 << ' ';
	cout << std::endl << "   ";
	for (std::size_t columnas = 0; columnas < this->columnas; columnas++)
		std::cout << ' ' << columnas % 10 << ' ';
	std::cout << std::endl;

	Coordenada coordenada;
	std::string contenido;
	for (std::size_t filas = 0; filas < this->filas; filas++) {
		std::cout << filas / 10 << filas % 10 << ' ';
		for (std::size_t columnas = 0; columnas < this->columnas;
		     columnas++) {
			coordenada = Coordenada(filas,columnas);
			
			std::cout << this->terreno[filas][columnas]->obtener_color();
			
			if(jugadores.consulta(1).obtener_posicion() == coordenada)
				contenido = "jugador1";
			else if(jugadores.consulta(2).obtener_posicion() == coordenada)
				contenido = "jugador2";
			else
				contenido = this->terreno[filas][columnas]->obtener_contenido();
			
			std::cout << ' ' << this->identificador_ocupados( contenido )<< ' ';
			std::cout << FIN_COLOR;
		}
		std::cout << std::endl << FIN_COLOR;
	}
	std::cout << FIN_COLOR;
}
*/
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

Resultado_Chequeos Mapa::reparar_edificio_ubicacion(const Coordenada& coordenada, bool reparar) const{
	return (this -> terreno[coordenada.x()][coordenada.y()]) -> reparar_edificio(reparar);

}

void Mapa::poner_material_ubicacion(std::string material,const Coordenada& coordenada) {
	(this -> terreno[coordenada.x()][coordenada.y()]) -> agregar_material(this -> generar_conjunto_material(material));
}

Material Mapa::generar_conjunto_material(std::string material){
	Material material_generado;
	for(std::size_t i = 0; i < CANTIDAD_CONJUNTOS; i++){
		if(NOMBRES_MATERIALES[i] == material)
			material_generado = Material(material, CONJUNTO[i]);
	}
	return material_generado;
}

//OBS: Ahora es inutil porque no recogemos direcamente del edificio, debemos producir primero!
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
	std::size_t andycoins_a_generar = this -> numero_aleatorio(ANDYCOINS_MINIMO, ANDYCOINS_MAXIMO);
	std::size_t a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar + andycoins_a_generar);
	std::size_t n_casillero = 0;
	bool mapa_ocupado = casilleros_libres->vacia();
	while(a_generar > 0 && !(casilleros_libres->vacia())){
		if((piedra_a_generar > 0)){
			n_casillero = this -> numero_aleatorio(1, casilleros_libres->consulta_largo());
			generar_material(NOMBRES_MATERIALES[PIEDRA], casilleros_libres -> consulta(n_casillero));
			piedra_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		if((madera_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this -> numero_aleatorio(1, casilleros_libres->consulta_largo());
			generar_material(NOMBRES_MATERIALES[MADERA], casilleros_libres->consulta(n_casillero));

			madera_a_generar--;
			casilleros_libres -> baja(n_casillero);

		}
		if((metal_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this->numero_aleatorio(1,casilleros_libres->consulta_largo());
			generar_material(NOMBRES_MATERIALES[METAL], casilleros_libres->consulta(n_casillero));

			metal_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		if((andycoins_a_generar > 0) && !(casilleros_libres->vacia())){
			n_casillero = this->numero_aleatorio(1,casilleros_libres->consulta_largo());
			generar_material(NOMBRES_MATERIALES[ANDYCOINS], casilleros_libres->consulta(n_casillero));
			andycoins_a_generar--;
			casilleros_libres -> baja(n_casillero);
		}
		a_generar = (piedra_a_generar + madera_a_generar + metal_a_generar + andycoins_a_generar);
		mapa_ocupado = casilleros_libres -> vacia();
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
	Resultado_Chequeos resultado = this -> terreno[coordenada.x()][coordenada.y()] -> atacar_edificio();
	edificio = this -> terreno[coordenada.x()][coordenada.y()] -> obtener_contenido();
	if(resultado == DESTRUIDO)
		this -> demoler_edificio_ubicacion(edificio, coordenada);
	return (resultado == DESTRUIDO);
}

char Mapa::obtener_identificador_casillero(Coordenada coordenada){
	return this -> terreno[coordenada.x()][coordenada.y()] -> obtener_identificador();
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
	else if(ocupador == "andycoins")
		identificador = "C";
	else if(ocupador == "jugador1")
		identificador = "J";
	else if(ocupador == "jugador2")
		identificador = "U";
	return identificador;
}


std::string Mapa::estado_actual_materiales(){
	std::string texto, linea; 
	for (std::size_t filas = 0; filas < this->filas; filas++){
		for (std::size_t columnas = 0; columnas < this->columnas; columnas++){
	     	if(this->terreno[filas][columnas] -> es_casillero_transitable() 
	     				&& this->terreno[filas][columnas]->obtener_contenido() != ""){
	     		linea = this->terreno[filas][columnas]->obtener_contenido() + " " + Coordenada(filas, columnas).a_string() + "\n";
				texto += linea;
			}
		}
	}
	return texto;
}
