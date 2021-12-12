#ifndef GRAFOS_NODO_H
#define GRAFOS_NODO_H
#include <string>
#include "../utils/coordenada.h"

using namespace std;

template < typename Tipo >
class NodoGrafo {
/*ATRIBUTOS*/
private:
    Tipo* elemento;
    NodoGrafo<Tipo>* siguiente;

/*MÉTODOS*/
public:
    NodoGrafo(Coordenada nombre);

    //post: devuelve el nodo siguiente.
    NodoGrafo<Tipo>* obtenerSiguiente();

    //post: devuelve el nombre del nodo
    Coordenada obtenerNombre();

    //post: le asigna como siguiente el nodo recibido
    void asignarSiguiente(NodoGrafo<Tipo>* siguiente);

    ~NodoGrafo();
};

template<typename Tipo>
NodoGrafo<Tipo>::NodoGrafo(Coordenada nombre) {
    elemento = new Tipo(nombre);
    siguiente = nullptr;
}

template<typename Tipo>
NodoGrafo<Tipo> *NodoGrafo<Tipo>::obtenerSiguiente() {
    return siguiente;
}

template<typename Tipo>
Coordenada NodoGrafo<Tipo>::obtenerNombre() {
    return elemento -> obtenerNombre();
}

template<typename Tipo>
void NodoGrafo<Tipo>::asignarSiguiente(NodoGrafo<Tipo> *siguiente) {
    this -> siguiente = siguiente;
}

template<typename Tipo>
NodoGrafo<Tipo>::~NodoGrafo() {
    delete elemento;
}


#endif //GRAFOS_NODO_H
