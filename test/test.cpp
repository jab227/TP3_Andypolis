#include "../utils/coordenada.h"
#include <iostream>

using namespace std;

const string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";


Coordenada devolver_coordenada(int x,int y){
    Coordenada coordenada = Coordenada(x,y);
    return coordenada;
}

int main(){
    Coordenada coord = devolver_coordenada(1,1);

    cout << coord.x() << endl;
    return 0;
}