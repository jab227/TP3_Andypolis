#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <string>

class Coordenada {
       private:
	std::size_t x_;
	std::size_t y_;

       public:
	//Constructor por default
	Coordenada() = default;

	//Constructor de copia por default
	Coordenada(const Coordenada& rhs) = default;

	//Operador = por default
	Coordenada& operator=(const Coordenada& rhs) = default;

	//Destructor por default
	~Coordenada() = default;

	//PRE: -
	//POS: Construye una Coordenada con x_ = x e y_ = y
	Coordenada(const std::size_t& x, const std::size_t& y);

	//PRE: rhs debe ser una instancia de Coordenada existente.
	//POS: Sobrecarga del operador ==. True si x_ e y_ son iguales a las de rhs.
	bool operator==(const Coordenada& rhs) const;

	//PRE: rhs debe ser una instancia de Coordenada existente.
	//POS: Sobrecarga del operador !=. True si x_ e y_ son distintas a las de rhs.
	bool operator!=(const Coordenada& rhs) const;

	//PRE: -
	//POS: Devuelve x_
	std::size_t x() const;

	//PRE: -
	//POS: Devuelve y_
	std::size_t y() const;

	//PRE: -
	//POS: Retorna el string (x_, y_). (Como en el formato ubicaciones.txt)
	std::string a_string() const;

};
#endif
