#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

template <typename Dato>

class Nodo {
//Atributos
private:
    Dato dato;
    Nodo* siguiente;

//Metodos
public:
    //constructor
    //PRE: -
    //POS: se construye un nodo y se guarda el dato
    Nodo(Dato d);

    //PRE: -
    //POS: se cambia el dato del nodo
    void cambiar_dato(Dato d);

    //PRE: -
    //POS: se cambia el nodo siguiente
    void cambiar_siguiente(Nodo* pn);

    //PRE: -
    //POS: devuelve el dato contenido
    Dato obtener_dato();

    //PRE: -
    //POS: devuelve el siguiente nodo
    Nodo* obtener_siguiente();
};

//Constructor
template <typename Dato>
Nodo<Dato>::Nodo(Dato d) {
    dato =  d;
    siguiente = 0;
}

template <typename Dato>
void Nodo<Dato>::cambiar_dato(Dato d) {
    dato = d;
}

template <typename Dato>
void Nodo<Dato>::cambiar_siguiente(Nodo* pn) {
    siguiente = pn;
}

template <typename Dato>
Dato Nodo<Dato>::obtener_dato() {
    return dato;
}

template <typename Dato>
Nodo<Dato>* Nodo<Dato>::obtener_siguiente() {
    return siguiente;
}

#endif // NODO_H_INCLUDED
