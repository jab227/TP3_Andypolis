#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

template <typename T>

class Nodo {
//Atributos
private:
    T dato;
    Nodo* siguiente;

//Metodos
public:
    //constructor
    //PRE: -
    //POS: se construye un nodo y se guarda el dato
    Nodo(T d);

    //PRE: -
    //POS: se cambia el dato del nodo
    void cambiar_dato(T d);

    //PRE: -
    //POS: se cambia el nodo siguiente
    void cambiar_siguiente(Nodo* pn);

    //PRE: -
    //POS: devuelve el dato contenido
    T obtener_dato();

    //PRE: -
    //POS: devuelve el siguiente nodo
    Nodo* obtener_siguiente();
};

//Constructor
template <typename T>
Nodo<T>::Nodo(T d) {
    dato =  d;
    siguiente = 0;
}

template <typename T>
void Nodo<T>::cambiar_dato(T d) {
    dato = d;
}

template <typename T>
void Nodo<T>::cambiar_siguiente(Nodo* pn) {
    siguiente = pn;
}

template <typename T>
T Nodo<T>::obtener_dato() {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::obtener_siguiente() {
    return siguiente;
}

#endif // NODO_H_INCLUDED
