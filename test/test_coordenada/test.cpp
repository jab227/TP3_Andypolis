#include "../../utils/coordenada.h"
#include <iostream>
using namespace std;

const std::string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const std::string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

Coordenada crear_coordenada3(size_t x = 3, size_t y = 3){
    return Coordenada(x,y);
}

int main(){
    Coordenada coordenada1 =  Coordenada(1,1);
    Coordenada coordenada2 =  Coordenada(2,2);
    Coordenada coordenada3 =  crear_coordenada3();
    Coordenada coordenada4 =  crear_coordenada3(4,4);

    cout << coordenada1.x() << endl;
    cout << coordenada1.y() << endl;
    cout << coordenada1.a_string() << endl;

    cout << coordenada2.x() << endl;
    cout << coordenada2.y() << endl;
    cout << coordenada2.a_string() << endl;

    cout << coordenada3.x() << endl;
    cout << coordenada3.y() << endl;
    cout << coordenada3.a_string() << endl;

    cout << coordenada4.x() << endl;
    cout << coordenada4.y() << endl;
    cout << coordenada4.a_string() << endl;
    
    cout << (coordenada1==coordenada2) << endl;
    cout << (coordenada1!=coordenada2) << endl;

    return 0;
}