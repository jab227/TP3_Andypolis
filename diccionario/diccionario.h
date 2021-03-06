#ifndef DICCIONARIO_H_
#define DICCIONARIO_H_

#include "../utils/Lista.h"
#include "nodo_diccionario.h"
#include <algorithm>
// La clave deberia mantenerse en algun tipo basico (incluido string).
//        Clave,   Valor
template <class T, class U>
class Diccionario {
	NodoDiccionario<T, U>* raiz_;

	// Pre: La clave no se tiene que repetir.
	// Pos: Inserta un nuevo nodo al diccionario.
	NodoDiccionario<T, U>* insertar(NodoDiccionario<T, U>* nodo,
					const T& clave, const U& dato) {
		if (nodo == nullptr) {
			nodo = new NodoDiccionario<T, U>(clave, dato);
		} else if (clave > nodo->clave()) {
			nodo->cambiar_derecha(
			    insertar(nodo->derecha(), clave, dato), nodo);
		} else {
			nodo->cambiar_izquierda(
			    insertar(nodo->izquierda(), clave, dato), nodo);
		}
		return nodo;
	};
	// Pre: -
	// Pos: Encuentra la mayor clave y la devuelve por referencia.
	void min(NodoDiccionario<T, U>* nodo, T& clave) const {
		if (nodo == nullptr) {
			return;
		} else if (nodo->izquierda() == nullptr) {
			clave = nodo->clave();
		} else {
			min(nodo->derecha(), clave);
		}
	};
	// Pre: -
	// Pos: Devuelve la clave y el dato del sucesor por referencia.
	T sucesor(NodoDiccionario<T, U>* nodo) {
		T tmp;
		if (nodo->derecha() != nullptr) {
			min(nodo->derecha(), tmp);
			return tmp;
		}
		NodoDiccionario<T, U>* sucesor = nullptr;
		NodoDiccionario<T, U>* ancestro = raiz_;
		while (ancestro != nodo) {
			if (nodo->clave() < ancestro->clave()) {
				sucesor = ancestro;
				ancestro = ancestro->izquierda();
			} else {
				ancestro = ancestro->derecha();
			}
		}
		return sucesor->clave();
	};
	// Pre: -
	// Pos: Remueve el elemento con clave "clave" del diccionario.
	NodoDiccionario<T, U>* remover(NodoDiccionario<T, U>* nodo,
				       const T& clave) {
		if (nodo == nullptr) return nullptr;

		if (nodo->clave() == clave) {
			if (nodo->hoja()) {
				delete nodo;
				nodo = nullptr;
			} else if (nodo->solo_hijo_derecha()) {
				nodo->derecha()->cambiar_padre(nodo->padre());
				NodoDiccionario<T, U>* aux = nodo;
				nodo = nodo->derecha();
				delete aux;
			} else if (nodo->solo_hijo_izquierda()) {
				nodo->izquierda()->cambiar_padre(nodo->padre());
				NodoDiccionario<T, U>* aux = nodo;
				nodo = nodo->izquierda();
				delete aux;
			} else {
				T clave_sucesor;
				sucesor(clave, clave_sucesor);
				nodo->cambiar_clave(clave_sucesor);
				nodo->cambiar_derecha(
				    remover(nodo->derecha(), clave_sucesor));
			}
		} else if (nodo->clave() < clave) {
			nodo->cambiar_derecha(remover(nodo->derecha(), clave));
		} else {
			nodo->cambiar_izquierda(
			    remover(nodo->izquierda(), clave));
		}
		return nodo;
	};
	// Pre: -
	// Pos: Devuelve el nodo donde asociado a la clave "clave".
	NodoDiccionario<T, U>* buscar(NodoDiccionario<T, U>* nodo,
				      const T& clave) const {
		if (nodo == nullptr || nodo->clave() == clave) return nodo;
		if (clave > nodo->clave())
			return buscar(nodo->derecha(), clave);
		return buscar(nodo->izquierda(), clave);
	};
	// Pre: -
	// Pos: Libera la memoria pedida para los nodos.
	void borrar_nodos(NodoDiccionario<T, U>* nodo) {
		if (nodo == nullptr) return;
		borrar_nodos(nodo->izquierda());
		borrar_nodos(nodo->derecha());
		delete nodo;
	};
	// Pre: -
	// Pos: True si encuentra el sucesor, False en otro caso. Devuelve
	// la clave del sucesor por referencia.
	bool sucesor(T clave, T& clave_resultado) {
		NodoDiccionario<T, U>* nodo_clave = buscar(raiz_, clave);
		if (nodo_clave == nullptr) return false;
		clave_resultado = sucesor(nodo_clave);
		return true;
	};

