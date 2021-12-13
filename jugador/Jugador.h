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
	std::size_t energia_;
	Almacen inventario_;
	Lista<Material> reservas_;
	Coordenada posicion_;
	Lista<Coordenada> edificios_;

public:
	// Constructor
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

	// PRE: -
	// POST: devuelve edificios_ del jugador
	const Lista<Coordenada>& obtener_edificios() const;

	// PRE: -
	// POST: Devuelve la posicion del jugador 
	Coordenada obtener_posicion() const;

	// PRE: -
	// POST: si hay energia suficiente, devuelve true.
	bool es_energia_suficiente(const std::size_t& energia_requerida) const;

	// PRE: el valor tiene que ser mayor o igual a la energia cambiada de
	// signo.
	// POST: se modifica el valor de la energia, si el numero es
	// positivo se suma y si es negativo se resta dicho valor. Devuelve la
	// energia resultante.
	bool usar_energia(const std::size_t& valor);

	//PRE: La coordenada pertenece a un casillero construible ocupado un edificio.
	//POS: Agrega la coordenada a la lista de coordenadas edificios_.
	void agregar_ubicacion(const Coordenada& coordenada);

	//PRE: -
	//POS: Devuelve el indice de la ubicacion de la coordenada en edificios_, en caso de no encontrarlo deuvelve 0.
	std::size_t existe_ubicacion( Coordenada coordenada) const;

	//PRE: -
	//POS: Suma valor a energia_, sin superar ENERGIA_MAXIMA.
	void recuperar_energia(const std::size_t &valor);

	//PRE: -
	//POS: Muestra por terminal la tabla los edificios construidos por el jugador.
	void mostrar_construidos(const Mapa* mapa) const;

	//PRE: -
	//POS: Da de baja la coordenada indicada por interfaz si es que se encuentra en la lista edificios_.
	void eliminar_ubicacion(const Coordenada& coordenada);

	//PRE: Inventario inicializado.
	//POS: Chequea que haya materiales suficientes en el inventario_.
	Resultado_Chequeos tiene_materiales( Lista<Material> materiales) const;
	
	//PRE: Inventario inicializado.
	//POS: Chequea que haya el 25% de los materiales en el inventario_.
	Resultado_Chequeos tiene_materiales_reparar( Lista<Material> materiales) const;

	//PRE: mapa inicializado.
	//POS: Devuelve la cantidad de edificios con el nombre nombre_edificio en la lista edificios_
	std::size_t cantidad_edificios(const std::string &nombre_edificio,  Mapa* mapa) const;
	
	//PRE: inventario inicializado.
	//POS: Descuenta un 25% de materiales al inventario
	void cobrar_reparacion( Lista<Material> materiales);

	//PRE: inventario inicializado.
	//POS: Descuenta el 100% materiales al inventario
	void usar_lista_materiales( Lista<Material> materiales);

	//PRE: inventario inicializado.
	//POS: Suma el 50% de materiales al inventario
	void recuperar_lista_materiales( Lista<Material> materiales);
	
	//PRE: inventario inicializado.
	//POS: Suma el 100% de materiales al inventario
	void sumar_lista_materiales( Lista<Material> materiales); 

	//PRE: -
	//POS: Suma las reserva_ al inventario e imprime por pantalla lo recolectado por el jugador.
	bool recolectar_reservas();
	
	//PRE: mapa != nullptr
	//POS: Carga los materiales producidos por los edificios pertenecientes a edificios_ en reserva_
	// En caso de ya estar cargado, le suma la cantidad al material.
	void producir_materiales(Mapa* mapa);

	//PRE: -
	//POS: Imprime por terminal el inventario del jugador.
	void mostrar_inventario() const;

	//PRE: el mapa debe estar cargado y la coordenada ser valida
	//POS: se mueve el jugador a la coordenada y se recolecta el material en ella
	void mover_a_coordenada(Coordenada coordenada, Mapa* mapa);

	//PRE: jugador inicializado.
	//POS: Devuelve en string el id y las coordenadas e nlas que se ubica.
	std::string a_string();

private:
	//PRE: indice <= edificios_.consulta_largo()
	//POS: Agrega la coordenada a la lista de coordenadas edificios_.
	Coordenada obtener_ubicacion(const std::size_t indice) const;

	//PRE: -
	//POS: Devuelve el largo de edificios_, que es la cantidad de edificios que tiene construidos el jugador.
	std::size_t cantidad_ubicaciones() const;

	//PRE: -
	//POS: Devuelve true si al sumar energia_recuperada a energia_ supera la ENERGIA_MAXIMA.
	bool es_energia_maxima(const std::size_t &energia_recuperada) const;

protected:
	//PRE: el mapa y el grafo debe estar cargado
	//POS: devuelve el resultado de las coordenadas ingresadas por el usuario. si estas son validas, las guarda en
	//coordenadas
	Resultado_Chequeos pedir_coordenadas(Coordenada& coordenada, Mapa* mapa, Grafo* grafo);

	//PRE: el mapa y el grafo debe estar cargado
	//POS: se chequea que la fila y columna sean validas y que se tenga la energia necesaria para moverse hasta ahi.
	Resultado_Chequeos chequeo_coordenadas_moverse(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada, Mapa* mapa, Grafo* grafo);

	//PRE: el mapa debe estar bien cargado
	//POS: devuelve un grafo con los casilleros como nodos con las claves de su coordenada y pesos cargados
	Grafo* cargar_grafo(Mapa* mapa);

	//PRE: -
	//POS: muestra un mensaje en base al resultado y devuelve true si hubo exito o se quiere salir
	bool mostrar_mensaje(Resultado_Chequeos resultado);

	//PRE: -
	//POS: se pide al usuario que ingrese si o no
	std::string pedir_si_no();

	//PRE: el mapa debe estar cargado y la coordenada ser valida
	//POS: devuelve el costo para cada jugador a moverse a ese casillero
	virtual std::size_t obtener_costo_terreno(Coordenada coordenada, Mapa* mapa) = 0;
};
#endif /* JUGADOR_JUGADOR_H_ */
