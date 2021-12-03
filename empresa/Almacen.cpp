#include "Almacen.h"
#include <fstream>
#include <iostream>

#include "../utils/LecturaArchivos.h"

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
	}
	archivo.close();
}
void Almacen::agregar_material(Material material, std::size_t posicion){
	this -> lista_materiales.alta(material, posicion);
}

int Almacen::buscar_material(string a_buscar){
	int cantidad = NO_ENCONTRADO;
	bool fin = false;
	std::size_t i = 1;
	while(!fin && i <= this -> lista_materiales.consulta_largo()){
		if (this -> lista_materiales.consulta(i).obtener_nombre() == a_buscar){
			//Casteo
			cantidad = (int) this -> lista_materiales.consulta(i).obtener_cantidad();
			fin = true;
		}
	i++;
	}
	return cantidad;
}

void Almacen::modificar_cantidad_material(string a_cambiar, std::size_t cantidad){
	bool fin = false;
	std::size_t i = 1;
	while(i <= this -> lista_materiales.consulta_largo() && !fin){
		if(this -> lista_materiales.consulta(i).obtener_nombre() == a_cambiar){
			Material nuevo = this -> lista_materiales.consulta(i);
			nuevo.cambiar_cantidad(nuevo.obtener_cantidad()+cantidad);
			this -> lista_materiales.modificar(nuevo, i);
			fin = true;
		}
	i++;
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
	bool suficiente = false, fin = false;
	std::size_t i = 1;
	while (i <= this -> lista_materiales.consulta_largo() && !fin){
		Material almacenado = this -> lista_materiales.consulta(i);
		if(almacenado.obtener_nombre() == material.obtener_nombre()){
			fin = true;
			suficiente = almacenado.obtener_cantidad() >= material.obtener_cantidad();
		}
		i++;
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

void Almacen::restar_lista_materiales(Lista<Material>* materiales_usados){
	for(std::size_t i = 1; i <= materiales_usados -> consulta_largo(); i++){
		Material material = materiales_usados -> consulta(i);
		this -> modificar_cantidad_material(material.obtener_nombre(), -material.obtener_cantidad());
	}
}

void Almacen::sumar_lista_materiales(Lista<Material>* materiales_obtenidos, bool recuperados){
	for(std::size_t i = 1; i <= materiales_obtenidos -> consulta_largo(); i++){
		Material material = materiales_obtenidos -> consulta(i);
		if(!recuperados)
			this -> modificar_cantidad_material(material.obtener_nombre(), material.obtener_cantidad());
		else
			this -> modificar_cantidad_material(material.obtener_nombre(), material.obtener_cantidad()/2);
	}
}
