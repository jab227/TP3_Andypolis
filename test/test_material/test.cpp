#include "../../material/Material.h"
#include <iostream>
using namespace std;

const std::string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const std::string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

Material crear_material3(std::string nombre, std::size_t cantidad){
    return Material(nombre, cantidad);
}

int main(){
    Material material1 = Material();
    Material material2 = Material("Ferr",10);

    cout << (material1 == material2) << endl;

    cout << material1.obtener_nombre() << endl;
    cout << material1.obtener_cantidad() << endl;

    material1.cambiar_nombre("Fer"); 
    material1.cambiar_cantidad(1); 

    cout << material1.obtener_nombre() << endl;
    cout << material1.obtener_cantidad() << endl;

    material1.sumar_cantidad(10); 
    cout << material1.obtener_cantidad() << endl;

    material1.saludar(); 

    cout << (material1 == material2) << endl;

    material2 = material1;
    cout << material2.obtener_cantidad() << endl;

    Material material3 = crear_material3("3",3);
    cout << material3.obtener_nombre() << endl;
    cout << material3.obtener_cantidad() << endl;

    return 0;
}