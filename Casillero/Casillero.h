#ifndef EDIFICIOS_CASILLERO_H_
#define EDIFICIOS_CASILLERO_H_

#include "../utils/colors.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"
#include "../edificio/Edificio.h"
#include "../empresa/Almacen.h"
#include <string>

const std::string VERDE = BGND_LIGHT_GREEN_46, AZUL = BGND_BLUE_12, GRIS = BGND_GRAY_245, GRIS_OSCURO = BGND_DARK_GRAY_239, FIN_COLOR = END_COLOR, NEGRO = TXT_DARK_GRAY_233, BLANCO = TXT_WHITE_255, MARRON = BGND_BROWN_137;
const std::string CONTENIDO_VACIO = "";
const char CAMINO = 'C', BETUN = 'B', MUELLE = 'M', INACCESIBLE = 'L', CONSTRUIBLE = 'T';

class Casillero
{
private:
	std::string color;

public:
	// PRE: -
	// POST: se construye un casillero vacio
	Casillero();

	// PRE: -
	// POST: se construye un casillero con color
	Casillero(std::string color);

	// PRE: -
	// POST: se destruye el casillero
	virtual ~Casillero();

	// PRE: -
	// POST: imprime un saludo por pantalla
	virtual void saludar() const = 0;

	// Q: PROVISORIO?
	// PRE: -
	// POST: devuelve si el casillero es transitable o no
	virtual bool es_casillero_transitable() = 0;

	// PRE: -
	// POST: devuelve si el casillero esta ocupado o no
	virtual bool esta_ocupado() const = 0;

	// PRE: -
	// POST: devuelve el nombre del material o edificio contenido;
	// Q: Es correcto que CasilleroInaccesible devuelve un string vacio? (Dependerá de como usemos, obviamente)
	virtual std::string obtener_contenido() const = 0;

	// PRE: -
	// POST: devuelve el color del casillero.
	std::string obtener_color();

	// PRE: -
	// POST:
	virtual Resultado_Chequeos construir_edificio(Edificio *edificio) = 0;

	// PRE: -
	// POST: Si es una celda construible y esta ocupado,se quita al edificio del casillero y lo devuelve, ahora esta vacio.
	// En caso contrario devuelve nullptr;
	virtual Resultado_Chequeos demoler_edificio() = 0;

	// PRE: -
	// POST: Casi seguro que podemos prescindir de este metodo.
	virtual Edificio *agregar_lista_edificio(Coordenada *coordenada, Lista<Edificio> *&lista_construidos) = 0;

	// Q: Le pasamos el jugador o el inventario del jugador o devolvemos el material y que el jugador se haga cargo de sumarlo.
	virtual void recoger_material(Almacen *inventario) = 0;

	virtual Resultado_Chequeos reparar_edificio() = 0;

	virtual Resultado_Chequeos atacar_edificio() = 0;
};

#endif /* EDIFICIOS_CASILLERO_H_ */
