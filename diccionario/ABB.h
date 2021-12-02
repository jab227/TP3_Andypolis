#ifndef ABB_H_
#define ABB_H_
#include "nodo_abb.h"

template <typename T>
class ABB {
       private:
	NodoABB<T>* raiz_;
	// Pre:
	// Pos:
	NodoABB<T>* insertar(NodoABB<T>* nodo, const T& dato) {
		if (nodo == nullptr) {
			nodo = new NodoABB<T>(dato);
		} else if (dato > nodo->dato()) {
			nodo->cambiar_derecha(insertar(nodo->derecha(), dato),
					      nodo);
		} else {
			nodo->cambiar_izquierda(
			    insertar(nodo->izquierda(), dato), nodo);
		}
		return nodo;
	};

	// Pre:
	// Pos:
	NodoABB<T>* buscar(NodoABB<T>* nodo, const T& dato) const {
		if (nodo == nullptr || nodo->dato() == dato) return nodo;
		if (dato > nodo->dato()) return search(nodo->derecha(), dato);
		return search(nodo->izquierda(), dato);
	};

	// Pre:
	// Pos:
	void find_min(NodoABB<T>* nodo, T& min) {
		if (nodo == nullptr)
			return;
		else if (nodo->izquierda() == nullptr)
			min = nodo->dato();
		else
			find_min(nodo->izquierda(), min);
	};

	// Pre:
	// Pos:
	void find_max(NodoABB<T>* nodo, T& max) {
		if (nodo == nullptr)
			return;
		else if (nodo->derecha() == nullptr)
			max = nodo->dato();
		else
			find_max(nodo->derecha(), max);
	};

	// Pre:
	// Pos:
	T sucesor(NodoABB<T>* nodo) {
		T tmp;
		if (nodo->derecha() != nullptr) {
			return find_min(nodo->derecha(), tmp);
		}
		NodoABB<T>* sucesor = nullptr;
		NodoABB<T>* ancestro = raiz_;
		while (ancestro != nodo) {
			if (nodo->dato() < ancestro->dato()) {
				sucesor = ancestro;
				ancestro = ancestro->izquierda();
			} else {
				ancestro = ancestro->derecha();
			}
		}
		return sucesor->dato();
	};

	// Pre:
	// Pos:
	NodoABB<T>* remover(NodoABB<T>* nodo, const T& dato) {
		if (nodo == nullptr) return nullptr;

		if (nodo->dato() == dato) {
			if (nodo->hoja()) {
				delete nodo;
			} else if (nodo->solo_hijo_derecha()) {
				nodo->derecha()->cambiar_padre(nodo->padre());
				NodoABB<T>* aux = nodo;
				nodo = nodo->derecha();
				delete aux;
			} else if (nodo->solo_hijo_izquierda()) {
				nodo->izquierda()->cambiar_padre(nodo->padre());
				NodoABB<T>* aux = nodo;
				nodo = nodo->izquierda();
				delete aux;
			} else {
				T dato_sucesor = sucesor(dato);
				nodo->cambiar_dato(dato_sucesor);
				nodo->cambiar_derecha(
				    remove(nodo->derecha(), dato_sucesor));
			}
		} else if (nodo->dato() < dato) {
			nodo->cambiar_derecha(remover(nodo->derecha(), dato));
		} else {
			nodo->cambiar_izquierda(
			    remover(nodo->izquierda(), dato));
		}
		return nodo;
	};

	// Pre:
	// Pos:
	void borrar_nodos(NodoABB<T>* nodo) {
		if (nodo == nullptr) return;
		delete_all(nodo->izquierda());
		delete_all(nodo->derecha());
		delete nodo;
	};

       public:
	// Pre:
	// Pos:
	ABB() : raiz_(nullptr){};
	// Pre:
	// Pos:
	~ABB() { borrar_nodos(); };
	// Pre:
	// Pos:
	void insertar(const T& dato) { raiz_ = insertar(raiz_, dato); };
	// Pre:
	// Pos:
	void borrar_nodos() { borrar_nodos(raiz_); };
	// Pre:
	// Pos:
	void remover(const T& dato) { raiz_ = remover(raiz_, dato); };
	// Pre:
	// Pos:
	void sucesor(const T& dato, T& sucesor) {
		NodoABB<T>* nodo_dato = search(raiz_, dato);
		T tmp;
		if (nodo_dato == nullptr) {
			return;
		} else {
			tmp = sucesor(nodo_dato);
		}
	};
	// Pre:
	// Pos:
	NodoABB<T>* raiz() const { return raiz_; };
	// Pre:
	// Pos:
	bool vacio() const { return (raiz() == nullptr); };
	// Pre:
	// Pos:
	bool buscar(const T& dato) const {
		NodoABB<T>* result = search(raiz_, dato);
		return result != nullptr;
	};
};

#endif
