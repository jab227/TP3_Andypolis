#ifndef JUGADOR_JUGADOR_H_
#define JUGADOR_JUGADOR_H_

#include <string>
#include "../empresa/Almacen.h"
#include "../utils/Lista.h"
#include "../utils/LecturaArchivos.h"

const std::size_t ENERGIA_COMPRAR_BOMBAS = 5;

class Jugador {
//Atributos
private:
	size_t jugador;
	int energia;
	Almacen* inventario;
	//TODO: Objetivos
	//TODO: Coordenada.
	Lista<int> ubicaciones_fila;
	Lista<int> ubicaciones_columna;
//Metodos
public:
	//TODO: Deberiamos pasarle al jugador el inventario y la lsita de coordenadas, ya procesado.
	Jugador(size_t jugador);
	~Jugador();

	//PRE: -
	//POST: devuelve el numero del jugador
	size_t obtener_jugador();

	//PRE: -
	//POST: devuelve la energia del jugador
	int obtener_energia();

	//PRE: energia_necesaria debe ser un numero positivo
	//POST: si hay energia suficiente, devuelve un numero >= 0 representando la energia que sobra.
	//Si no alcanza devuelve un numero negativo representando la energia que falta.
	int energia_suficiente(int energia_necesaria);


	//PRE: el valor tiene que ser mayor o igual a la energia cambiada de signo.
	//POST: se modifica el valor de la energia, si el numero es positivo se suma y si es negativo
	//se resta dicho valor. Devuelve la energia resultante.
	int modificar_energia(int valor);

	//PRE: -
	//POST: devuelve el inventario del jugador
	Almacen* obtener_inventario();

	//TODO: Hacer post y pre.
	void agregar_ubicacion(int fila, int columna);

	int obtener_largo_ubicaciones();

	void obtener_ubicacion(int ubicacion, int &fila, int &columna);

	void eliminar_ubicacion(int fila, int columna);

	void comprar_bombas();

private:
	std::size_t pedir_bombas_validas();
};

#endif /* JUGADOR_JUGADOR_H_ */
