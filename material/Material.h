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
	//POS: se crea un material vacio
	Material();

	//PRE: -
	//POS: se crea un material con los datos ingresados
	Material(std::string nombre, std::size_t cantidad);

	Material(const Material& rhs) = default;

	//PRE: -
	//POS: devuelve el nombre del material
	std::string obtener_nombre() const;

	//PRE: -
	//POS: devuelve la cantidad del material
	std::size_t obtener_cantidad() const;

	//PRE: -
	//POS: se cambia el nombre del material
	void cambiar_nombre(std::string nombre);

	//PRE: -
	//POS: se cmbia la cantidad del material
	void cambiar_cantidad(std::size_t cantidad);

	//PRE: -
	//POS: se suma cantidad a la cantidad del material
	void sumar_cantidad(std::size_t cantidad);

	//PRE: -
	//POS: se resta cantidad a la cantidad del material
	void restar_cantidad(std::size_t cantidad);
	
	//PRE: -
	//POS: imprime un saludo
	void saludar() const;

	// PRE: -
	// POS: True si los materiales son iguales, False
	// en otro caso.
	bool operator==(const Material& rhs) const;

	// Operador de asignacion del material
	void operator=(const Material& rhs);
};

#endif /* MATERIAL_H_ */
