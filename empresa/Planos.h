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
	//POS: creo unos planos inicializado en 0;
	Planos();

	//PRE: -
	//POS: Instancia planos con el diccionario.
	Planos(Diccionario<std::string, Edificio*> diccionario);

	//PRE: -
	//POS: se libera la memoria utilizada y el puntero se apunta  nullptr.
	~Planos();

	//PRE: -
	//POS: Deevuelve el puntero Edificio* del edificio con nombre nombre_edificio.
	static Edificio* buscar(std::string nombre_edificio);
	
	//PRE: -
	//POS: Deevuelve Resultado_Chequeos de si existe el edificio con nombre_edificio.
	static Resultado_Chequeos existe(std::string nombre_edificio);

	// PRE: El edificio tiene que existir
	// POS: Devuelve la cantidad permitida de edificios que se puede 
	// construir.
	static std::size_t cantidad_permitida(const std::string& edificio);

	// PRE: -
	// POS: Devuelve una lista con los edificios en el diccionario.
	static Lista<std::string> edificios_disponibles();

	//PRE: -
	//POS: muestra por terminal la cantidad de edificios construidos de cada tipo,
	//los que se pueden construir y los materiales necesarios para construirlos.
	void mostrar_edificios();

	//PRE: -
	//POS: Permite modificar los valores de construcción del edificio.
	void modificar_edificio(std::string nombre, std::size_t madera, std::size_t piedra, std::size_t metal);

	//PRE: el edificio debe ser valido
	//POS: devuelve una lista  los materiales necesarios para construir el edificio solicitado.
	Lista<Material> materiales_necesarios( std::string edificio);

	//PRE: -
	//POS: devuelve true si el nombre corresponde a un edificio o false en caso contrario.
	//por interfaz carga un puntero a Edificio con el edificio de la lista.
	Resultado_Chequeos chequeo_construir(const std::string &nombre_edificio,  Jugador* jugador,  Mapa* mapa);

	//PRE: El diccionario de edificios debe estar cargado.
	//POS: Devuelve en un string la informacion de los edificios para guardar en un archivo.
	std::string estado_actual_edificios();
};


#endif /* PLANOS_H_ */
