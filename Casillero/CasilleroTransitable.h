#ifndef CASILLERO_CASILLEROTRANSITABLE_H_
#define CASILLERO_CASILLEROTRANSITABLE_H_

#include "Casillero.h"
#include "../material/Material.h"

class Casillero_Transitable: public Casillero{
private:
	Material* material;
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

	//PRE: - PROVISORIO
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: - ELIMINAR?
	//POST: devuelve el nombre del material contenido o MATERIAL_VACIO.
	std::string obtener_contenido();
	
	//PRE: -
	//POST:
	bool construir_edificio(Edificio* edificio);

	//Agregar demoler_edificio en inacc y transitables.
	Edificio* demoler_edificio();

	//PRE: -
	//POST: -
	Edificio* agregar_lista_edificio( std::size_t* coordenadas, Lista<std::string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas);
};

#endif /* CASILLERO_CASILLEROTRANSITABLE_H_ */
