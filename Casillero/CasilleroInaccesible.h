#ifndef CASILLERO_CASILLEROINACCESIBLE_H_
#define CASILLERO_CASILLEROINACCESIBLE_H_

#include "Casillero.h"

class Casillero_Inaccesible: public Casillero{
public:
	//PRE: -
	//POST: se crea un casillero vacio
	Casillero_Inaccesible();

	//PRE: -
	//POST: se destruye el casillero
	~Casillero_Inaccesible();

	//PRE: -
	//POST: devuelve si el casillero esta ocupado, para este caso, devuelve siempre true
	bool esta_ocupado();

	//PRE: -
	//POST: imprime un saludo por terminal.
	void saludar();

	//PRE: no se deberia llamar a esta funcion, este casillero nunca contiene algo.
	//POST: devuelve CONTENIDO_VACIO.
	std::string obtener_contenido();
	
	//PRE: - PROVISORIO
	//POST: devuelve si el casillero es transitable o no
	bool es_casillero_transitable();
	
	//PRE: -
	//POST:
	bool construir_edificio(Edificio* edificio);

	//PRE: -
	//POST: -
	Edificio* agregar_lista_edificio( std::size_t* coordenadas, Lista<std::string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas);

	//Agregar demoler_edificio en inacc y transitables.
	Edificio* demoler_edificio();
};

#endif /* CASILLERO_CASILLEROINACCESIBLE_H_ */
