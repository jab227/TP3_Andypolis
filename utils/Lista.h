#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
#include "Nodo.h"

const int NO_ESTA = -1;

template <typename Dato>
class Lista {
    // Atributos
private:
    Nodo<Dato>* primero;
    int cantidad;

    // Metodos
public:
    //Constructor
    //PRE: -
    //POS: se crea una lista vacia
    Lista();

    //PRE: 1 <= pos <= cantidad + 1
    //POS: agrega d en la posicion de la lista
    void alta(Dato d, int pos);

    //PRE: -
    //POST: agrega d al final de la lista
    void alta_al_final(Dato d);

    //PRE: 1 <= pos <= cantidad
    //POS: devuelve el dato que esta arriba
    Dato consulta(int pos);

    //PRE: -
    //POST: devuelve el largo de la lista
    int consulta_largo();

    //PRE: 1 <= pos <= cantidad
    //POS: devuelve el dato que esta arriba y decrementa tope
    Dato baja(int pos);

    //PRE: 1<= pos <= cantidad
    //POST: modifica el dato ubicado en esa posicion
    void modificar(Dato d, int pos);

    //PRE: -
    //POS: devuelve true si la pila esta vacia, false si no
    bool vacia();

    //PRE: el tipo de dato tiene que poder compararse con el operador =.
    //POST: devuelve el indice en que se encuentra el dato ingresado o NO_ENCONTRADO en caso de
    //no existir el dato
    int buscar_indice(Dato d);

    //Destructor
    ~Lista();

private:
    Nodo<Dato>* obtener_nodo(int pos);
};

template <typename Dato>
Lista<Dato>::Lista() {
    primero = 0;
    cantidad = 0;
}

template <typename Dato>
bool Lista<Dato>::vacia() {
    return (cantidad == 0);
}

template <typename Dato>
void Lista<Dato>::alta(Dato dato_nuevo, int pos) {
    Nodo<Dato>* nuevo = new Nodo<Dato>(dato_nuevo);
    Nodo<Dato>* siguiente = primero;

    if (pos == 1) {
        primero = nuevo;
    }
    else {
        Nodo<Dato>* anterior = obtener_nodo(pos - 1);
        siguiente = anterior->obtener_siguiente();
        anterior->cambiar_siguiente(nuevo);
    }
    nuevo->cambiar_siguiente(siguiente);
    cantidad++;
}

template <typename Dato>
void Lista<Dato>::alta_al_final(Dato dato_nuevo) {
    this -> alta(dato_nuevo, this -> cantidad + 1);
}


template <typename Dato>
Dato Lista<Dato>::baja(int pos) {
    Nodo<Dato>* baja = primero;
    if (pos == 1)
        primero = baja->obtener_siguiente();
    else {
        Nodo<Dato>* anterior = obtener_nodo(pos - 1);
        baja = anterior->obtener_siguiente();
        anterior->cambiar_siguiente(baja->obtener_siguiente());
    }
    cantidad--;
    Dato d = baja->obtener_dato();
    delete baja;
    return d;
}

template <typename Dato>
void Lista<Dato>::modificar(Dato d, int pos){
	baja(pos);
	alta(d, pos);
}

template <typename Dato>
Dato Lista<Dato>::consulta(int pos) {
    Nodo<Dato>* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

template <typename Dato>
int Lista<Dato>::consulta_largo(){
	return this -> cantidad;
}

template <typename Dato>
int Lista<Dato>::buscar_indice(Dato d){
	bool encontrado = false;
	int indice = 1;
    //Es mejorable??
	if(this->cantidad > 0){
		Nodo<Dato>* nodo = this->primero;
		if(nodo->obtener_dato() == d){
			encontrado = true;
		}
		while(nodo->obtener_siguiente() != nullptr && !encontrado){
			nodo = nodo->obtener_siguiente();
			indice++;
			if(nodo->obtener_dato() == d)
				encontrado = true;
		}
	}
	if(!encontrado)
		indice = NO_ESTA;
	return indice;
}

template <typename Dato>
Lista<Dato>::~Lista() {
    while (! vacia())
        baja(1);
}

template <typename Dato>
Nodo<Dato>* Lista<Dato>::obtener_nodo(int pos) {
    Nodo<Dato>* aux = primero;
    for (int i = 1; i < pos; i++)
        aux = aux->obtener_siguiente();
    return aux;
}



#endif // LISTA_H_INCLUDED
