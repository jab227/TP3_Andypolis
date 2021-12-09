#ifndef EDIFICIOS_CASILLERO_H_
#define EDIFICIOS_CASILLERO_H_

#include "../utils/colors.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"
#include "../edificio/Edificio.h"
#include "../empresa/Almacen.h"
#include <string>

const std::string VERDE = BGND_LIGHT_GREEN_46;
const std::string AZUL = BGND_BLUE_12;
const std::string GRIS = BGND_GRAY_245;
const std::string GRIS_OSCURO = BGND_DARK_GRAY_239;
const std::string FIN_COLOR = END_COLOR;
const std::string NEGRO = TXT_DARK_GRAY_233;
const std::string BLANCO = TXT_WHITE_255;
const std::string ROJO = TXT_RED_196;
const std::string MARRON = BGND_BROWN_137;
const std::string CONTENIDO_VACIO = "";
const char BETUN = 'B';
const char CAMINO = 'C';
const char LAGO = 'L';
const char MUELLE = 'M';
const char TERRENO = 'T';

class Casillero
{
private:
	std::string color;

public:
	// PRE: -
	// POST: Se construye un casillero vacio
	Casillero();

	// PRE: -
	// POST: Se construye un casillero con color
	Casillero(std::string color);

	// PRE: -
	// POST: Se destruye el casillero
	virtual ~Casillero();

	// PRE: -
	// POST: Imprime un saludo por pantalla
	virtual void saludar() const = 0;

	//Q: PROVISORIO? Ya que rompe el telldontask.
	// PRE: -
	// POST: Devuelve si el casillero es transitable o no
	virtual bool es_casillero_transitable() = 0;

	// PRE: -
	// POST: Devuelve si el casillero esta ocupado o no
	virtual bool esta_ocupado() const = 0;

	// PRE: -
	// POST: Devuelve el nombre del material o edificio contenido;
	//Q: Es correcto que CasilleroInaccesible devuelve un string vacio? (Dependerá de como usemos, obviamente)
	virtual std::string obtener_contenido() const = 0;

	// PRE: -
	// POST: Devuelve el color del casillero.
	std::string obtener_color();

	// PRE: -
	// POST: -
	//Descomentar en caso de que necesitemos armar una lista de edificios x alguna razon.
	//virtual Edificio *agregar_lista_edificio(Coordenada *coordenada, Lista<Edificio> *&lista_construidos) = 0;

	// PRE: inventario != nullptr;
	// POST: Lepide al casillero que cargue al inventario el material que posee.
	//Q: Le pasamos el jugador o el inventario del jugador o devolvemos el material y que el jugador se haga cargo de sumarlo.
	virtual Resultado_Chequeos recoger_material(Almacen *inventario) = 0;

	// PRE: -
	// POST: Pide al casillero reparar un edficio.
	virtual Resultado_Chequeos reparar_edificio() = 0;

	// PRE: -
	// POST: Pide al casillero atacar un edficio.
	virtual Resultado_Chequeos atacar_edificio() = 0;
	
	// PRE: -
	// POST: Pide al casillero construir un edficio.
	virtual Resultado_Chequeos construir_edificio(Edificio *edificio) = 0;

	// PRE: -
	// POST: Le pide al casillero destruir un edificio.
	virtual Resultado_Chequeos demoler_edificio() = 0;

	virtual	void agregar_material(Material material) = 0;
};

#endif /* EDIFICIOS_CASILLERO_H_ */
