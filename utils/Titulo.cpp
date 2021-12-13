#include <iostream>
#include "colors.h"

using namespace std;

const int linea1[] = {0,1,3,2,1,3,1,1,4,2,1,3,1,1,4,3,3,2,1,5,5,2,4};
const int linea2[] = {1,3,1,1,2,2,1,1,1,3,1,2,1,1,1,2,1,3,1,1,1,3,1,1,1,7,1,3,1,4};
const int linea3[] = {5,1,1,1,1,1,1,1,1,3,1,3,1,3,4,2,1,3,1,1,1,7,1,4,3,1};
const int linea4[] = {1,3,1,1,1,2,2,1,1,3,1,3,1,3,1,5,1,3,1,1,1,7,1,7,1};
const int linea5[] = {1,3,1,1,1,3,1,1,4,4,1,3,1,6,3,2,5,1,5,1,4,1};

const string CELESTE =    BGND_LIGHT_BLUE_6, NEGRO = TXT_DARK_GRAY_233, NEGRITA = TXT_BOLD, AMARILLO = BGND_YELLOW_226;
const string COL[] =  {AMARILLO, CELESTE};
const int LARGO = 9*5+8, LINEAS = 5;

const int* MENSAJE[] = {linea1, linea2, linea3, linea4, linea5};

void mostrar_linea(const int* linea){
	int cuenta = 0;
	cout << CELESTE << "   ";
		for(int i = 0; cuenta < LARGO; i++){
		cuenta += linea[i];
		for(int j = 0; j < linea[i]; j++){
			cout << COL[i%2] << ' ';
		}
	}
	cout << CELESTE << "   " << END_COLOR << endl;
}

void titulo(){
	cout << CELESTE + NEGRO + NEGRITA << "                          Bienvenido a:                          " << END_COLOR << endl;
	for(int i = 0; i < LINEAS; i++){
		cout <<  "   ";
		mostrar_linea(MENSAJE[i]);
	}
	cout << CELESTE + NEGRO + NEGRITA << "                    La Batalla por el Obelisco                   " << END_COLOR << endl;
}
