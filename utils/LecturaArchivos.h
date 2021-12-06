#ifndef LECTURAARCHIVOS_H_
#define LECTURAARCHIVOS_H_

#include <string>

#include "../Casillero/Casillero.h"
#include "../edificio/Edificio.h"

// PRE: linea debe tener el formato valido para el rango del mapa
// POST: se carga la linea y la fila con los valores correspondientes a la linea
// ingresada
void cargar_fila_columna(std::string linea, std::size_t& filas,
			 std::size_t& columnas);

// PRE: nombre debe ser un edificio valido
// POST: devuelve el edificio cargado con los datos
Edificio* traductor_edificios(std::string nombre, std::size_t piedra,
			      std::size_t madera, std::size_t metal,
			      std::size_t max_permitidos);

// PRE: nombre debe ser un edificio valido
// POST: devuelve el edificio cargado con los datos
Edificio* traductor_edificios(std::string nombre, std::size_t piedra,
			      std::size_t madera, std::size_t metal,
			      std::size_t max_permitidos, size_t propietario);

// PRE: nombre debe corresponder a un casillero
// POST: se devuelve el casillero vacio correspondiente a nombre creado en
// memoria dinamica
Casillero* traductor_casillero(char nombre);

// PRE: nombre debe ser un material valido
// POST: devuelve el material cargado con los datos
Material* traductor_materiales(std::string nombre, std::size_t cantidad);

#endif /* LECTURAARCHIVOS_H_ */
