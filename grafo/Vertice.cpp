#include "Vertice.h"

Vertice::Vertice(Coordenada nombre) {
    this -> nombre = nombre;
}

Coordenada Vertice::obtenerNombre() {
    return nombre;
}

Vertice::~Vertice() {

}
