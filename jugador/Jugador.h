#ifndef JUGADOR_JUGADOR_H_
#define JUGADOR_JUGADOR_H_

#include <string>
#include "../empresa/Almacen.h"

class Jugador {
//Atributos
private:
	size_t jugador;
	int energia;
	Almacen* inventario;
	//objetivos
//Metodos
public:
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
};

#endif /* JUGADOR_JUGADOR_H_ */
