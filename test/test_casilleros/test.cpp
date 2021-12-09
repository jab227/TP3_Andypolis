#include "../../Casillero/Casillero.h"
#include "../../Casillero/CasilleroInaccesible.h"
#include "../../Casillero/casilleros/Muelle.h"
#include "../../Casillero/casilleros/Camino.h"
#include "../../Casillero/casilleros/Betun.h"
#include "../../Casillero/CasilleroConstruible.h"
#include "../../edificio/edificios/Mina.h"
#include "../../edificio/edificios/Fabrica.h"

using namespace std;

const std::string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const std::string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

int main()
{
    Casillero *casillero1 = new Casillero_Construible();
    Casillero *casillero2 = new Muelle();
    Casillero *casillero3 = new Camino();
    Casillero *casillero4 = new Betun();
    Casillero *casillero5 = new Casillero_Inaccesible();
    /*
        casillero1->saludar();
        casillero2->saludar();
        casillero3->saludar();
        casillero4->saludar();
        casillero5->saludar();
    */
    /*
        cout << casillero1->esta_ocupado() << endl;
        cout << casillero2->esta_ocupado() << endl;
        cout << casillero3->esta_ocupado() << endl;
        cout << casillero4->esta_ocupado() << endl;
        cout << casillero5->esta_ocupado() << endl;
    */
    Edificio *edificio = new Fabrica(1, 1, 1, 1);
    cout << casillero1->construir_edificio(edificio)<< endl;
    /*
    cout << casillero2->construir_edificio(edificio)<< endl;
    cout << casillero3->construir_edificio(edificio)<< endl;
    cout << casillero4->construir_edificio(edificio)<< endl;
    cout << casillero5->construir_edificio(edificio)<< endl;
    */
    Material material01 = Material("andycoins", 200);
    Material material02 = Material("andycoins", 300);
    Material material03 = Material("andycoins", 400);
    // CAMBIAR DOWNCAST.
    ((Casillero_Transitable *)casillero2)->agregar_material(material01);
    ((Casillero_Transitable *)casillero3)->agregar_material(material02);
    ((Casillero_Transitable *)casillero4)->agregar_material(material03);
    /*
        casillero1->saludar();
        casillero2->saludar();
        casillero3->saludar();
        casillero4->saludar();
        casillero5->saludar();
   */
    /*
        cout << casillero1->esta_ocupado() << endl;
        cout << casillero2->esta_ocupado() << endl;
        cout << casillero3->esta_ocupado() << endl;
        cout << casillero4->esta_ocupado() << endl;
        cout << casillero5->esta_ocupado() << endl;
    */


    /*
        cout << casillero1->es_casillero_transitable() << endl;
        cout << casillero2->es_casillero_transitable() << endl;
        cout << casillero3->es_casillero_transitable() << endl;
        cout << casillero4->es_casillero_transitable() << endl;
        cout << casillero5->es_casillero_transitable() << endl;
    */
   /*
    cout << casillero1->obtener_contenido() << endl;
    cout << casillero2->obtener_contenido() << endl;
    cout << casillero3->obtener_contenido() << endl;
    cout << casillero4->obtener_contenido() << endl;
    cout << casillero5->obtener_contenido() << endl;
   */
   /*
    cout << casillero1 -> obtener_color() << endl;
    cout << casillero2 -> obtener_color() << endl;
    cout << casillero3 -> obtener_color() << endl;
    cout << casillero4 -> obtener_color() << endl;
    cout << casillero5 -> obtener_color() << endl;
   */
/*
    cout << casillero1->demoler_edificio() << std::endl;
    cout << casillero2->demoler_edificio() << std::endl;
    cout << casillero3->demoler_edificio() << std::endl;
    cout << casillero4->demoler_edificio() << std::endl;
    cout << casillero5->demoler_edificio() << std::endl;
*/
/*
        casillero1->saludar();
        casillero2->saludar();
        casillero3->saludar();
        casillero4->saludar();
        casillero5->saludar();
*/
/* RECOGER MATERIALES
    Lista<Material> lista_materiales;
    Material material1 = Material("piedra",10);
    lista_materiales.alta_al_final(material1);
    Material material2 = Material("madera",10);
    lista_materiales.alta_al_final(material2);
    Material material3 = Material("metal",10);
    lista_materiales.alta_al_final(material3);
    Material material4 = Material("andycoins",10);
    lista_materiales.alta_al_final(material4);
    Material material5 = Material("bombas",10);
    lista_materiales.alta_al_final(material5);

    Almacen* inventario = new Almacen(lista_materiales);
    inventario->mostrar_materiales();

    casillero1->recoger_material(inventario);
    casillero2->recoger_material(inventario);
    casillero3->recoger_material(inventario);
    casillero4->recoger_material(inventario);
    casillero5->recoger_material(inventario);
    
    casillero1->recoger_material(inventario);
    casillero1->demoler_edificio();

    casillero1->recoger_material(inventario);
    casillero2->recoger_material(inventario);
    casillero3->recoger_material(inventario);
    casillero4->recoger_material(inventario);
    casillero5->recoger_material(inventario);

    inventario->mostrar_materiales();
    
    delete inventario;
*/
/*
    cout << casillero1->atacar_edificio();
    cout << casillero2->atacar_edificio();
    cout << casillero3->atacar_edificio();
    cout << casillero4->atacar_edificio();
    cout << casillero5->atacar_edificio();

    cout << casillero1->reparar_edificio() << endl;
    cout << casillero1->atacar_edificio() << endl;
    
    cout << casillero1->reparar_edificio();
    cout << casillero2->reparar_edificio();
    cout << casillero3->reparar_edificio();
    cout << casillero4->reparar_edificio();
    cout << casillero5->reparar_edificio();
    cout << casillero1->reparar_edificio();

*/    
  
    delete casillero1;
    delete casillero2;
    delete casillero3;
    delete casillero4;
    delete casillero5;
    return 0;
}