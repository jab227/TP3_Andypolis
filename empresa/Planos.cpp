#include "Planos.h"
#include "../edificio/Productor.h"
#include "../utils/LecturaArchivos.h"
#include <fstream>

Planos::Planos() { }

//Cuando este el Parser, hacer que reciba los datos.
Planos::Planos(string ruta){
	this -> cargar_edificios(ruta);
}

Planos::~Planos() {
	//Eliminar el diccionario y liberar la memoria de los nodos.
	//WHY: Como sabe cuando liberar el dato y cuando no?
}

//PARSER: Reemplazable con el Parser_Ubicacion.
void Planos::agregar_edificio(Edificio* edificio){
	this -> lista_edificios.insertar(edificio -> obtener_nombre(), edificio);
}

//PARSER: Reemplazable con el Parser_Ubicacion.
void Planos::cargar_edificios(string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		std::size_t cant_agregados = 0;
		Edificio* nuevo_edificio;
		while(getline(archivo, lectura, ENTER)){
			nuevo_edificio = procesar_edificio(lectura);
			agregar_edificio(nuevo_edificio);
		}
	}
	archivo.close();
}

//TODO: Agregar a diccionario un metodo para imprimir en formato tabla.
//o tener un vector con los nombres posibles para las construcciones...
void Planos::mostrar_edificios(){
	/*
	cout << "|Edificio\t\t|Piedra\t|Madera\t|Metal\t|Construidos\t|Construibles\t|Material Producido\t|" << endl;
	Edificio* consultado = this -> lista_edificios[key];
		cout << '|' << consultado -> obtener_nombre() << espaciado(consultado -> obtener_nombre(), 21)
				    << consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[PIEDRA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[MADERA]) << "\t|"
					<< consultado -> obtener_cant_material(MATERTIALES_EDIFICIOS[METAL])  << "\t|"
					<< consultado -> obtener_construidos()  << "\t\t|"
					<< consultado -> obtener_max_permitidos() - consultado -> obtener_construidos() << "\t\t|"
					<< material_producido(consultado) << "\t\t|" << endl;
	}
	*/
}


std::string Planos::material_producido( Edificio* edificio){
	return edificio -> info_producto();
}

Resultado_Chequeos Planos::permitido_construir(const std::string &nombre_edificio, const Jugador* &jugador, const Mapa* &mapa){
	Resultado_Chequeos resultado = NO_EXISTE;
	if(existe(nombre_edificio)){
		Edificio* ptr_edificio = lista_edificios[nombre_edificio];
		Lista<Material>* materiales = materiales_necesarios(ptr_edificio);
		resultado = jugador -> tiene_materiales(materiales);
		if(resultado != NO_MATERIALES){
			std::size_t construidos = jugador -> cantidad_edificios(nombre_edificio, mapa);
			resultado = ptr_edificio -> esta_maxima_capacidad(construidos);
		}
	}
	return resultado;
}

bool Planos::existe(std::string nombre_edificio){
	return lista_edificios.existe(nombre_edificio);
}

Lista<Material>* Planos::materiales_necesarios(const Edificio* &edificio){
	Lista<Material>* lista_materiales = new Lista<Material>;
	//Chequear que no haya roto al cambiar alta() por alta_al_final().
	for(std::size_t i = 0; i < CANT_MATERIALES_EDIFICIOS; i++)
		lista_materiales -> alta_al_final(Material(MATERTIALES_EDIFICIOS[i], edificio -> obtener_cant_material(MATERTIALES_EDIFICIOS[i])));
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

void Planos::disminuir_construidos_edificio(const string &edificio){
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

// TODO: Responsabilidad del jugador.
Lista<Material>* Jugador::obtener_recursos_producidos(){
	Lista<Material>* listado = new Lista<Material>;
	Edificio* edificio;
	Material material_producido;
	std::size_t agregados = 0;
	for(std::size_t i = 1; i <= this -> lista_edificios.consulta_largo(); i++){
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
		for(std::size_t i = 1; i <= listado -> consulta_largo(); i++){
			Material material = listado -> consulta(i);
			cout << "- " << material.obtener_cantidad() << " de " << material.obtener_nombre() << endl;
		}
	}else
		cout << "No hay edificios construidos que produzcan materiales.\n"
				"Construyo alguno para empezar a producir!" << endl;
}


Edificio* Planos::buscar(std::string nombre_edificio){
	return lista_edificios[nombre_edificio];
}