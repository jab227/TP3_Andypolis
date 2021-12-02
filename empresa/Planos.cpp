#include "Planos.h"
#include "../edificio/Productor.h"
#include "../utils/LecturaArchivos.h"
#include <fstream>


const int NO_ENCONTRADO = -1;

Planos::Planos() { }

//Cuando este el Parser, hacer que reciba los datos.
Planos::Planos(string ruta){
	this -> cargar_edificios(ruta);
}

Planos::~Planos() {
	for(int i = 1; i <= lista_edificios.consulta_largo(); i++)
		delete this -> lista_edificios.consulta(i);
}

void Planos::agregar_edificio(Edificio* edificio, int posicion){
	this -> lista_edificios.alta(edificio, posicion);
}

//Reemplazable con el Parser.
void Planos::cargar_edificios(string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		int cant_agregados = 0;
		Edificio* nuevo_edificio;
		while(getline(archivo, lectura, ENTER)){
			nuevo_edificio = procesar_edificio(lectura);
			agregar_edificio(nuevo_edificio, ++cant_agregados);
		}
	}
	archivo.close();
}

//Reemplazable por el printer.
void Planos::mostrar_edificios(){
	cout << "|Edificio\t\t|Piedra\t|Madera\t|Metal\t|Construidos\t|Construibles\t|Material Producido\t|" << endl;
	Edificio* consultado;
	for(int i = 1; i <= this -> lista_edificios.consulta_largo(); i++){
		consultado = this -> lista_edificios.consulta(i);
		cout << '|' << consultado -> obtener_nombre() << espaciado(consultado -> obtener_nombre(), 21)
				    << consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[PIEDRA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[MADERA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[METAL])  << "\t|"
					<< consultado -> obtener_construidos()  << "\t\t|"
					<< consultado -> obtener_max_permitidos() - consultado -> obtener_construidos() << "\t\t|"
					<< material_producido(consultado) << "\t\t|" << endl;
	}
}


string Planos::material_producido(Edificio* edificio){
	return edificio -> info_producto();
}

bool Planos::es_edificio_valido(string nombre_edificio, Edificio*& edificio){
	bool encontrado = false;
	int i = 1;
	//Provisorio. //Liberar?
	edificio = traductor_edificios(nombre_edificio,0,0,0,0);
	while(!encontrado && i <= this -> lista_edificios.consulta_largo()){
		if(*(this -> lista_edificios.consulta(i)) == *edificio){
			*edificio =*(this -> lista_edificios.consulta(i));
			encontrado = true;
		}
		i++;
	} 
	return encontrado;
}

Lista<Material>* Planos::materiales_necesarios(Edificio* edificio){
	Lista<Material>* lista_materiales = new Lista<Material>;
	//Chequear que no haya roto al cambiar alta() por alta_al_final().
	for(int i = 0; i < CANT_MATERIALES_EDIFICIOS; i++)
		lista_materiales -> alta_al_final(Material(MATERTIALES_EDIFICIOS[i], edificio -> obtener_cant_material(MATERTIALES_EDIFICIOS[i])));
	return lista_materiales;
}

void Planos::aumentar_construidos_edificio(Edificio* edificio){
	bool encontrado = false;
	int i = 1;
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

void Planos::disminuir_construidos_edificio(string edificio){
	bool encontrado = false;
	int i = 1;
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

Resultado_Chequeos Planos::check_construir_edificio(string edificio, Edificio*& edif){
	Resultado_Chequeos resultado = EXITO;
	if(!this -> es_edificio_valido(edificio, edif))
		resultado = NO_EXISTE;
	else if(edif -> esta_maxima_capacidad())
		resultado = MAXIMA_CANTIDAD;
	return resultado;
}

Lista<Material>* Planos::obtener_recursos_producidos(){
	Lista<Material>* listado = new Lista<Material>;
	Edificio* edificio;
	Material material_producido;
	int agregados = 0;
	for(int i = 1; i <= this -> lista_edificios.consulta_largo(); i++){
		edificio = this -> lista_edificios.consulta(i);
		//No necesito chequear si esta construido.
		material_producido = edificio -> producir_material();
		//Si no tengo construidos, el material que se sume va a ser 0.
		material_producido.cambiar_cantidad( material_producido.obtener_cantidad() * edificio -> obtener_construidos());
		//Comparador de Material.
		if(material_producido.obtener_nombre() != "ninguno") //provisorio.
			listado -> alta(material_producido, ++agregados);
	}
	this -> mostrar_materiales_producidos(listado);
	return listado;
}

void Planos::mostrar_materiales_producidos(Lista<Material>* listado){
	//Podria reemplazarse por simple while, pero como aviso cuando no hay edif productor?
	if(listado -> consulta_largo() > 0){
		cout << "Se produjo: " << endl;
		for(int i = 1; i <= listado -> consulta_largo(); i++){
			Material material = listado -> consulta(i);
			cout << "- " << material.obtener_cantidad() << " de " << material.obtener_nombre() << endl;
		}
	}else
		cout << "No hay edificios construidos que produzcan materiales.\n"
				"Construyo alguno para empezar a producir!" << endl;
}
