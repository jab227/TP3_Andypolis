#include "../../edificio/Edificio.h"
#include "../../edificio/edificios/Aserradero.h"
#include "../../edificio/edificios/Escuela.h"
#include "../../edificio/edificios/Mina.h"
#include "../../edificio/edificios/MinaOro.h"
#include "../../edificio/edificios/Fabrica.h"
#include "../../edificio/edificios/PlantaElectrica.h"
#include "../../edificio/edificios/Obelisco.h"

using namespace std;

const string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

int main(){
    Edificio* edificio1 = new Aserradero(1,1,1,1);
    Edificio* edificio2 = new Escuela(1,1,1,1);
    Edificio* edificio3 = new Mina(1,1,1,1);
    Edificio* edificio4 = new Mina_Oro(1,1,1,1);
    Edificio* edificio5 = new Fabrica(1,1,1,1);
    Edificio* edificio6 = new Planta_Electrica(1,1,1,1);
    Edificio* edificio7 = new Obelisco(1,1,1,1);
/* // NOMBRES ok
    cout << edificio1 -> obtener_nombre() << endl;
    cout << edificio2 -> obtener_nombre() << endl;
    cout << edificio3 -> obtener_nombre() << endl;
    cout << edificio4 -> obtener_nombre() << endl;
    cout << edificio5 -> obtener_nombre() << endl;
    cout << edificio6 -> obtener_nombre() << endl;
    cout << edificio7 -> obtener_nombre() << endl;
*/
/* CANTIDAD_MATERIAL: OK
    cout << edificio1 -> obtener_cant_material("madera") << endl;
    cout << edificio2 -> obtener_cant_material("madera") << endl;
    cout << edificio3 -> obtener_cant_material("madera") << endl;
    cout << edificio4 -> obtener_cant_material("madera") << endl;
    cout << edificio5 -> obtener_cant_material("madera") << endl;
    cout << edificio6 -> obtener_cant_material("madera") << endl;
    cout << edificio7 -> obtener_cant_material("madera") << endl;
*/
/* VIDA: ok
    cout << edificio1 -> obtener_vida() << endl;
    cout << edificio2 -> obtener_vida() << endl;
    cout << edificio3 -> obtener_vida() << endl;
    cout << edificio4 -> obtener_vida() << endl;
    cout << edificio5 -> obtener_vida() << endl;
    cout << edificio6 -> obtener_vida() << endl;
    cout << edificio7 -> obtener_vida() << endl;
*/

/*SALUDAR: ok
    edificio1 -> saludar();
    edificio2 -> saludar();
    edificio3 -> saludar();
    edificio4 -> saludar();
    edificio5 -> saludar();
    edificio6 -> saludar();
    edificio7 -> saludar();
*/
    
/*EDIFICIOS VACIOS: ok
    cout << edificio1 -> vacio() << endl;
    cout << edificio2 -> vacio() << endl;
    cout << edificio3 -> vacio() << endl;
    cout << edificio4 -> vacio() << endl;
    cout << edificio5 -> vacio() << endl;
    cout << edificio6 -> vacio() << endl;
    cout << edificio7 -> vacio() << endl;
*/
/*MODIFICAR_CONSTRUIDOS: ok
    edificio1 -> aumentar_construidos();
    edificio2 -> aumentar_construidos();
    edificio3 -> aumentar_construidos();
    edificio4 -> aumentar_construidos();
    edificio5 -> aumentar_construidos();
    edificio6 -> aumentar_construidos();
    edificio7 -> aumentar_construidos();

    edificio1 -> modificar_construidos(2);
    edificio2 -> modificar_construidos(2);
    edificio3 -> modificar_construidos(2);
    edificio4 -> modificar_construidos(2);
    edificio5 -> modificar_construidos(2);
    edificio6 -> modificar_construidos(2);
    edificio7 -> modificar_construidos(2);

    edificio1 -> disminuir_construidos();
    edificio2 -> disminuir_construidos();
    edificio3 -> disminuir_construidos();
    edificio4 -> disminuir_construidos();
    edificio5 -> disminuir_construidos();
    edificio6 -> disminuir_construidos();
    edificio7 -> disminuir_construidos();

    cout << edificio1 -> obtener_construidos() << endl;
    cout << edificio2 -> obtener_construidos() << endl;
    cout << edificio3 -> obtener_construidos() << endl;
    cout << edificio4 -> obtener_construidos() << endl;
    cout << edificio5 -> obtener_construidos() << endl;
    cout << edificio6 -> obtener_construidos() << endl;
    cout << edificio7 -> obtener_construidos() << endl;

*/
/*MAX_PERMITIDOS: OK
    cout << edificio1 -> obtener_max_permitidos() << endl;
    cout << edificio2 -> obtener_max_permitidos() << endl;
    cout << edificio3 -> obtener_max_permitidos() << endl;
    cout << edificio4 -> obtener_max_permitidos() << endl;
    cout << edificio5 -> obtener_max_permitidos() << endl;
    cout << edificio6 -> obtener_max_permitidos() << endl;
    cout << edificio7 -> obtener_max_permitidos() << endl;

*/
/*MAXIMA_CAPACIDAD: ok
    cout << edificio1 -> esta_maxima_capacidad(1) << endl;
    cout << edificio2 -> esta_maxima_capacidad(1) << endl;
    cout << edificio3 -> esta_maxima_capacidad(1) << endl;
    cout << edificio4 -> esta_maxima_capacidad(1) << endl;
    cout << edificio5 -> esta_maxima_capacidad(1) << endl;
    cout << edificio6 -> esta_maxima_capacidad(1) << endl;
    cout << edificio7 -> esta_maxima_capacidad(1) << endl;

*/
/*PRODUCIR_MATERIAL: ok
    cout << edificio1 -> producir_material().obtener_nombre() << " "
    << (edificio1 -> producir_material()).obtener_cantidad() << endl;
    cout << edificio2 -> producir_material().obtener_nombre() << " "
    << edificio2 -> producir_material().obtener_cantidad() << endl;
    cout << edificio3 -> producir_material().obtener_nombre() << " "
    << edificio3 -> producir_material().obtener_cantidad() << endl;
    cout << edificio4 -> producir_material().obtener_nombre() << " "
    << edificio4 -> producir_material().obtener_cantidad() << endl;
    cout << edificio5 -> producir_material().obtener_nombre() << " "
    << edificio5 -> producir_material().obtener_cantidad() << endl;
    cout << edificio6 -> producir_material().obtener_nombre() << " "
    << edificio6 -> producir_material().obtener_cantidad() << endl;
    cout << edificio7 -> producir_material().obtener_nombre() << " "
    << edificio7 -> producir_material().obtener_cantidad() << endl;
*/
/*
INFO PRODUCTO: ok
    cout << edificio1 -> info_producto() << endl;
    cout << edificio2 -> info_producto() << endl;
    cout << edificio3 -> info_producto() << endl;
    cout << edificio4 -> info_producto() << endl;
    cout << edificio5 -> info_producto() << endl;
    cout << edificio6 -> info_producto() << endl;
    cout << edificio7 -> info_producto() << endl;

*/
/*REPARAR: ok
    cout << edificio1 -> reparar() << endl;
    cout << edificio2 -> reparar() << endl;
    cout << edificio3 -> reparar() << endl;
    cout << edificio4 -> reparar() << endl;
    cout << edificio5 -> reparar() << endl;
    cout << edificio6 -> reparar() << endl;
    cout << edificio7 -> reparar() << endl;

    cout << edificio1 -> disminuir_vida() << endl;
    cout << edificio2 -> disminuir_vida() << endl;
    cout << edificio3 -> disminuir_vida() << endl;
    cout << edificio4 -> disminuir_vida() << endl;
    cout << edificio5 -> disminuir_vida() << endl;
    cout << edificio6 -> disminuir_vida() << endl;
    cout << edificio7 -> disminuir_vida() << endl;

    cout << edificio1 -> reparar() << endl;
    cout << edificio2 -> reparar() << endl;
    cout << edificio3 -> reparar() << endl;
    cout << edificio4 -> reparar() << endl;
    cout << edificio5 -> reparar() << endl;
    cout << edificio6 -> reparar() << endl;
    cout << edificio7 -> reparar() << endl;
 */  

    delete edificio1;
    delete edificio2;
    delete edificio3;
    delete edificio4;
    delete edificio5;
    delete edificio6;
    delete edificio7;
    return 0;
}