#ifndef EDIFICIOS_CASILLERO_H_
#define EDIFICIOS_CASILLERO_H_

#include "../utils/colors.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"
#include "../edificio/Edificio.h"
#include "../empresa/Almacen.h"
#include <string>

const std::string VERDE = BGND_LIGHT_GREEN_46, AZUL = BGND_BLUE_12, GRIS = BGND_GRAY_245, FIN_COLOR = END_COLOR, NEGRO = TXT_DARK_GRAY_233;
const std::string CONTENIDO_VACIO = "";
const char TRANSITABLE = 'C', INACCESIBLE = 'L' , CONSTRUIBLE = 'T';

class Casillero {
private:
	std::string color;
public:
	//PRE: -
	//POST: se construye un casillero vacio
	Casillero();
	
	//PRE: -
	//POST: se construye un casillero con color
	Casillero(std::string color);

	//PRE: -
	//POST: se destruye el casillero
	virtual ~Casillero();

	//PRE: -
	//POST: imprime un saludo por pantalla
	virtual void saludar() const = 0;

	//PRE: - PROVISORIO
	//POST: devuelve si el casillero es transitable o no
	virtual bool es_casillero_transitable() = 0;

	//PRE: -
	//POST: devuelve si el casillero esta ocupado o no
	virtual bool esta_ocupado() const = 0;

	//PRE: -
	//POST: devuelve el nombre del material o edificio contenido;
	virtual std::string obtener_contenido() const = 0;

	//PRE: -
	//POST: devuelve el color del casillero.
	std::string obtener_color();

	//PRE: -
	//POST:
	virtual Resultado_Chequeos construir_edificio(Edificio* edificio) = 0;

	//PRE: -
	//POST: Si es una celda construible y esta ocupado,se quita al edificio del casillero y lo devuelve, ahora esta vacio. 
	//En caso contrario devuelve nullptr;
	virtual Resultado_Chequeos demoler_edificio() = 0;

	//PRE: -
	//POST: -
	virtual Edificio* agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos) = 0;

	//WHY: Le pasamos el jugador o el inventario del jugador?
	virtual void recoger_material(Almacen* inventario) = 0;
};

#endif /* EDIFICIOS_CASILLERO_H_ */
