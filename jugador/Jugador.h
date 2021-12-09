#ifndef JUGADOR_JUGADOR_H_
#define JUGADOR_JUGADOR_H_

#include <string>

#include "../diccionario/diccionario.h"
#include "../empresa/Almacen.h"
#include "../empresa/Mapa.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"

const std::size_t ENERGIA_COMPRAR_BOMBAS = 5;
const std::size_t ENERGIA_MAXIMA = 100;

class Jugador {
	// Atributos
       private:
	const std::size_t id_;
	//TODO: Cuando los construimos, sabemos que energía tienen?
	std::size_t energia_;
	Almacen inventario_;
	Coordenada posicion_;
	Lista<Coordenada> edificios_;

       public:
	// Q: Construimos primero el jugador con las cosas o primero lo ubicamos?
	Jugador(std::size_t id, const Coordenada& coordenada);
	// Destructuor
	virtual ~Jugador() = default; 
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
	Almacen& obtener_inventario();
	
	// Pre: - 
	// Pos: Cambia el almacen del jugador
	void colocar_almacen(const Almacen& inventario);
	
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

	//Devuelve 0 si no encontro, devuelve el indice si lo encontro.
	std::size_t existe_ubicacion( Coordenada coordenada) const;

	//void eliminar_ubicacion(Coordenada);

	bool es_energia_maxima(const std::size_t &energia_recuperada) const;
	
	bool recuperar_energia(const std::size_t &valor);

	void mostrar_construidos(const Mapa* mapa) const;

	void eliminar_ubicacion(const Coordenada& coordenada);

	Resultado_Chequeos tiene_materiales( Lista<Material> materiales) const;
	
	Resultado_Chequeos tiene_materiales_reparar( Lista<Material> materiales) const;

	//TODO: Eliminar construidos de edificios.
	std::size_t cantidad_edificios(const std::string &nombre_edificio,  Mapa* mapa) const;
	
	void cobrar_reparacion( Lista<Material> materiales);

	void usar_lista_materiales( Lista<Material> materiales);

	void recuperar_lista_materiales( Lista<Material> materiales);
	
	void sumar_lista_materiales( Lista<Material> materiales);
	
	//PRE: -
	//POST: devuelve un listado con los materiales producidos por los edificios construidos e imprime
	//por la consola los materiales producidos.
	Lista<Material> obtener_recursos_producidos(Mapa* mapa);

	void mostrar_inventario() const;
	
	void recolectar(Mapa* mapa);
};

#endif /* JUGADOR_JUGADOR_H_ */
