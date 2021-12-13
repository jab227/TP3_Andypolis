#include <iostream>
#include "colors.h"
#include "Titulos.h"

using namespace std;

const int bienvenida_1[] = {0,1,3,2,1,3,1,1,4,2,1,3,1,1,4,3,3,2,1,5,5,2,4};
const int bienvenida_2[] = {1,3,1,1,2,2,1,1,1,3,1,2,1,1,1,2,1,3,1,1,1,3,1,1,1,7,1,3,1,4};
const int bienvenida_3[] = {5,1,1,1,1,1,1,1,1,3,1,3,1,3,4,2,1,3,1,1,1,7,1,4,3,1};
const int bienvenida_4[] = {1,3,1,1,1,2,2,1,1,3,1,3,1,3,1,5,1,3,1,1,1,7,1,7,1};
const int bienvenida_5[] = {1,3,1,1,1,3,1,1,4,4,1,3,1,6,3,2,5,1,5,1,4,1};

const int jugador1_1[] = {0,4,1,1,1,3,1,1,5,1,5,1,4,2,5,1,5,5,1,1};
const int jugador1_2[] = {0,4,1,1,1,3,1,1,1,5,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,4,2,1};
const int jugador1_3[] = {0,4,1,1,1,3,1,1,1,1,3,1,5,1,1,3,1,1,1,3,1,1,4,6,1,1};
const int jugador1_4[] = {0,1,1,2,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,2,1,6,1,1};
const int jugador1_5[] = {0,1,4,1,5,1,5,1,1,3,1,1,4,2,5,1,1,3,1,5,1,1};

const int jugador2_1[] = {0,4,1,1,1,3,1,1,5,1,5,1,4,2,5,1,5,4,2,1};
const int jugador2_2[] = {0,4,1,1,1,3,1,1,1,5,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,3,1,2,1};
const int jugador2_3[] = {0,4,1,1,1,3,1,1,1,1,3,1,5,1,1,3,1,1,1,3,1,1,4,6,1,1};
const int jugador2_4[] = {0,1,1,2,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,2,1,5,1,2};
const int jugador2_5[] = {0,1,4,1,5,1,5,1,1,3,1,1,4,2,5,1,1,3,1,3,4};

const string CELESTE =    BGND_LIGHT_BLUE_6, NEGRO = TXT_DARK_GRAY_233, NEGRITA = TXT_BOLD, AMARILLO = BGND_YELLOW_226;
const string COL[] =  {AMARILLO, CELESTE};
const int LARGO_BIENVENIDA = 9*5+8, LARGO_JUGADORES = 48, LINEAS = 5;

const int* BIENVENIDA[] = {bienvenida_1, bienvenida_2, bienvenida_3, bienvenida_4, bienvenida_5};
const int* JUGADOR_1[] = {jugador1_1, jugador1_2, jugador1_3, jugador1_4, jugador1_5};
const int* JUGADOR_2[] = {jugador2_1, jugador2_2, jugador2_3, jugador2_4, jugador2_5};

void mostrar_linea(const int* linea, int largo){
	int cuenta = 0;
	cout << CELESTE << "   ";
		for(int i = 0; cuenta < largo; i++){
		cuenta += linea[i];
		for(int j = 0; j < linea[i]; j++){
			cout << COL[i%2] << ' ';
		}
	}
	cout << CELESTE << "   " << END_COLOR << endl;
}

void mensaje_bienvenida(){
	cout << CELESTE + NEGRO + NEGRITA << "                          Bienvenido a:                          " << END_COLOR << endl;
	for(int i = 0; i < LINEAS; i++){
		cout <<  "   ";
		mostrar_linea(BIENVENIDA[i], LARGO_BIENVENIDA);
	}
	cout << CELESTE + NEGRO + NEGRITA << "                    La Batalla por el Obelisco                   " << END_COLOR << endl;
}

void mensaje_jugador_1(){
	cout << CELESTE + NEGRO + NEGRITA << "                           Ganador el:                      " << END_COLOR << endl;
	for(int i = 0; i < LINEAS; i++){
		cout <<  "   ";
		mostrar_linea(JUGADOR_1[i], LARGO_JUGADORES);
	}
	cout << CELESTE + NEGRO + NEGRITA << "                                                            " << END_COLOR << endl;
}

void mensaje_jugador_2(){
	cout << CELESTE + NEGRO + NEGRITA << "                           Ganador el:                      " << END_COLOR << endl;
	for(int i = 0; i < LINEAS; i++){
		cout <<  "   ";
		mostrar_linea(JUGADOR_2[i], LARGO_JUGADORES);
	}
	cout << CELESTE + NEGRO + NEGRITA << "                                                            " << END_COLOR << endl;
}
