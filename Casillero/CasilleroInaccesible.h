#ifndef CASILLERO_CASILLEROINACCESIBLE_H_
#define CASILLERO_CASILLEROINACCESIBLE_H_

#include "../Casillero.h"

class Casillero_Inaccesible : public Casillero{
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

	//PRE: -
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: -
	//POST: devuelve si el casillero es construible o no.
	bool es_casillero_construible();

	//PRE: no se deberia llamar a esta funcion, este casillero nunca contiene algo.
	//POST: devuelve CONTENIDO_VACIO.
	std::string obtener_contenido();
};

#endif /* CASILLERO_CASILLEROINACCESIBLE_H_ */
