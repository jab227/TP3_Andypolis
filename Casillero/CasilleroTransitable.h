#ifndef CASILLERO_CASILLEROTRANSITABLE_H_
#define CASILLERO_CASILLEROTRANSITABLE_H_

#include "Casillero.h"
#include "../material/Material.h"

class Casillero_Transitable: public Casillero{
private:
	Material material;
public:
	//PRE: -
	//POST: Se crea un casillero transitable vacio con color
	Casillero_Transitable(std::string color);

	//PRE: -
	//POST: Se destruye el casillero, se libera el material en caso de estar ocupado
	~Casillero_Transitable() = default;

	//PRE: El material debe estar ubicado en memoria dinamica
	//POST: Se ocupa el casillero con el material
	void agregar_material(Material material) override;

	//PRE: inventario != nullpointer.
	//POST: Si esta ocupado, se suma el material al inventario y se deja vacío el casillero, devuelve EXITO. Devuelve NO_MATERIALES si no hay ningun material.
	Resultado_Chequeos recoger_material(Material& material_recogido) override;

	//PRE: -
	//POST: Devuelve true si el casillero esta ocupado por un material.
	bool esta_ocupado() const override ;

	//PRE: -
	//POST: Devuelve true.
	bool es_casillero_transitable() override;

	//PRE: -
	//POST: Devuelve el nombre del material contenido o MATERIAL_VACIO.
	std::string obtener_contenido() const override;
	
	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE
	Resultado_Chequeos construir_edificio(Edificio* edificio) override;

	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE
	Resultado_Chequeos demoler_edificio() override;

	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE
	Resultado_Chequeos reparar_edificio(bool reparar = true) override;

	//PRE: -
	//POST: Imprime por pantalla el saludo del material que posee.
	void saludo_material() const;
	
	//PRE: -
	//POST: Devuelve CASILLERO_NO_CONSTRUIBLE
	Resultado_Chequeos atacar_edificio() override;

	//PRE: -
	//POST: devuelve un identificador del casillero.
	virtual char obtener_identificador() = 0;

};

#endif /* CASILLERO_CASILLEROTRANSITABLE_H_ */
