#ifndef EDIFICIOS_CASILLERO_H_
#define EDIFICIOS_CASILLERO_H_

#include <string>
#include "colors.h"

const std::string VERDE = BGND_LIGHT_GREEN_46, AZUL = BGND_BLUE_12, GRIS = BGND_GRAY_245, FIN_COLOR = END_COLOR, NEGRO = TXT_DARK_GRAY_233;
const std::string CONTENIDO_VACIO = "";
const char TRANSITABLE = 'C', INACCESIBLE = 'L' , CONSTRUIBLE = 'T';

class Casillero {
protected:
	std::string color;
public:
	//PRE: -
	//POST: se construye un casillero vacio
	Casillero();

	//PRE: -
	//POST: se destruye el casillero
	virtual ~Casillero() = 0;

	//PRE: -
	//POST: imprime un saludo por pantalla
	virtual void saludar() = 0;

	//PRE: -
	//POST: devuelve si el casillero es transitable o no
	virtual bool es_casillero_transitable() = 0;

	//PRE: -
	//POST: devuelve si el casillero es construible o no
	virtual bool es_casillero_construible() = 0;

	//PRE: -
	//POST: devuelve si el casillero esta ocupado o no
	virtual bool esta_ocupado() = 0;

	//PRE: -
	//POST: devuelve el contenido del casillero en caso de estar ocupado o CASILLERO_VACIO en caso contrario.
	virtual std::string obtener_contenido() = 0;

	//PRE: -
	//POST: devuelve el color del casillero.
	std::string obtener_color();
};

#endif /* EDIFICIOS_CASILLERO_H_ */
