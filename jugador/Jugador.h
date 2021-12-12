#ifndef JUGADOR_JUGADOR_H_
#define JUGADOR_JUGADOR_H_

#include <string>
#include <iostream>

#include "../diccionario/diccionario.h"
#include "../empresa/Almacen.h"
#include "../empresa/Mapa.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"
#include "../grafo/Grafo.h"
#include "../edificio/Edificio.h"

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

	// Pre: el mapa debe estar bien cargado
	// Pos: se pide al usuario que ingrese coordenadas validas y con energia suficiente.
	//se pide confirmacion para moverse a esa coordenada.
	bool mover(Mapa* mapa);
	// PRE: -
	// POST: devuelve el numero del jugador
	std::size_t obtener_jugador() const;

	// PRE: -
	// POST: devuelve la energia del jugador
	std::size_t obtener_energia() const;

	// PRE: -
	// POST: devuelve el inventario del jugador
	Almacen& obtener_inventario();
	
	const Lista<Coordenada>& obtener_edificios() const;
	// Pre: - 
	// Pos: Cambia el almacen del jugador
	void colocar_almacen(const Almacen& inventario);
	
	// PRE: -
	// POST: Devuelve la posicoin del jugador 
	Coordenada obtener_posicion() const;
	// PRE: -
	// POST: si hay energia suficiente, devuelve un numero entre 0 y 100
	// representando la energia que sobra. Si no alcanza devuelve un numero
	// muy grande, el numero que devuelve cambiado de signo es la energia que falta.
	std::size_t energia_suficiente(const std::size_t& energia_requerida) const;

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

	void iniciar_coordenadas(Mapa* mapa);

	//PRE: el mapa debe estar cargado y la coordenada ser valida
	//POST: se mueve el jugador a la coordenada y se recolecta el material en ella
	void mover_a_coordenada(Coordenada coordenada, Mapa* mapa);

protected:
	//PRE: el mapa y el grafo debe estar cargado
	//POST: devuelve el resultado de las coordenadas ingresadas por el usuario. si estas son validas, las guarda en
	//coordenadas
	Resultado_Chequeos pedir_coordenadas(Coordenada& coordenada, Mapa* mapa, Grafo* grafo);

	//PRE: el mapa y el grafo debe estar cargado
	//POST: se chequea que la fila y columna sean validas y que se tenga la energia necesaria para moverse hasta ahi.
	Resultado_Chequeos chequeo_coordenadas_moverse(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada, Mapa* mapa, Grafo* grafo);

	//PRE: el mapa debe estar bien cargado
	//POST: devuelve un grafo con los casilleros como nodos con las claves de su coordenada y pesos cargados
	Grafo* cargar_grafo(Mapa* mapa);

	//PRE: -
	//POST: muestra un mensaje en base al resultado y devuelve true si hubo exito o se quiere salir
	bool mostrar_mensaje(Resultado_Chequeos resultado);

	//PRE: -
	//POST: se pide al usuario que ingrese si o no
	std::string pedir_si_no();

	//PRE: el mapa debe estar cargado y la coordenada ser valida
	//POST: devuelve el costo para cada jugador a moverse a ese casillero
	virtual std::size_t obtener_costo_terreno(Coordenada coordenada, Mapa* mapa) = 0;
};
#endif /* JUGADOR_JUGADOR_H_ */
