#ifndef LECTURAARCHIVOS_H_
#define LECTURAARCHIVOS_H_

#include <string>
#include "../edificio/Edificio.h"
#include "../casillero/Casillero.h"

using namespace std;

const char ESPACIO = ' ', ENTER = 10, DELIMITADOR_UBICACION = '(';

//PRE: -
//POST: devuelve si la palabra esta compuesta por todos numeros o no.
bool es_numero(string palabra);

//PRE: linea debe tener el formato valido para los edificios
//POST: se procesa la linea y se devuelve el edificio referencido en la linea.
Edificio* procesar_edificio(string linea);

//PRE: linea debe tener el formato valido para los materiales
//POST: se procesa la linea y se devuelve el material referencido en la linea.
Material procesar_material(string linea);

//PRE: linea debe tener el formato valido para el rango del mapa
//POST: se carga la linea y la fila con los valores correspondientes a la linea ingresada
void cargar_fila_columna(string linea, int &filas, int &columnas);

//PRE: linea debe tener el formato valido para las ubicaciones
//POST: devuelve el edificio referido en la linea y fila y columna se igualan a la posicion del edificio
string procesar_ubicacion(string linea, int &fila, int &columna);

//PRE: nombre debe ser un edificio valido
//POST: devuelve el edificio cargado con los datos
Edificio* traductor_edificios(string nombre, int piedra, int madera, int metal, int max_permitidos);

//PRE: nombre debe corresponder a un casillero
//POST: se devuelve el casillero vacio correspondiente a nombre creado en memoria dinamica
Casillero* traductor_casillero(char nombre);

//PRE: nombre debe ser un material valido
//POST: devuelve el material cargado con los datos
Material* traductor_materiales(string nombre, int cantidad);

//PRE: -
//POST: devuelve un espaciado correspondiente al laro deseado y al largo de la palabra
string espaciado(string palabra, unsigned long int largo);

#endif /* LECTURAARCHIVOS_H_ */
