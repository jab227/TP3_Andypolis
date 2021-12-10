#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>

const std::string MATERIAL_VACIO = "";

class Material{
private:
	std::string nombre;
	std::size_t cantidad;

public:
	//PRE: -
	//POST: se crea un material vacio
	Material();

	//PRE: -
	//POST: se crea un material con los datos ingresados
	Material(std::string nombre, std::size_t cantidad);

	Material(const Material& rhs) = default;

	//PRE: -
	//POST: devuelve el nombre del material
	std::string obtener_nombre() const;

	//PRE: -
	//POST: devuelve la cantidad del material
	std::size_t obtener_cantidad() const;

	//PRE: -
	//POST: se cambia el nombre del material
	void cambiar_nombre(std::string nombre);

	//PRE: -
	//POST: se cmbia la cantidad del material
	void cambiar_cantidad(std::size_t cantidad);

	//PRE: -
	//POST: se suma cantidad a la cantidad del material
	void sumar_cantidad(std::size_t cantidad);

	//PRE: -
	//POST: se resta cantidad a la cantidad del material
	void restar_cantidad(std::size_t cantidad);
	
	//PRE: -
	//POST: imprime un saludo
	void saludar() const;

	bool operator==(Material rhs) const;

	void operator=(Material rhs);
};

#endif /* MATERIAL_H_ */
