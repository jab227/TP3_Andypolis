#ifndef EDIFICIOS_CASILLERO_H_
#define EDIFICIOS_CASILLERO_H_

#include "../utils/colors.h"
#include "../utils/Lista.h"
#include "../edificio/Edificio.h"
#include "../empresa/Almacen.h"
#include <string>

const std::string VERDE = BGND_LIGHT_GREEN_46, AZUL = BGND_BLUE_12, GRIS = BGND_GRAY_245, FIN_COLOR = END_COLOR, NEGRO = TXT_DARK_GRAY_233;
const std::string CONTENIDO_VACIO = "";
const char TRANSITABLE = 'C', INACCESIBLE = 'L' , CONSTRUIBLE = 'T';

//TODO: Heredados del printer. Colocar en el lugar correspondiente.S
static const std::string RESET = "\e\[0m";
static const std::string BOLD = "\e\[1m";
static const std::string UNDERLINE = "\e\[4m";
static const std::string CLEAR = "\e\[H\e[2J";
static const std::string GREEN = "\e\[32m";
static const std::string RED = "\e\[31m";
static const std::string YELLOW = "\e\[33m";
static const std::string BLUE = "\e\[34m";

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
	virtual ~Casillero() = 0;

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
	//POST: devuelve el contenido del casillero en caso de estar ocupado o CASILLERO_VACIO en caso contrario.
	virtual void obtener_contenido(Edificio*& edificio) const = 0;
	//PRE: -
	//POST: devuelve el contenido del casillero en caso de estar ocupado o CASILLERO_VACIO en caso contrario.
	virtual void obtener_contenido(Material*& material) const = 0;

	//PRE: -
	//POST: devuelve el color del casillero.
	std::string obtener_color();

	//PRE: -
	//POST:
	virtual bool construir_edificio(Edificio* edificio) = 0;

	//PRE: -
	//POST: Si es una celda construible y esta ocupado,se quita al edificio del casillero y lo devuelve, ahora esta vacio. 
	//En caso contrario devuelve nullptr;
	virtual std::string demoler_edificio() = 0;

	//PRE: -
	//POST: -
	virtual Edificio* agregar_lista_edificio(std::size_t fila, std::size_t columna, Lista<std::string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas) = 0;

	//WHY: Le pasamos el jugador o el inventario del jugador?
	virtual void recoger_material(Almacen* inventario);
};

#endif /* EDIFICIOS_CASILLERO_H_ */
