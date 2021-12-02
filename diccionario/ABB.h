#ifndef ABB_H_
#define ABB_H_
#include "nodo_abb.h"

template <typename T>
class ABB {
       private:
	NodoABB<T>* raiz_;

	NodoABB<T>* insertar(NodoABB<T>* nodo, const T& dato){ 
		if (nodo == nullptr) {
			nodo = new NodoABB<T>(dato);
		} else if (dato > nodo->dato()) {
			nodo->cambiar_derecha(insertar(nodo->derecha(), dato), nodo);
		} else {
			nodo->cambiar_izquierda(insertar(nodo->izquierda(), dato), nodo);
		}
		return nodo;
	};
	NodoABB<T>* buscar(NodoABB<T>* nodo, const T& dato) const {};
	T sucesor(NodoABB<T>* nodo){};
	NodoABB<T>* remover(NodoABB<T>* nodo, const T& dato){};

       public:
	ABB() : raiz_(nullptr){};
	~ABB();
	void insertar(const T& dato) { raiz_ = insertar(raiz_, dato); };
	bool buscar(const T& dato) const;
	void remover(const T& dato);
	NodoABB<T>* raiz() const { return raiz_; };
	bool vacio() const { return (raiz() == nullptr); };
};

#endif
