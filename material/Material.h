#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

using namespace std;

const string MATERIAL_VACIO = "";

class Material{
private:
	string nombre;
	std::size_t cantidad;

public:
	//PRE: -
	//POST: se crea un material vacio
	Material();

	//PRE: -
	//POST: se crea un material con los datos ingresados
	Material(string nombre, std::size_t cantidad);

	//PRE: -
	//POST: devuelve el nombre del material
	string obtener_nombre();

	//PRE: -
	//POST: devuelve la cantidad del material
	std::size_t obtener_cantidad();

	//PRE: -
	//POST: se cambia el nombre del material
	void cambiar_nombre(string nombre);

	//PRE: -
	//POST: se cmbia la cantidad del material
	void cambiar_cantidad(std::size_t cantidad);

	//PRE: -
	//POST: se suma cantidad a la cantidad del material
	void sumar_cantidad(std::size_t cantidad);

	//PRE: -
	//POST: imprime un saludo
	void saludar();

	bool operator==(Material rhs);

	bool operator=(Material rhs);
};

#endif /* MATERIAL_H_ */
