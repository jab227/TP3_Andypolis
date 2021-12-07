#include "Planos.h"
#include "../edificio/Productor.h"
#include "../utils/LecturaArchivos.h"
#include <fstream>

Diccionario<std::string, Edificio*> Planos::lista_edificios = Diccionario();

Planos::Planos() {
}

//Cuando este el Parser, hacer que reciba los datos.
Planos::Planos(std::string ruta){
	this -> cargar_edificios(ruta);
}

Planos::~Planos() {
	//delete lista_edificios;
}

//PARSER: Reemplazable con el Parser_Ubicacion.
/*
void Planos::agregar_edificio(Edificio* edificio){
	lista_edificios.insertar(edificio -> obtener_nombre(), edificio);
}
*/
//PARSER: Reemplazable con el Parser_Ubicacion.
/*
void Planos::cargar_edificios(std::string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		std::string lectura;
		Edificio* nuevo_edificio;
		while(getline(archivo, lectura, ENTER)){
			nuevo_edificio = procesar_edificio(lectura);
			agregar_edificio(nuevo_edificio);
		}
	}
	archivo.close();
}
*/
//TODO: Agregar vector con claves del diccionario para poder recorrerla.
void Planos::mostrar_edificios(){
	std::cout << "|Edificio\t\t|Piedra\t|Madera\t|Metal\t|Construidos\t|Construibles\t|Material Producido\t|" << std::endl;
	/*
	Edificio* consultado = this -> lista_edificios[key];
		std::cout << '|' << consultado -> obtener_nombre() << espaciado(consultado -> obtener_nombre(), 21)
				    << consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[PIEDRA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[MADERA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[METAL])  << "\t|"
					<< consultado -> obtener_construidos()  << "\t\t|"
					<< consultado -> obtener_max_permitidos() - consultado -> obtener_construidos() << "\t\t|"
					<< material_producido(consultado) << "\t\t|" << std::endl;
	}
	*/
}


std::string Planos::material_producido( Edificio* edificio){
	return edificio -> info_producto();
}

Resultado_Chequeos Planos::permitido_construir(const std::string &nombre_edificio,  Jugador* jugador,  Mapa* mapa){
	Resultado_Chequeos resultado = NO_EXISTE;
	if(existe(nombre_edificio)){
		Edificio* ptr_edificio = this -> lista_edificios[nombre_edificio];
		Lista<Material>* materiales = materiales_necesarios(ptr_edificio);
		resultado = jugador -> tiene_materiales(materiales);
		if(resultado != NO_MATERIALES){
			std::size_t construidos = jugador -> cantidad_edificios(nombre_edificio, mapa);
			resultado = ptr_edificio -> esta_maxima_capacidad(construidos);
		}
		delete materiales;
	}
	return resultado;
}

bool Planos::existe(std::string nombre_edificio){
	return lista_edificios.existe(nombre_edificio);
}

//Liberar vector.
Lista<Material>* Planos::materiales_necesarios( Edificio* edificio){
	Lista<Material>* lista_materiales = new Lista<Material>;
	//Chequear que no haya roto al cambiar alta() por alta_al_final().
	for(std::size_t i = 0; i < CANT_MATERIALES_EDIFICIOS; i++)
		lista_materiales -> alta_al_final(Material(MATERIALES_EDIFICIOS[i], edificio -> obtener_cant_material(MATERIALES_EDIFICIOS[i])));
	return lista_materiales;
}

/* WHY: Borrables?
void Planos::aumentar_construidos_edificio(const Edificio* &edificio){
	bool encontrado = false;
	std::size_t i = 1;
	Edificio* buscado;
	while(!encontrado && i <= this -> lista_edificios.consulta_largo()){
		buscado = this -> lista_edificios.consulta(i);
		if(*(buscado) == *edificio){
			encontrado = true;
			buscado -> aumentar_construidos();
		}
		i++;
	}
}

void Planos::disminuir_construidos_edificio(const std::string &edificio){
	bool encontrado = false;
	std::size_t i = 1;
	Edificio* buscado;
	while(!encontrado && i <= this -> lista_edificios.consulta_largo()){
		 buscado = this -> lista_edificios.consulta(i);
		if(buscado -> obtener_nombre() == edificio){
			encontrado = true;
			buscado -> disminuir_construidos();
		}
		i++;
	}
}
*/

void Planos::mostrar_materiales_producidos(Lista<Material>* listado){
	//Podria reemplazarse por simple while, pero como aviso cuando no hay edif productor?
	if(listado -> consulta_largo() > 0){
		std::cout << "Se produjo: " << std::endl;
		for(std::size_t i = 1; i <= listado -> consulta_largo(); i++){
			Material material = listado -> consulta(i);
			std::cout << "- " << material.obtener_cantidad() << " de " << material.obtener_nombre() << std::endl;
		}
	}else
		std::cout << "No hay edificios construidos que produzcan materiales.\n"
				"Construyo alguno para empezar a producir!" << std::endl;
}


Edificio* Planos::buscar(std::string nombre_edificio){
	return lista_edificios[nombre_edificio];
}