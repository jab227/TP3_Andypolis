#ifndef PLANOS_H_
#define PLANOS_H_

#include "../edificio/Edificio.h"
#include "../jugador/Jugador.h"
#include "../utils/Lista.h"

class Planos {
private:
//FER: Lo hago estatico ya que es comun a todo el programa, no es de la intancia particular.
//Evita tener a mano la instancia del diccionario cuando queremos preguntar si existe un edificio.
	static Diccionario<std::string, Edificio*> lista_edificios;
public:

	//PRE: -
	//POST: creo unos planos inicializado en 0;
	Planos();

	//PRE: ruta debe ser una ruta a un archivo bien estructurado
	//POST: creo unos planos inicializado con el archivo en la ruta espesificada.
	Planos(string ruta);

	//PRE: -
	//POST: se libera la memoria utilizada y el puntero se apunta  nullptr.
	~Planos();

	// NO esta compilando el static. Referencia indefinida. 
	// Tendre que adaptarlo si no lo resuelvo.
	static Edificio* buscar(std::string nombre_edificio);
	static bool existe(std::string nombre_edificio);

	//PRE: se le debe pasar la ruta del archivo a abrir el cual debe estar bien estructurado
	//POST: en caso de poder abrir el archivo, carga la lista con los elementos del archivo
	void cargar_edificios(string ruta);

	//PRE: -
	//POST: muestra por terminal la cantidad de edificios construidos de cada tipo,
	//los que se pueden construir y los materiales necesarios para construirlos.
	void mostrar_edificios();

	//PRE: el edificio debe ser valido
	//POST: devuelve un vector en memoria dinamica con un listado de los materiales necesarios para
	//construir el edificio solicitado.
	Lista<Material>* materiales_necesarios( Edificio* edificio);

	//PRE: edificio es valido
	//POST: aumenta 1 la cantidad del edificio construido
	void aumentar_construidos_edificio(const Edificio* &edificio);

	//PRE: edificio es valido
	//POST: disminuye 1 la cantidad del edificio construido
	void disminuir_construidos_edificio(const string &edificio);

	//PRE: edificio es valido
	//POST: devuele si se puede construir, si no existe o se tiene la cantidad maxima construida.
	Resultado_Chequeos check_construir_edificio(const string &edificio, Edificio*& edif);

//Lo pase al jugador porque es quien sabe las coordenadas donde estan ubicados
//sus edificios.
//Lista<Material>* obtener_recursos_producidos()
	//PRE: -
	//POST: devuelve true si el nombre corresponde a un edificio o false en caso contrario.
	//por interfaz carga un puntero a Edificio con el edificio de la lista.
	Resultado_Chequeos permitido_construir(const std::string &nombre_edificio,  Jugador* jugador,  Mapa* mapa);
private:
	//PRE: 1 <= posicion <= el largo de la lista.
	//POST: se agrega el material al final del vector.
	void agregar_edificio(Edificio* edificio);

	//PRE: edificio tiene que ser distinto de nullptr
	//POST: devuelve en un string que cantidad y de que material produce el edificio o "ninguno".
	string material_producido( Edificio* edificio);

	void mostrar_materiales_producidos(Lista<Material>* listado);

};


#endif /* PLANOS_H_ */
