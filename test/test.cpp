#include <iostream>

#include "../edificio/Edificio.h"
#include "../edificio/edificios/Aserradero.h"
#include "../edificio/edificios/Escuela.h"
#include "../edificio/edificios/Fabrica.h"
#include "../empresa/Planos.h"
#include "../utils/Lista.h"
#include "../utils/Nodo.h"
#include "../utils/LecturaArchivos.h"

using namespace std;

int main(){
    Planos plano = Planos("./saves/edificios.txt");
    Lista<Edificio*> lista = Lista<Edificio*>();
    Resultado_Chequeos hola = EXITO;
    cout << hola << endl;
    hola = plano.check_construir_edificio("escuela");
    cout << hola << endl;

}