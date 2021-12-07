#ifndef CASILLERO_CASILLEROINACCESIBLE_H_
#define CASILLERO_CASILLEROINACCESIBLE_H_

#include "Casillero.h"

class Casillero_Inaccesible: public Casillero{
public:
	//PRE: -
	//POST: Se crea un casillero vacio
	Casillero_Inaccesible();

	//PRE: -
	//POST: Se destruye el casillero
	~Casillero_Inaccesible();

	//PRE: -
	//POST: Devuelve true, ya que no puede ser ocupado por nada.
	bool esta_ocupado() const;

	//PRE: -
	//POST: Imprime un saludo por terminal.
	void saludar() const;

	//PRE: No se deberia llamar a esta funcion, este casillero nunca contiene algo.
	//POST: Devuelve CONTENIDO_VACIO.
	std::string obtener_contenido() const override;
	
	//PRE: - PROVISORIO
	//POST: Devuelve false.
	bool es_casillero_transitable();
	
	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE.
	Resultado_Chequeos construir_edificio(Edificio* edificio);

	//PRE: -
	//POST: - PROVISORIO
	Edificio* agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos) override;

	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE.
	Resultado_Chequeos demoler_edificio();

	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE.
	Resultado_Chequeos reparar_edificio() override;

	//PRE: -
	//POST: Retorna NO_MATERIALES.
	Resultado_Chequeos recoger_material(Almacen* inventario) override;

	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE.
	Resultado_Chequeos atacar_edificio() override;

};

#endif /* CASILLERO_CASILLEROINACCESIBLE_H_ */
