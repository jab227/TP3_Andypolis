#ifndef CASILLERO_CASILLEROCONSTRUIBLE_H_
#define CASILLERO_CASILLEROCONSTRUIBLE_H_

#include "Casillero.h"

class Casillero_Construible: public Casillero{
private:
	Edificio* edificio_;
public:
	//PRE: -
	//POST: Se crea un casillero vacio
	Casillero_Construible();

	//PRE: -
	//POST: Se destruye el casillero, se libera el edificio en caso de estar ocupado
	~Casillero_Construible();

	//PRE: El edificio debe estar ubicado en memoria dinamica
	//POST: se construye el edificio en este casillero, ahor esta ocupado
	Resultado_Chequeos construir_edificio(Edificio* edificio) override;

	//PRE: -
	//POST: En caso de estar ocupado, liberal el edificio y lo deja en nullptr;
	Resultado_Chequeos demoler_edificio() override;

	//PRE: -
	//POST: True si edificio != nullptr, es decir, edificio_ esa inicializado.
	//Q: Creo que podría ser privado si logramos cambiar el telldontask.
	bool esta_ocupado() const override;

	//PRE: -
	//POST: Imprime un saludo del casillero por terminal. Si estaá ocupado, también saludará el edificio; en caso contrario indica que no tiene.
	void saludar() const override;
	
	//PRE: - PROVISORIO
	//POST: Devuelve false.
	bool es_casillero_transitable() override;

	//PRE: -
	//POST: Si esta ocupado, devuelve el nombre del edificio contenido o EDIFICIO_VACIO.
	std::string obtener_contenido() const override;

	//PRE: -
	//POST: 
	//Descomentar en caso de que necesitemos armar una lista de edificios x alguna razon.
	//Edificio* agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos) override;

	//PRE: -
	//POST: Si esta ocupado, devuelve el nombre del edificio contenido o EDIFICIO_VACIO.
	Resultado_Chequeos recoger_material(Almacen* inventario) override;

	//PRE: -
	//POST: Si esta ocupado, pide al edificio de repararse. Devuelve NO_REPARABLE o EXITO.
	Resultado_Chequeos reparar_edificio() override;
	
	//PRE: -
	//POST: Si esta ocupado, disminuye la vida del edificio. 
	Resultado_Chequeos atacar_edificio() override;

	void agregar_material(Material material) override;
};

#endif /* CASILLERO_CASILLEROCONSTRUIBLE_H_ */
