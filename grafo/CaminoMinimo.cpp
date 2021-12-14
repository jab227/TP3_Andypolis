#include "CaminoMinimo.h"

CaminoMinimo::CaminoMinimo(Lista_Grafo<Vertice> *vertices, int **matrizAdyacencia) {
    this -> vertices = vertices;
    this -> matrizAdyacencia = matrizAdyacencia;
    cantidadVertices = vertices -> obtenerCantidadDeElementos();
}
