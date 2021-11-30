#ifndef CASILLERO_CASILLEROTRANSITABLE_H_
#define CASILLERO_CASILLEROTRANSITABLE_H_

#include "../Casillero.h"
#include "../Material.h"

class Casillero_Transitable : public Casillero{
private:
	Material* material;
	bool ocupado;
public:
	//PRE: -
	//POST: se crea un casillero vacio
	Casillero_Transitable();

	//PRE: -
	//POST: se destruye el casillero, se libera el material en caso de estar ocupado
	~Casillero_Transitable();

	//PRE: el material debe estar ubicado en memoria dinamica
	//POST: se ocupa el casillero con el material
	void agregar_material(Material* material);

	//PRE: -
	//POST: se quita al material del casillero y lo devuelve, ahora esta vacio. si el
	//casillero ya estaba vacio, devuelve nullptr.
	Material* eliminar_material();

	//PRE: -
	//POST: devuelve si el casillero esta ocupado
	bool esta_ocupado();

	//PRE: -
	//POST: imprime un saludo por terminal. en caso de tener un material, este tambien
	//saluda. de lo contrario, se informa que no hay material.
	void saludar();

	//PRE: -
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: -
	//POST: devuelve si el casillero es construible o no.
	bool es_casillero_construible();

	//PRE: -
	//POST: devuelve el nombre del material contenido o MATERIAL_VACIO.
	string obtener_contenido();
};

#endif /* CASILLERO_CASILLEROTRANSITABLE_H_ */
