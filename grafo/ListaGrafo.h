#ifndef GRAFOS_LISTA_H
#define GRAFOS_LISTA_H
#include <string>
#include "NodoGrafo.h"
#include "../utils/coordenada.h"

using namespace std;

const int POSICION_NO_ENCONTRADA = -1;
const Coordenada NOMBRE_NO_ENCONTRADO(-1, -1);

template < typename Tipo >
class Lista_Grafo{
/*ATRIBUTOS*/
private:
    int cantidadDeElementos;
    NodoGrafo<Tipo>* primero;
    NodoGrafo<Tipo>* ultimo;

/*MÉTODOS*/
public:
    Lista_Grafo();

    //post: devuelve la cantidad de elementos que tiene la lista
    int obtenerCantidadDeElementos();

    //post: devuelve la posicion en la que se encuentra el nombre que recibe o -1 si no lo encuentra
    int obtenerPosicion(Coordenada nombre);

    //post: devuelve el  nombre que se encuentra en la posicion recibida o NOMBRE_NO_ENCONTRADO si no lo encuentra
    Coordenada obtenerNombre(int posicion);

    //post: agrega un nuevo elemento a la lista
    void agregar(Coordenada nuevoElemento);

    ~Lista_Grafo();
};

template < typename Tipo >
Lista_Grafo<Tipo>::Lista_Grafo(){
    cantidadDeElementos = 0;
    ultimo = nullptr;
    primero =  nullptr;
}

template < typename Tipo >
int Lista_Grafo<Tipo>::obtenerCantidadDeElementos(){
    return cantidadDeElementos;
}

template < typename Tipo >
int Lista_Grafo<Tipo>::obtenerPosicion(Coordenada nombre) {
    bool elementoEncontrado = false;
    int i = 0;
    NodoGrafo<Tipo>* auxiliar = primero;

    while(!elementoEncontrado && i < cantidadDeElementos){
        if(auxiliar -> obtenerNombre() == nombre){
            elementoEncontrado = true;
        }
        i++;
        auxiliar = auxiliar -> obtenerSiguiente();
    }

    if(!elementoEncontrado){
        return POSICION_NO_ENCONTRADA;
    }
    return i - 1;
}

template < typename Tipo >
void Lista_Grafo<Tipo>::agregar(Coordenada nuevoElemento) {
    NodoGrafo<Tipo>* nuevoNodo = new NodoGrafo<Tipo>(nuevoElemento);
    if(primero == nullptr){
        primero = nuevoNodo;
        ultimo = primero;
    } else {
        ultimo -> asignarSiguiente(nuevoNodo);
        ultimo = nuevoNodo;
    }
    cantidadDeElementos++;
}

template<typename Tipo>
Lista_Grafo<Tipo>::~Lista_Grafo() {
    NodoGrafo<Tipo>* siguiente;
    while(primero != nullptr){
        siguiente = primero -> obtenerSiguiente();
        delete primero;
        primero = siguiente;
    }
}

template<typename Tipo>
Coordenada Lista_Grafo<Tipo>::obtenerNombre(int posicion) {
    int i = 0;
    NodoGrafo<Tipo>* auxiliar = primero;

    if(posicion > cantidadDeElementos){
        return NOMBRE_NO_ENCONTRADO;
    }

    while(i != posicion - 1){
        auxiliar = auxiliar -> obtenerSiguiente();
        i++;
    }
    return auxiliar -> obtenerNombre();
}

#endif //GRAFOS_LISTA_H
