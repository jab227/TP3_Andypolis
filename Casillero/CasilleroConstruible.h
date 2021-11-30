#ifndef CASILLERO_CASILLEROCONSTRUIBLE_H_
#define CASILLERO_CASILLEROCONSTRUIBLE_H_

#include "../Casillero.h"
#include "../Edificio.h"

class Casillero_Construible : public Casillero{
private:
	Edificio* edificio;
	bool ocupado;
public:
	//PRE: -
	//POST: se crea un casillero vacio
	Casillero_Construible();

	//PRE: -
	//POST: se destruye el casillero, se libera el edificio en caso de estar ocupado
	~Casillero_Construible();

	//PRE: el edificio debe estar ubicado en memoria dinamica
	//POST: se construye el edificio en este casillero, ahor esta ocupado
	void construir_edificio(Edificio* edificio);

	//PRE: -
	//POST: se quita al edificio del casillero y lo devuelve, ahora esta vacio. si el
	//casillero ya estaba vacio, devuelve nullptr.
	Edificio* demoler_edificio();

	//PRE: -
	//POST: devuelve si el casillero esta ocupado
	bool esta_ocupado();

	//PRE: -
	//POST: imprime un saludo por terminal. en caso de tener un edificio, este tambien
	//saluda. de lo contrario, se informa que no hay edificio.
	void saludar();

	//PRE: -
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: -
	//POST: devuelve si el casillero es construible o no.
	bool es_casillero_construible();

	//PRE: -
	//POST: devuelve el nombre del edificio contenido o EDIFICIO_VACIO.
	string obtener_contenido();

};

#endif /* CASILLERO_CASILLEROCONSTRUIBLE_H_ */
