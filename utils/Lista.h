#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>

#include "Nodo.h"

//Esto es suponiendo que la lista arranca en 1, entonces si no esta el elemento, 0 puede ser error
const int NO_ESTA = 0;

template <typename T>
class Lista {
	// Atributos
       private:
	Nodo<T>* primero_;
	std::size_t cantidad_;

	// Metodos
       public:
	// Constructor
	// PRE: -
	// POS: se crea una lista vacia
	Lista();
	// Constructor de copia
	// PRE: -
	// POS: Construye la nueva lista a partir de una copia de rhs
	Lista(const Lista<T>& rhs);

	// PRE: -
	// POS: Mueve la informacion de la lista rhs a la lista a la cual
	// se le asigna
	Lista<T>& operator=(const Lista<T>& rhs);

	// PRE: 1 <= pos <= cantidad + 1
	// POS: agrega d en la posicion de la lista
	void alta(const T &d, std::size_t pos);

	// PRE: -
	// POST: agrega d al final de la lista
	void alta_al_final(const T& d);

	// PRE: 1 <= pos <= cantidad
	// POS: devuelve el dato que esta arriba
	const T& consulta(std::size_t pos) const;

	//TODO: Agregar pre,pos condicion
	T& consulta(std::size_t pos);

	// PRE: -
	// POST: devuelve el largo de la lista
	std::size_t consulta_largo() const;

	// PRE: 1 <= pos <= cantidad
	// POS: devuelve el dato que esta arriba y decrementa tope
	T baja(std::size_t pos);

	// PRE: 1<= pos <= cantidad
	// POST: modifica el dato ubicado en esa posicion
	void modificar(T d, std::size_t pos);

	// PRE: -
	// POS: devuelve true si la pila esta vacia, false si no
	bool vacia() const;

	// PRE: el tipo de dato tiene que poder compararse con el operador ==.
	// POST: devuelve el indice en que se encuentra el dato ingresado o
	// NO_ENCONTRADO en caso de no existir el dato
	int buscar_indice(T d);
	
	//WHY: Es usado?
	int buscar_indice(T* d);

	// Destructor
	~Lista();

       private:
	Nodo<T>* obtener_nodo(std::size_t pos) const;
	void swap(Lista<T>& lista);
};

template <typename T>
Lista<T>::Lista() : primero_(nullptr), cantidad_(0) {}

template <typename T>
Lista<T>::Lista(const Lista<T>& rhs) : Lista() {
	Nodo<T>* tmp = rhs.primero_;
	while (tmp != nullptr) {
		alta_al_final(tmp->obtener_dato());
		tmp = tmp->obtener_siguiente();
	}
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& rhs) {
	Lista<T> copia = rhs;
	copia.swap(*this);
	return *this;
}

template <typename T>
bool Lista<T>::vacia() const{
	return (cantidad_ == 0);
}

template <typename T>
void Lista<T>::alta(const T &dato_nuevo, std::size_t pos) {
	Nodo<T>* nuevo = new Nodo<T>(dato_nuevo);
	Nodo<T>* siguiente = primero_;

	if (pos == 1) {
		primero_ = nuevo;
	} else {
		Nodo<T>* anterior = obtener_nodo(pos - 1);
		siguiente = anterior->obtener_siguiente();
		anterior->cambiar_siguiente(nuevo);
	}
	nuevo->cambiar_siguiente(siguiente);
	cantidad_++;
}

template <typename T>
void Lista<T>::alta_al_final(const T &dato_nuevo) {
	this->alta(dato_nuevo, cantidad_ + 1);
}

template <typename T>
T Lista<T>::baja(std::size_t pos) {
	Nodo<T>* baja = primero_;
	if (pos == 1)
		primero_ = baja->obtener_siguiente();
	else {
		Nodo<T>* anterior = obtener_nodo(pos - 1);
		baja = anterior->obtener_siguiente();
		anterior->cambiar_siguiente(baja->obtener_siguiente());
	}
	cantidad_--;
	T d = baja->obtener_dato();
	delete baja;
	return d;
}

template <typename T>
void Lista<T>::modificar(T d, std::size_t pos) {
	baja(pos);
	alta(d, pos);
}

template <typename T>
T& Lista<T>::consulta(std::size_t pos) {
	Nodo<T>* aux = obtener_nodo(pos);
	return aux->obtener_dato();
}

template <typename T>
const T& Lista<T>::consulta(std::size_t pos) const {
	Nodo<T>* aux = obtener_nodo(pos);
	return aux->obtener_dato();
}

template <typename T>
std::size_t Lista<T>::consulta_largo() const{
	return this->cantidad_;
}

template <typename T>
int Lista<T>::buscar_indice(T d) {
	bool encontrado = false;
	int indice = 1;
	// Es mejorable??
	if (this->cantidad_ > 0) {
		Nodo<T>* nodo = this->primero_;
		if (nodo->obtener_dato() == d) {
			encontrado = true;
		}
		while (nodo->obtener_siguiente() != nullptr && !encontrado) {
			nodo = nodo->obtener_siguiente();
			indice++;
			if (nodo->obtener_dato() == d) encontrado = true;
		}
	}
	if (!encontrado) indice = NO_ESTA;
	return indice;
}

template <typename T>
Lista<T>::~Lista() {
	while (!vacia()) baja(1);
}

template <typename T>
Nodo<T>* Lista<T>::obtener_nodo(std::size_t pos) const {
	Nodo<T>* aux = primero_;
	for (std::size_t i = 1; i < pos; i++) aux = aux->obtener_siguiente();
	return aux;
}

template <typename T>
void Lista<T>::swap(Lista<T>& lista) {
	using std::swap;
	swap(primero_, lista.primero_);
	swap(cantidad_, lista.cantidad_);
}

#endif	// LISTA_H_INCLUDED
