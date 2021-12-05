#include "Almacen.h"
#include <fstream>
#include <iostream>

#include "../utils/LecturaArchivos.h"

const string NOMBRES_MATERIALES[] = {"madera", "piedra", "metal", "andycoins", "bombas"};
const int CANTIDAD_MATERIALES_DISTINTOS = 5, CANTIDAD_INICIAL = 0;
const std::size_t PRECIO_BOMBA = 100, BOMBAS_VACIAS = -1;

Almacen::Almacen() {
}

Almacen::Almacen(string ruta) {
	this -> cargar_materiales(ruta);
}

Almacen::~Almacen() {
}

void Almacen::cargar_materiales(string ruta){
	ifstream archivo;
	archivo.open(ruta);
	if (archivo.is_open()){
		string linea;
		Material nuevo_material;
		std::size_t cant_agregados = 0;
		while(getline(archivo, linea, ENTER)){
			nuevo_material = procesar_material(linea);
			agregar_material(nuevo_material, cant_agregados+1);
			cant_agregados++;
		}
	}else{
		for(int i = 0; i < CANTIDAD_MATERIALES_DISTINTOS; i++)
			agregar_material(Material(NOMBRES_MATERIALES[i], CANTIDAD_INICIAL), i+1);
	}
	archivo.close();
}

void Almacen::agregar_material(Material material, std::size_t posicion){
	this -> lista_materiales.alta(material, posicion);
}


//ESTO ES ASUMIENDO QUE LA LISTA EMPIEZA EN 1, ENTONCES 0 ES ERROR.
std::size_t Almacen::buscar_material(Material& a_buscar){
	std::size_t i = 1;
	std::size_t indice = NO_ENCONTRADO;
	while(!indice && i <= this -> lista_materiales.consulta_largo()){
		if (this -> lista_materiales.consulta(i) == a_buscar ){
			a_buscar = this -> lista_materiales.consulta(i);
			indice = i;
		}
	i++;
	}
	return indice;
}


//ESTO ES ASUMIENDO QUE LA LISTA EMPIEZA EN 1, ENTONCES 0 ES ERROR.
void Almacen::sumar_cantidad_material(string a_cambiar, std::size_t cantidad){
	Material material_a_cambiar = Material(a_cambiar,0);
	//VER: si nos podemos ahorrar ciclos (Edificiencia temoporal)
	std::size_t index = buscar_material(material_a_cambiar);
	if(index){
		material_a_cambiar.sumar_cantidad(cantidad);
		this -> lista_materiales.modificar(material_a_cambiar, index);
	}
}

void Almacen::mostrar_materiales(){
	cout << "Los materiales que hay son:" << endl;
	for(std::size_t i = 1; i <= this -> lista_materiales.consulta_largo(); i++){
		cout << "- " << this -> lista_materiales.consulta(i).obtener_cantidad() << " de "
			 << this -> lista_materiales.consulta(i).obtener_nombre() << endl;
	}
}

bool Almacen::guardar_materiales(string path){
	ofstream archivo(path);
	bool salida = false;

	if (archivo.is_open()){
		salida = true;
		for(std::size_t i = 1; i <= this -> lista_materiales.consulta_largo(); i++)
			archivo << this -> lista_materiales.consulta(i).obtener_nombre()   << " "
					<< this -> lista_materiales.consulta(i).obtener_cantidad() << endl;
	}
	archivo.close();
	return salida;
}

bool Almacen::hay_material_suficiente(Material material){
	bool suficiente = false;
	Material almacenado = Material(material.obtener_nombre(),0);
	if(buscar_material(almacenado)){
		suficiente = almacenado.obtener_cantidad() >= material.obtener_cantidad();
	}
	return suficiente;
}

Resultado_Chequeos Almacen::hay_lista_materiales(Lista<Material>* materiales_consultados){
	bool fin = false;
	Resultado_Chequeos suficiente = EXITO;
	std::size_t i = 1;
	while (i <= this -> lista_materiales.consulta_largo() && !fin){
		if(!this -> hay_material_suficiente(materiales_consultados -> consulta(i))){
			suficiente = NO_MATERIALES;
			fin = true;
		}
		i++;
	}
	return suficiente;
}


void Almacen::descontar_lista_materiales(Lista<Material>* materiales_usados, std::size_t porcentaje){
	std::size_t proporcion = porcentaje/100;
	for(std::size_t i = 1; i <= materiales_usados -> consulta_largo(); i++){
		Material material = materiales_usados -> consulta(i);
		this -> sumar_cantidad_material(material.obtener_nombre(), -material.obtener_cantidad()*proporcion);
	}
}

void Almacen::sumar_lista_materiales(Lista<Material>* materiales_obtenidos, std::size_t porcentaje){
	//TODO: Constantes.
	std::size_t proporcion = porcentaje/100;
	for(std::size_t i = 1; i <= materiales_obtenidos -> consulta_largo(); i++){
		Material material = materiales_obtenidos -> consulta(i);
		this -> sumar_cantidad_material(material.obtener_nombre(), material.obtener_cantidad()*proporcion);
	}
}


void Almacen::comprar_bombas(){
	std::size_t bombas = this -> pedir_bombas();

		if(bombas != BOMBAS_VACIAS){
			cout << "Compraste " << bombas << " bombas exitosamente."  << endl;
			this -> sumar_cantidad_material(NOMBRES_MATERIALES[4], bombas);
			this -> sumar_cantidad_material(NOMBRES_MATERIALES[3], -(bombas*PRECIO_BOMBA));
			Material andycoins = Material(NOMBRES_MATERIALES[3],0);
			Material bombas = Material(NOMBRES_MATERIALES[4],0);
			buscar_material(andycoins);
			buscar_material(bombas);
			std::cout << "Cantidad de bombas: " << andycoins.obtener_cantidad() << std::endl;
			std::cout << "Andycoins restantes: " << bombas.obtener_cantidad() << std::endl;
		}
}

std::size_t Almacen::pedir_bombas(){
	Material andycoins = Material(NOMBRES_MATERIALES[3],0);
	this -> buscar_material(andycoins);
	std::size_t bombas = BOMBAS_VACIAS, bombas_comprables =  andycoins.obtener_cantidad() % PRECIO_BOMBA;
	bool fin = false;
	string bombas_ingresadas;
	do{
		cout << "Se pueden comprar " << bombas_comprables << " bombas." << endl;
		cout << "Ingresa la cantidad de bombas que queres comprar o salir" << endl << "Bombas: ";
		getline(cin, bombas_ingresadas);
		fin = this -> chequeo_bombas(bombas_ingresadas, bombas_comprables, bombas);
	}
	while(!fin);
	return bombas;
}

bool Almacen::chequeo_bombas(string bombas_ingresadas, std::size_t bombas_comprables, std::size_t &bombas){
	bool resultado = false;
	if(bombas_ingresadas == SALIR_STR){
		resultado = true;
		std::cout << "No se realizo ninguna accion." << std::endl;
	}
	else if(!es_numero(bombas_ingresadas) || stoi(bombas_ingresadas) < 0)
		std::cout << "La/s opcion/es ingresada/s no es/son valida/s." << std::endl;
	else if(stoi(bombas_ingresadas) > (int) bombas_comprables)
		std::cout << "No hay suficientes materiales." << std::endl;
	else{
		bombas = stoi(bombas_ingresadas);
		resultado = true;
	}
	return resultado;
}
