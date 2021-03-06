#ifndef META_META_H_
#define META_META_H_

#include "../utils/Lista.h"
#include "objetivos/tipos/Armado.h"
#include "objetivos/tipos/Bombardero.h"
#include "objetivos/tipos/Cansado.h"
#include "objetivos/tipos/Constructor.h"
#include "objetivos/tipos/Energetico.h"
#include "objetivos/tipos/Extremista.h"
#include "objetivos/tipos/Letrado.h"
#include "objetivos/tipos/Minero.h"
#include "objetivos/tipos/Monedas.h"
#include "objetivos/tipos/Piedras.h"
#include "objetivos/tipos/BatallaObelisco.h"

const int CANTIDAD_OBJETIVOS = 3;

class Meta {
private:
	Lista<Objetivo*> objetivos;
public:
	//PRE: jugador debe estar bien cargado
	//POST: crea una Meta de CANTIDAD_OBJETIVOS objetivos para el jugador.
	Meta(Jugador* jugador, Mapa* mapa);
	
	//PRE: -
	//POST: elimina los objetivos
	~Meta();

	//PRE: -
	//POST: se actualizan los objetivos del jugador y devuelve true si se cumplieron los 3 objetivos
	bool actualizar_objetivos();

	//PRE: -
	//POST: Devuelve una lista con los objetivos asignados.
	const Lista<Objetivo*>& obtener_objetivos() const;

	//PRE: -
	//POST: muestra los objetivos por pantalla.
	void mostrar_objetivos();

private:
	//PRE: jugador debe estar bien cargado
	//POST: devuelve una lista con todos los objetivos disponibles en el juego
	Lista<Objetivo*> crear_listado(Jugador* jugador, Mapa* mapa);

	//PRE: -
	//POST: libera los objetivos contenidos en la lista asi como tambien la lista.
	void eliminar_listado(Lista<Objetivo*>& listado);
	//PRE: a > 0
	//POS: devuelve un numero aleatorio en el intervalo (a,b)
	std::size_t generar_numero_aleatorio(std::size_t a, std::size_t b);
};

#endif /* META_META_H_ */
