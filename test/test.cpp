#include "../empresa/EmpresaConstructora.h"

using namespace std;

const string RUTA_MATERIALES = "./saves/materiales.txt", RUTA_EDIFICIOS = "./saves/edificios.txt";
const string RUTA_MAPA = "./saves/mapa.txt", RUTA_UBICACIONES = "./saves/ubicaciones.txt";

int main(){
    Empresa_Constructora coca = Empresa_Constructora(RUTA_MATERIALES,RUTA_EDIFICIOS,RUTA_MAPA,RUTA_UBICACIONES);
    coca.mostrar_construidos();
    
    return 0;
}