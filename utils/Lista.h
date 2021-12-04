#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "Nodo.h"
#include <iostream>

const int NO_ESTA = -1;

template <typename Dato>
class Lista {
    // Atributos
private:
    Nodo<Dato>* primero;
    std::size_t cantidad;

    // Metodos
public:
    //Constructor
    //PRE: -
    //POST: se crea una lista vacia
    Lista();

    //PRE: 1 <= pos <= cantidad + 1
    //POST: agrega d en la posicion de la lista
    void alta(Dato d, std::size_t pos);

    //PRE: -
    //POST: agrega d al final de la lista
    void alta_al_final(Dato d);

    //PRE: 1 <= pos <= cantidad
    //POST: devuelve el dato que esta arriba
    Dato consulta(std::size_t pos) const;

    //PRE: -
    //POST: devuelve el largo de la lista
    std::size_t consulta_largo() const;

    //PRE: 1 <= pos <= cantidad
    //POST: devuelve el dato que esta arriba y decrementa tope
    Dato baja(std::size_t pos);

    //PRE: 1<= pos <= cantidad
    //POST: modifica el dato ubicado en esa posicion
    void modificar(Dato d, std::size_t pos);

    //PRE: -
    //POST: devuelve true si la pila esta vacia, false si no
    bool vacia();

    //PRE: el tipo de dato tiene que poder compararse con el operador =.
    //POST: devuelve el indice en que se encuentra el dato ingresado o NO_ENCONTRADO en caso de
    //no existir el dato
    int buscar_indice(Dato d) const;

    //Destructor
    ~Lista();

private:
    Nodo<Dato>* obtener_nodo(std::size_t pos) const;
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
void Lista<Dato>::alta(Dato dato_nuevo, std::size_t pos) {
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
Dato Lista<Dato>::baja(std::size_t pos) {
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
void Lista<Dato>::modificar(Dato d, std::size_t pos){
	baja(pos);
	alta(d, pos);
}

template <typename Dato>
Dato Lista<Dato>::consulta(std::size_t pos) const{
    Nodo<Dato>* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

template <typename Dato>
std::size_t Lista<Dato>::consulta_largo() const{
	return this -> cantidad;
}

template <typename Dato>
int Lista<Dato>::buscar_indice(Dato d) const{
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
Nodo<Dato>* Lista<Dato>::obtener_nodo(std::size_t pos) const {
    Nodo<Dato>* aux = primero;
    for (std::size_t i = 1; i < pos; i++)
        aux = aux->obtener_siguiente();
    return aux;
}



#endif // LISTA_H_INCLUDED
