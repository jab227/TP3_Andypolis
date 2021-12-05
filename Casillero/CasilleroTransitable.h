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
	void recoger_material(Almacen* inventario);

	//PRE: -
	//POST: devuelve si el casillero esta ocupado
	bool esta_ocupado() const;

	//PRE: -
	//POST: imprime un saludo por terminal. en caso de tener un material, este tambien
	//saluda. de lo contrario, se informa que no hay material.
	void saludar() const;

	//PRE: - PROVISORIO
	//POST: devuelve si el casillero es transitable o no.
	bool es_casillero_transitable();

	//PRE: -
	//POST: devuelve el nombre del material contenido o MATERIAL_VACIO.
	void obtener_contenido(Edificio*& edificio) const override;
	void obtener_contenido(Material*& material) const override;
	
	//PRE: -
	//POST:
	bool construir_edificio(Edificio* edificio);

	//Agregar demoler_edificio en inacc y transitables.
	std::string demoler_edificio();

	//PRE: -
	//POST: -
	Edificio* agregar_lista_edificio( Coordenada* coordenada, Lista<string> &lista_nombres,Lista<Lista<Coordenada*>*> &lista_coordenadas) override;
};

#endif /* CASILLERO_CASILLEROTRANSITABLE_H_ */
