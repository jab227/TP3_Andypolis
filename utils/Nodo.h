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
    Nodo(const T &d);

    //PRE: -
    //POS: se cambia el dato del nodo
    void cambiar_dato(T d);

    //PRE: -
    //POST: se cambia el nodo siguiente
    void cambiar_siguiente(Nodo* pn);

    //PRE: -
    //POS: devuelve la referencia al dato contenido
    T& obtener_dato();

    //PRE: -
    //POST: devuelve el siguiente nodo
    Nodo* obtener_siguiente() const;
};

//Constructor
template <typename T>
Nodo<T>::Nodo(const T &d) {
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
T& Nodo<T>::obtener_dato() {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::obtener_siguiente() const {
    return siguiente;
}

#endif // NODO_H_INCLUDED
