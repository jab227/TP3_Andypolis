#ifndef CASILLERO_CASILLEROCONSTRUIBLE_H_
#define CASILLERO_CASILLEROCONSTRUIBLE_H_

#include "Casillero.h"

class Casillero_Construible: public Casillero{
private:
	Edificio* edificio_;
public:
	//PRE: -
	//POST: se crea un casillero vacio
	Casillero_Construible();

	//PRE: -
	//POST: se destruye el casillero, se libera el edificio en caso de estar ocupado
	~Casillero_Construible();

	//PRE: el edificio debe estar ubicado en memoria dinamica
	//POST: se construye el edificio en este casillero, ahor esta ocupado
	Resultado_Chequeos construir_edificio(Edificio* edificio);

	//PRE: -
	//POST: se quita al edificio del casillero y lo devuelve, ahora esta vacio. si el
	//casillero ya estaba vacio, devuelve nullptr.
	std::string demoler_edificio();

	//PRE: -
	//POST: devuelve si el casillero esta ocupado
	bool esta_ocupado() const;

	//PRE: -
	//POST: imprime un saludo por terminal. en caso de tener un edificio, este tambien
	//saluda. de lo contrario, se informa que no hay edificio.
	void saludar() const;
	
	//PRE: - PROVISORIO
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: -
	//POST: devuelve el nombre del edificio contenido o EDIFICIO_VACIO.
	void obtener_contenido(Edificio*& edificio) const override;
	
	//PRE: -
	//POST: devuelve nullpointer
	void obtener_contenido(Material*& material) const override;

	//PRE: -
	//POST: SE USA??
	Edificio* agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos) override;

	void recoger_material(Almacen* inventario) override;
};

#endif /* CASILLERO_CASILLEROCONSTRUIBLE_H_ */
