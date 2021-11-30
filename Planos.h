#ifndef PLANOS_H_
#define PLANOS_H_

#include "Edificio.h"
#include "Lista.h"

class Planos {
public:
	Lista<Edificio*> lista_edificios;
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

	//PRE: se le debe pasar la ruta del archivo a abrir el cual debe estar bien estructurado
	//POST: en caso de poder abrir el archivo, carga la lista con los elementos del archivo
	void cargar_edificios(string ruta);

	//PRE: -
	//POST: muestra por terminal la cantidad de edificios construidos de cada tipo,
	//los que se pueden construir y los materiales necesarios para construirlos.
	void mostrar_edificios();

	//PRE: -
	//POST: devuelve true si el nombre corresponde a un edificio o false en caso contrario.
	bool es_edificio_valido(string edificio);

	//PRE: el edificio debe ser valido.
	//POST: devuelve la cantidad maxima permitida para construir del edificio.
	int cant_max_edificio(string edificio);

	//PRE: el edificio debe ser valido.
	//POST: devuelve cuantos edificios hay construidos de este tipo.
	int cant_construidos(string edificio);

	//PRE: el edificio debe ser valido
	//POST: devuelve un vector en memoria dinamica con un listado de los materiales necesarios para
	//construir el edificio solicitado.
	Lista<Material>* materiales_necesarios(string edificio);

	//PRE: edificio es valido
	//POST: aumenta 1 la cantidad del edificio construido
	void aumentar_construidos_edificio(string edificio);

	//PRE: edificio es valido
	//POST: disminuye 1 la cantidad del edificio construido
	void disminuir_construidos_edificio(string edificio);

	//PRE: edificio es valido
	//POST: devuele si se puede construir, si no existe o se tiene la cantidad maxima construida.
	Resultado_Chequeos check_construir_edificio(string edificio);

	//PRE: -
	//POST: devuelve un listado con los materiales producidos por los edificios construidos e imprime
	//por la consola los materiales producidos.
	Lista<Material>* obtener_recursos_producidos();
private:
	//PRE: 1 <= posicion <= el largo de la lista.
	//POST: se agrega el material al final del vector.
	void agregar_edificio(Edificio* edificio, int posicion);

	//PRE: edificio tiene que ser distinto de nullptr
	//POST: devuelve en un string que cantidad y de que material produce el edificio o "ninguno".
	string material_producido(Edificio* edificio);

	void mostrar_materiales_producidos(Lista<Material>* listado);
};


#endif /* PLANOS_H_ */
