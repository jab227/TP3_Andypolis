#ifndef NODO_DICCIONARIO_H_
#define NODO_DICCIONARIO_H_

#include <iostream>
//        Clave,   Valor
template <class T, class U>
class NodoDiccionario {
       private:
	T clave_;
	U dato_;
	NodoDiccionario<T, U>* izquierda_;
	NodoDiccionario<T, U>* derecha_;
	NodoDiccionario<T, U>* padre_;

       public:
	NodoDiccionario() = default;
	NodoDiccionario(const NodoDiccionario& rhs) = default;
	NodoDiccionario& operator=(const NodoDiccionario& rhs) = default;
	// Pre: -
	// Pos: Construye un nuevo nodo del diccionario.
	NodoDiccionario(T clave, U dato)
	    : clave_(clave),
	      dato_(dato),
	      izquierda_(nullptr),
	      derecha_(nullptr),
	      padre_(nullptr){};
	// Pre: -
	// Pos: Devuelve la clave guardada en el nodo.
	T clave() const { return clave_; };
	// Pre: -
	// Pos: Devuelve el dato guardado en el nodo.
	U dato() const { return dato_; };
	// Pre: -
	// Pos: Devuelve el dato guardado en el nodo por referencia.
	U& dato() { return dato_; };
	// Pre: -
	// Pos: Cambia la clave guardada dentro del nodo.
	void cambiar_clave(const T& clave) { clave_ = clave; };
	// Pre: -
	// Pos: Cambia el dato guardado dentro del nodo.
	void cambiar_dato(const U& dato) { dato_ = dato; };
	// Pre: -
	// Pos: Cambia el nodo a la derecha del nodo actual.
	void cambiar_derecha(NodoDiccionario<T, U>* derecha) {
		derecha_ = derecha;
	};
	// Pre: -
	// Pos: Cambia el nodo a la izquierda del nodo actual.
	void cambiar_izquierda(NodoDiccionario<T, U>* izquierda) {
		izquierda_ = izquierda;
	};
	// Pre: -
	// Pos: Cambia el nodo a la derecha del nodo actual y su nodo
	// padre.
	void cambiar_derecha(NodoDiccionario<T, U>* derecha,
			     NodoDiccionario<T, U>* padre) {
		derecha_ = derecha;
		padre_ = padre;
	};
	// Pre: -
	// Pos: Cambia el nodo a la izquierda del nodo actual y su nodo
	// padre.
	void cambiar_izquierda(NodoDiccionario<T, U>* izquierda,
			       NodoDiccionario<T, U>* padre) {
		izquierda_ = izquierda;
		padre_ = padre;
	};
	// Pre: -
	// Pos: Cambia el nodo padre del nodo actual.
	void cambiar_padre(NodoDiccionario<T,U>* padre) { padre_ = padre; }
	// Pre: -
	// Pos: Devuelve un puntero al nodo de la derecha.
	NodoDiccionario<T,U>* derecha() const { return derecha_; };
	// Pre: -
	// Pos: Devuelve un puntero al nodo de la izquierda.
	NodoDiccionario<T,U>* izquierda() const { return izquierda_; };
	// Pre: -
	// Pos: Devuelve un puntero al nodo padre.
	NodoDiccionario<T,U>* padre() const { return padre_; };
	// Pre: -
	// Pos: Devuelve true si el nodo es una hoja del arbol, false en
	// otro caso.
	bool hoja() const {
		return (derecha() == nullptr && izquierda() == nullptr);
	};
	// Pre: -
	// Pos: Devuelve True si el nodo solo tiene un hijo a la derecha,
	// false en otro caso.
	bool solo_hijo_derecha() const {
		return (derecha() != nullptr && izquierda() == nullptr);
	};
	// Pre: -
	// Pos: Devuelve true si el nodo solo tiene un hijo a la izquierda,
	// false en otro caso
	bool solo_hijo_izquierda() const {
		return (derecha() == nullptr && izquierda() != nullptr);
	}
};

#endif
