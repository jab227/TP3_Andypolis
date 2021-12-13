#include <iostream>
#include "juego/juego.h"

int main() {
	Juego andypolis;
	Salida salida;
	salida = andypolis.comenzar_juego();
	if (salida != GUARDAR_Y_SALIR)
		salida = andypolis.jugar();
	andypolis.finalizar_juego(salida);
	return 0;
}

