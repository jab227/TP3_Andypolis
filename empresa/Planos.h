#ifndef PLANOS_H_
#define PLANOS_H_

#include "../edificio/Edificio.h"
#include "../jugador/Jugador.h"
#include "../utils/Lista.h"

class Planos {
private:
	static Diccionario<std::string, Edificio*> lista_edificios;
public:
	//PRE: -
	//POST: creo unos planos inicializado en 0;
	Planos();

	//PRE: -
	//POST: Instancia planos con el diccionario.
	Planos(Diccionario<std::string, Edificio*> diccionario);

	//PRE: -
	//POST: se libera la memoria utilizada y el puntero se apunta  nullptr.
	~Planos();

	//PRE: -
	//POST: Deevuelve el puntero Edificio*.
	static Edificio* buscar(std::string nombre_edificio);
	
	//PRE: -
	//POST: Deevuelve el puntero Edificio*.
	static Resultado_Chequeos existe(std::string nombre_edificio);

	static std::size_t cantidad_permitida(const std::string& edificio);

	//PRE: -
	//POST: muestra por terminal la cantidad de edificios construidos de cada tipo,
	//los que se pueden construir y los materiales necesarios para construirlos.
	void mostrar_edificios();

	//PRE: -
	//POST: Permite modificar los valores de construcción del edificio.
	void modificar_edificio(std::string nombre, std::size_t madera, std::size_t piedra, std::size_t metal);

	//PRE: el edificio debe ser valido
	//POST: devuelve un vector en memoria dinamica con un listado de los materiales necesarios para
	//construir el edificio solicitado.
	Lista<Material> materiales_necesarios( Edificio* edificio);

	//PRE: edificio es valido
	//POST: aumenta 1 la cantidad del edificio construido
	void aumentar_construidos_edificio(const Edificio* &edificio);

	//PRE: edificio es valido
	//POST: disminuye 1 la cantidad del edificio construido
	void disminuir_construidos_edificio(const std::string &edificio);

	//Lo pase al jugador porque es quien sabe las coordenadas donde estan ubicados
	//sus edificios.
	//Lista<Material>* obtener_recursos_producidos()

	//PRE: -
	//POST: devuelve true si el nombre corresponde a un edificio o false en caso contrario.
	//por interfaz carga un puntero a Edificio con el edificio de la lista.
	Resultado_Chequeos chequeo_construir(const std::string &nombre_edificio,  Jugador* jugador,  Mapa* mapa);
private:

	void mostrar_materiales_producidos(Lista<Material> listado);
	
	//PRE: edificio tiene que ser distinto de nullptr
	//POST: devuelve en un std::string que cantidad y de que material produce el edificio o "ninguno".
	//Q: Se usa?
	//std::string material_producido( Edificio* edificio);


};


#endif /* PLANOS_H_ */
