#ifndef NODO_ABB_H_
#define NODO_ABB_H_

template <typename T>
class NodoABB {
       private:
	T dato_;
	NodoABB<T>* izquierda_;
	NodoABB<T>* derecha_;
	NodoABB<T>* padre_;

       public:
	// Pre: -
	// Pos: Construye un nuevo nodo del arbol binario.
	NodoABB(const T& dato)
	    : dato_(dato),
	      izquierda_(nullptr),
	      derecha_(nullptr),
	      padre_(nullptr){};
	// Pre: -
	// Pos: Devuelve el dato guardado en el nodo.
	T dato() const { return dato_; };
	// Pre: -
	// Pos: Cambia el dato guardado dentro del nodo.
	void cambiar_dato(const T& dato) { dato_ = dato; };
	// Pre: -
	// Pos: Cambia el nodo a la derecha del nodo actual.
	void cambiar_derecha(NodoABB<T>* derecha) { derecha_ = derecha; };
	// Pre: -
	// Pos: Cambia el nodo a la izquierda del nodo actual.
	void cambiar_izquierda(NodoABB<T>* izquierda) {
		izquierda_ = izquierda;
	};
	// Pre: - 
	// Pos: Cambia el nodo a la derecha del nodo actual y su nodo
	// padre.
	void cambiar_derecha(NodoABB<T>* derecha, NodoABB<T>* padre) {
		derecha_ = derecha;
		padre_ = padre;
	};
	// Pre: -
	// Pos: Cambia el nodo a la izquierda del nodo actual y su nodo
	// padre.
	void cambiar_izquierda(NodoABB<T>* izquierda, NodoABB<T>* padre) {
		izquierda_ = izquierda;
		padre_ = padre;
	};
	// Pre: -
	// Pos: Cambia el nodo padre del nodo actual.
	void cambiar_padre(NodoABB<T>* padre) { padre_ = padre; }
	// Pre: -
	// Pos: Devuelve un puntero al nodo de la derecha.
	NodoABB<T>* derecha() const { return derecha_; };
	// Pre: -
	// Pos: Devuelve un puntero al nodo de la izquierda.
	NodoABB<T>* izquierda() const { return izquierda_; };
	// Pre: -
	// Pos: Devuelve un puntero al nodo padre.
	NodoABB<T>* padre() const { return padre_; };
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
		return (derecha() != nullptr && izquieda() == nullptr);
	};
	// Pre: -
	// Pos: Devuelve true si el nodo solo tiene un hijo a la izquierda,
	// false en otro caso
	bool solo_hijo_izquierda() const {
		return (derecha() == nullptr && izquieda() != nullptr);
	}
};

#endif
