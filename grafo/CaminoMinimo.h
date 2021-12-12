#ifndef GRAFOS_CAMINOMINIMO_H
#define GRAFOS_CAMINOMINIMO_H
#include <string>
#include "ListaGrafo.h"
#include "Vertice.h"
#include <iostream>
#include "../utils/coordenada.h"
#include "../utils/Lista.h"

const int INFINITO = 99999999;

class CaminoMinimo {
//Atributos
protected:
    int ** matrizAdyacencia;
    Lista_Grafo<Vertice> * vertices;
    int cantidadVertices;

//Métodos
public:
    CaminoMinimo(Lista_Grafo<Vertice> * vertices, int** matrizAdyacencia);

    //post: muestra por pantalla el camino mínimo entre el origen y el destino, detallando su recorrido y peso
    virtual Lista<Coordenada>* caminoMinimo(int origen, int destino) = 0;

    virtual int energiaCaminoMinimo(int origen, int destino) = 0;

    virtual ~CaminoMinimo() = default;
};


#endif //GRAFOS_CAMINOMINIMO_H
