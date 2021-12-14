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

    //post: devuelve una lista de las coordenadas a seguir hasta el destino en caso de que exista el recorido.
    //Si no existe manda un mensaje por terminal
    virtual Lista<Coordenada>* caminoMinimo(int origen, int destino) = 0;

    //post: devuelve la energia que cuesta ir del origen al destino, incluyendo INFINITO
    virtual int energiaCaminoMinimo(int origen, int destino) = 0;

    virtual ~CaminoMinimo() = default;
};


#endif //GRAFOS_CAMINOMINIMO_H
