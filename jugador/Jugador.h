#ifndef JUGADOR_JUGADOR_H_
#define JUGADOR_JUGADOR_H_

#include <string>

#include "../diccionario/diccionario.h"
#include "../empresa/Almacen.h"
#include "../empresa/Mapa.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"

const std::size_t ENERGIA_COMPRAR_BOMBAS = 5;

class Jugador {
	// Atributos
       private:
	const std::size_t id_;
	std::size_t energia_;
	Almacen* inventario_;
	Coordenada posicion_;
	Lista<Coordenada> edificios_;

       public:
	// TODO: Deberiamos pasarle al jugador el inventario y la lsita de
	// coordenadas, ya procesado.
	Jugador(std::size_t id, const Coordenada& coordenada);
	// Destructuor
	virtual ~Jugador() {
		delete inventario_;
		inventario_ = nullptr;
	};
	// Pre: 
	// Pos:
	virtual bool mover(const Coordenada& coordenada, const Mapa& mapa) = 0;
	// PRE: -
	// POST: devuelve el numero del jugador
	std::size_t obtener_jugador() const;

	// PRE: -
	// POST: devuelve la energia del jugador
	std::size_t obtener_energia() const;

	// PRE: -
	// POST: devuelve el inventario del jugador
	Almacen* obtener_inventario() const;
	
	// PRE: -
	// POST: Devuelve la posicoin del jugador 
	Coordenada obtener_posicion() const;
	// PRE: -
	// POST: si hay energia suficiente, devuelve un numero >= 0
	// representando la energia que sobra. Si no alcanza devuelve un numero
	// negativo representando la energia que falta.
	bool energia_suficiente(const std::size_t& energia_requerida) const;

	// PRE: el valor tiene que ser mayor o igual a la energia cambiada de
	// signo. POST: se modifica el valor de la energia, si el numero es
	// positivo se suma y si es negativo se resta dicho valor. Devuelve la
	// energia resultante.
	bool usar_energia(const std::size_t& valor);

	// TODO: Hacer post y pre.
	void agregar_ubicacion(const Coordenada& coordenada);

	std::size_t cantidad_ubicaciones() const;

	Coordenada obtener_ubicacion(const std::size_t indice) const;

	void eliminar_ubicacion(const Coordenada& coordenada);

};

#endif /* JUGADOR_JUGADOR_H_ */
