#ifndef GRAFOS_VERTICE_H
#define GRAFOS_VERTICE_H

#include "../utils/coordenada.h"

class Vertice {
/*ATRIBUTOS*/
private:
    Coordenada nombre;

/*MÉTODOS*/
public:
    Vertice(Coordenada nombre);

    //post: obtiene el nombre del vertice
    Coordenada obtenerNombre();

    ~Vertice();
};


#endif //GRAFOS_VERTICE_H
