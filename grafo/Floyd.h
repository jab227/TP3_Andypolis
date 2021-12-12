#ifndef GRAFOS_FLOYD_H
#define GRAFOS_FLOYD_H
#include "CaminoMinimo.h"

using namespace std;

class Floyd : public CaminoMinimo{
private:
    int ** matrizCostos;
    int ** matrizCaminos;

    //pre: requiere una matriz de adyacencia bien cargada
    //post: crea la matriz costo inicializandola con los valores de la matriz de adyacencia
    int ** crearMatrizCostos(int ** matrizAdyacencia);

    //post: crea una matriz de caminos
    int ** crearMatrizCaminos();

    //post: libera la memoria de las matrices de costos y caminos
    void liberarMatrices();

    //post: muestra la matriz de costo y de caminos.
    void mostrarMatrices();

    //post:calcula las matrices de costos y caminos.
    void calcularMatrices();

public:
    Floyd(Lista_Grafo<Vertice> *vertices, int ** matrizAdyacencia);

    //post: muestra por pantalla el camino mínimo entre el origen y el destino, detallando su recorrido y peso
    Lista<Coordenada>* caminoMinimo(int origen, int destino) override;

    //post: devuelve el costo necesario para ir del origen al destino
    int energiaCaminoMinimo(int origen, int destino);

    ~Floyd() override;
};


#endif //GRAFOS_FLOYD_H
