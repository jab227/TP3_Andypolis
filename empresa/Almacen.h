#ifndef ALMACEN_H_
#define ALMACEN_H_

#include "../material/Material.h"
#include "../utils/Lista.h"
#include "../edificio/Edificio.h"

const int NO_ENCONTRADO = 0;
std::string const SALIR_STR = "salir";
const std::string NOMBRES_MATERIALES[] = {"piedra", "madera", "metal", "andycoins", "bombas"};

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

	//Constructor de copia
	Almacen(const Almacen& rhs) = default;
	
	//Destructor por default
	~Almacen() = default;
	
	//PRE: -
	//POS: Devuelve lista_materiales_
	Lista<Material>& obtener_materiales(); 
	
	//PRE: -
	//POS: Retorna el material de la lista_materiales_.
	//En caso de no encontrarse, devuelve el Material con el material
	//de nombre y la cantidad vacia.
	Material obtener_material(std::string material) const;

	//PRE: -
	//POS: se resta cantidad del material de nombre a_cambiar. Si no existe el material
	//con ese nombre, no se realiza ningun cambio.
	void restar_cantidad_material(const std::string& nombre, std::size_t cantidad);	
	
	//PRE: -
	//POS: se suma cantidad del material de nombre a_cambiar. Si no existe el material
	//con ese nombre, no se realiza ningun cambio.
	void sumar_cantidad_material(const std::string& a_cambiar, std::size_t cantidad);

	//PRE: -
	//POS: muestra todos los materiales en lista_materiales_ por terminal
	void mostrar_materiales() const;

	//PRE:  -
	//POS: devuelve true si se cuentan con toda la lista de los materiales
	//en stock
	Resultado_Chequeos hay_lista_materiales(const Lista<Material>& materiales_consultados, std::size_t porcentaje = 100) const;

	//PRE:  -
	//POS: Descuenta de lista_materiales_ los materiales que esten en materiales_usados. Porcentaje para definir si queres descontar menos.	
	void descontar_lista_materiales(const Lista<Material>& materiales_usados, std::size_t porcentaje = 100);

	//PRE:  -
	//POS: Incrementa de lista_materiales_ los materiales que esten en materiales_usados. Porcentaje para definir si queres descontar menos.
	void sumar_lista_materiales(const Lista<Material>& materiales_usados, std::size_t porcentaje = 100);

	//PRE: -
	//POS: se compran las bombas pidiendo al usuario la cantidad
	Resultado_Chequeos comprar_bombas(std::size_t cantidad_bombas);

private:
	//PRE: -
	//POS: se agrega el material al final de la lista_materiales_.
	void agregar_material(const Material& material);

	//PRE: -
	//POS: devuelve el indice del material en caso de encontrarse o en caso de
	//no estar en el arreglo, devuelve NO_ENCONTRADO.
	std::size_t buscar_material(const Material& a_buscar) const;
	
	//PRE: -
	//POS: devuelve true si hay la cantidad del material ingresado en stock y false si
	//no la hay o si no se encuentra ese material.
	bool hay_material_suficiente(const Material& material, std::size_t porcentaje = 100) const;
	

};

#endif /* ALMACEN_H_ */
