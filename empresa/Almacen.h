#ifndef ALMACEN_H_
#define ALMACEN_H_

#include "../material/Material.h"
#include "../utils/Lista.h"
#include "../edificio/Edificio.h"

const int NO_ENCONTRADO = 0;
std::string const SALIR_STR = "salir";
const std::string NOMBRES_MATERIALES[] = {"madera", "piedra", "metal", "andycoins", "bombas"};

class Almacen {
private:
	Lista<Material> lista_materiales_;

public:
	//PRE: -
	//POS: creo un almacen inicializado en 0;
	Almacen();

	//PRE: ruta debe ser una ruta a un archivo bien estructurado.
	//POS: creo un almacen inicializado con el archivo en la ruta espesificada.
	Almacen(const Lista<Material>& lista);

	//PRE: -
	//POS: se libera la memoria utilizada
	~Almacen();

	//PRE: -
	//POS: se modifica la cantidad del material de nombre a_cambiar. Si no existe, no
	//se realiza ningun cambio. La cantidad puede ser negativa, en tal caso se restara.
	void sumar_cantidad_material(const std::string& a_cambiar, std::size_t cantidad);
	//Le puse sumar, porque modificar pareciera no suma, sino que reemplaza el valor.

	//PRE: almacen debe ser un puntero a estructura existente, es decir, != nullptr.
	//post: muestra todos los materiales por terminal
	void mostrar_materiales() const;

	//PRE: almacen debe ser puntero a estructura existente, es decir, != nullptr.
	//POS: se guardan los datos de los edificios en el archivo de salida en caso
	//de que exista y devuelve true. De lo contrario devuelve false.
	bool guardar_materiales(const std::string& ruta);


	//TODO: Sobrecarga de hay_material_suficiente y hay_lista_materiales.

	//PRE: -
	//POS: devuelve true si hay la cantidad del material ingresado en stock y false si
	//no la hay o si no se encuentra ese material.
	bool hay_material_suficiente(const Material& material, std::size_t porcentaje = 100) const;


	//PRE:  -
	//POS: devuelve true si se cuentan con toda la lista de los materiales
	//en stock
	Resultado_Chequeos hay_lista_materiales(const Lista<Material>& materiales_consultados, std::size_t porcentaje = 100) const;

	//TODO: Agregue porcentaje para que sea multiuso. Puede agregarse un valor default al porcentaje?
	void descontar_lista_materiales(const Lista<Material>& materiales_usados, std::size_t porcentaje);
	
	void sumar_lista_materiales(const Lista<Material>& materiales_usados, std::size_t porcentaje);

	//PRE:
	//POS: se compran las bombas pidiendo al usuario la cantidad
	Resultado_Chequeos comprar_bombas(std::size_t cantidad_bombas);

	//PRE: -
	//POS: devuelve el indice del material en caso de encontrarse o en caso de
	//no estar en el arreglo, devuelve NO_ENCONTRADO.
	std::size_t buscar_material(const Material& a_buscar) const;

private:
	//PRE: 1 <= posicion <= el largo de la lista.
	//POS: se agrega el material al final del vector.
	void agregar_material(const Material& material);
	

};

#endif /* ALMACEN_H_ */
