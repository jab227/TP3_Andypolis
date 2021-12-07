#ifndef LECTURAARCHIVOS_H_
#define LECTURAARCHIVOS_H_

#include "../edificio/Edificio.h"
#include "../Casillero/Casillero.h"
#include "../utils/coordenada.h"
#include <string>

using namespace std;

const char ESPACIO = ' ', ENTER = 10, DELIMITADOR_UBICACION = '(';

//PRE: -
//POST: devuelve si la palabra esta compuesta por todos numeros o no.
bool es_numero(std::string palabra);

//PRE: linea debe tener el formato valido para los edificios
//POST: se procesa la linea y se devuelve el edificio referencido en la linea.
//Edificio* procesar_edificio(std::string linea);

//PRE: linea debe tener el formato valido para los materiales
//POST: se procesa la linea y se devuelve el material referencido en la linea.
//Material procesar_material(std::string linea);

//PRE: linea debe tener el formato valido para el rango del mapa
//POST: se carga la linea y la fila con los valores correspondientes a la linea ingresada
void cargar_fila_columna(std::string linea, std::size_t &filas, std::size_t &columnas);

//PRE: nombre debe ser un edificio valido
//POST: devuelve el edificio cargado con los datos
Edificio* traductor_edificios(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t max_permitidos);

//std::string procesar_ubicacion(std::string linea, Coordenada& coordenada);

//PRE: nombre debe corresponder a un casillero
//POST: se devuelve el casillero vacio correspondiente a nombre creado en memoria dinamica
Casillero* traductor_casillero(char nombre);

// PRE: nombre debe ser un material valido
// POST: devuelve el material cargado con los datos
Material* traductor_materiales(std::string nombre, std::size_t cantidad);

#endif /* LECTURAARCHIVOS_H_ */