	// Pre: -
	// Pos: Copia recursivamente los pares clave-dato del nodo "nodo"
	// en el objeto sobre el cual se llama.
	void copiar(NodoDiccionario<T, U>* nodo) {
		if (nodo == nullptr) {
			return;
		}
		insertar(nodo->clave(), nodo->dato());
		copiar(nodo->izquierda());
		copiar(nodo->derecha());
	};
	// Pre: -
	// Pos: Intercambia los contenidos del diccionario pasado por 
	// referencia, con los del diccionario sobre el que se llama
	void swap(Diccionario<T, U>& diccionario) {
		using std::swap;
		swap(raiz_, diccionario.raiz_);
	};

	// Pre:
	// Pos:
	void claves(NodoDiccionario<T, U>* nodo, Lista<T>& lista) { 
		if (nodo != nullptr) {			
			claves(nodo->izquierda(), lista);
			lista.alta_al_final(nodo->clave());
			claves(nodo->derecha(), lista);
		}
	};
       public:
	// Pre: -
	// Pos: Constructor del diccionario;
	Diccionario() : raiz_(nullptr){};
	// Pre: -
	// Pos: Construye el nuevo diccionario a partir de una copia del
	// del lado derecho de la igualdad.
	Diccionario(const Diccionario& rhs) : raiz_(nullptr) {
		NodoDiccionario<T, U>* tmp = rhs.raiz_;
		copiar(tmp);
	};
	// Pre: -
	// Pos: Operador de asignacion del diccionario. Asigna los
	// contenidos del diccionario a la derecha del igual, al de
	// la izquierda.
	Diccionario<T, U>& operator=(const Diccionario<T, U>& rhs) {
		Diccionario<T, U> copia = rhs;
		copia.swap(*this);
		return *this;
	};
	// Pre: -
	// Pos: Destruye el diccionario.
	~Diccionario() { borrar_nodos(raiz_); };
	// Pre: -
	// Pos: Inserta en el diccionario el dato con la clave "clave".
	void insertar(const T& clave, const U& dato) {
		raiz_ = insertar(raiz_, clave, dato);
	};
	// Pre: -
	// Pos: Remueve el elemento con la clave "clave".
	void remover(const T& clave) { raiz_ = remover(raiz_, clave); };
	// Pre: -
	// Pos: True si encuentra la clave, False en otro caso. Devuelve
	// por referencia el resultado.
	bool buscar(const T& clave) const {
		NodoDiccionario<T, U>* nodo = buscar(raiz_, clave);
		if (nodo != nullptr) {
			return true;
		}
		return false;
	};
	// Pre: -
	// Pos: Accede al elemento con clave "clave". Si la clave existe
	// devuelve una referencia al dato asociado; si no existe crea la
	// clave y devuelve la referencia al dato (Creado usando Constructor
	// por defecto)
	U& operator[](const T& clave) {
		NodoDiccionario<T, U>* nodo = buscar(raiz_, clave);
		if (nodo == nullptr) {
			insertar(clave, U());
			nodo = buscar(raiz_, clave);
		}
		return nodo->dato();
	};
	const U& operator[](const T& clave) const {
		NodoDiccionario<T, U>* nodo = buscar(raiz_, clave);
		if (nodo == nullptr) {
			insertar(clave, U());
			nodo = buscar(raiz_, clave);
		}
		return nodo->dato();
	};
	// Pre: -
	// Pos: True si esta vacio, False en otro caso.
	bool vacio() const { return (raiz_ == nullptr); };

	// Pre: -
	// Pos: True si existe la clave, False en otro caso.
	bool existe(const T& clave) {
		return (buscar(raiz_, clave) != nullptr);
	};
	// Pre: -
	// Pos: Devuelve una lista con las claves del diccionario.
	Lista<T> claves() {
		Lista<T> lista;
		claves(raiz_, lista);
		return lista;
	};
};

#endif
