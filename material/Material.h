#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

using namespace std;

const string MATERIAL_VACIO = "";

class Material{
private:
	string nombre;
	int cantidad;

public:
	//PRE: -
	//POST: se crea un material vacio
	Material();

	//PRE: -
	//POST: se crea un material con los datos ingresados
	Material(string nombre, int cantidad);

	//PRE: -
	//POST: devuelve el nombre del material
	string obtener_nombre();

	//PRE: -
	//POST: devuelve la cantidad del material
	int obtener_cantidad();

	//PRE: -
	//POST: se cambia el nombre del material
	void cambiar_nombre(string nombre);

	//PRE: -
	//POST: se cmbia la cantidad del material
	void cambiar_cantidad(int cantidad);

	//PRE: -
	//POST: imprime un saludo
	void saludar();
};

#endif /* MATERIAL_H_ */
