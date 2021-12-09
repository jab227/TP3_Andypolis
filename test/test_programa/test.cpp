#include <iostream>
#include "../utils/Lista.h"
#include "../utils/coordenada.h"

int main(){
    Lista<Coordenada> lista = Lista<Coordenada>();
    
    Coordenada coor = Coordenada(1,1);
    coor = Coordenada(1,1);
    lista.alta_al_final(coor);
    coor = Coordenada(2,2);
    lista.alta_al_final(coor);
    coor = Coordenada(3,3);
    lista.alta_al_final(coor);
    
    
    for(std::size_t i = 1; i < 4; i++)
        std::cout << lista.consulta(i).x() << std::endl;
    
    return 0;
}