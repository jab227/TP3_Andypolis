#ifndef ALMACEN_H_
#define ALMACEN_H_

#include "../material/Material.h"
#include "../utils/Lista.h"
#include "../edificio/Edificio.h"

const int NO_ENCONTRADO = 0;

class Almacen {
private:
	Lista<Material> lista_materiales;

public:
	//PRE: -
	//POST: creo un almacen inicializado en 0;
	Almacen();

	//PRE: ruta debe ser una ruta a un archivo bien estructurado.
	//POST: creo un almacen inicializado con el archivo en la ruta espesificada.
	Almacen(string ruta);

	//PRE: -
	//POST: se libera la memoria utilizada
	~Almacen();

	//PRE: se le debe pasar la ruta del archivo a abrir el cual debe estar bien estructurado
	//POST: en caso de poder abrir el archivo, se agregan los materiales del archivo a la
	//lista
	void cargar_materiales(string ruta);

	//PRE: almacen debe ser un puntero a estructura existente, es decir, != nullptr.
	//POST: se modifica la cantidad del material de nombre a_cambiar. Si no existe, no
	//se realiza ningun cambio. La cantidad puede ser negativa, en tal caso se restara.
	
	void sumar_cantidad_material(string a_cambiar, std::size_t cantidad);
	//Le puse sumar, porque modificar pareciera no suma, sino que reemplaza el valor.

	//PRE: almacen debe ser un puntero a estructura existente, es decir, != nullptr.
	//post: muestra todos los materiales por terminal
	void mostrar_materiales();

	//PRE: almacen debe ser puntero a estructura existente, es decir, != nullptr.
	//POST: se guardan los datos de los edificios en el archivo de salida en caso
	//de que exista y devuelve true. De lo contrario devuelve false.
	bool guardar_materiales(string ruta);

	//PRE: -
	//POST: devuelve true si hay la cantidad del material ingresado en stock y false si
	//no la hay o si no se encuentra ese material.
	bool hay_material_suficiente(Material material);

	//PRE: la lista no debe ser un puntero nulo
	//POST: devuelve true si se cuentan con toda la lista de los materiales
	//en stock
	Resultado_Chequeos hay_lista_materiales(Lista<Material>* materiales_consutlados);

	//TODO: Agregue porcentaje para que sea multiuso. Puede agregarse un valor default al porcentaje?
	void descontar_lista_materiales(Lista<Material>* materiales_usados, std::size_t porcentaje);
	void sumar_lista_materiales(Lista<Material>* materiales_usados, std::size_t porcentaje);

	//PRE:
	//POST: se compran las bombas pidiendo al usuario la cantidad
	Resultado_Chequeos comprar_bombas( std::size_t cantidad);


private:
	//PRE: 1 <= posicion <= el largo de la lista.
	//POST: se agrega el material al final del vector.
	void agregar_material(Material material, std::size_t posicion);
	
	Resultado_Chequeos chequeo_bombas(std::size_t cantidad);

	//PRE: -
	//POST: devuelve el indice del material en caso de encontrarse o en caso de
	//no estar en el arreglo, devuelve NO_ENCONTRADO.
	std::size_t buscar_material(Material& a_buscar);
};

#endif /* ALMACEN_H_ */
