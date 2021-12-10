#include "../material/Material.h"
#include "../utils/Lista.h"
#include <iostream>
using namespace std;

const string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";


Lista<Material> devolver_lista(Material material){
    Lista<Material> lista = Lista<Material>();
    lista.alta_al_final(material);
    return lista;
}

int main(){
    Material material1("madera",1);
    Material material2("madera",2);
    Material material3("madera",3);
    Material material4("madera",4);

    Lista<Material> lista1 = devolver_lista(material1);
    Lista<Material> lista2 = devolver_lista(material2);
    Lista<Material> lista3 = devolver_lista(material3);
    Lista<Material> lista4 = devolver_lista(material4);

    std::cout << lista1.consulta(1).obtener_nombre() << lista1.consulta(1).obtener_cantidad() << std::endl;
    std::cout << lista2.consulta(1).obtener_nombre() << lista2.consulta(1).obtener_cantidad() << std::endl;
    std::cout << lista3.consulta(1).obtener_nombre() << lista3.consulta(1).obtener_cantidad() << std::endl;
    std::cout << lista4.consulta(1).obtener_nombre() << lista4.consulta(1).obtener_cantidad() << std::endl;

    return 0;
}