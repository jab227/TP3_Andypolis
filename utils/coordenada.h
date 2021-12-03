#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <string>

class Coordenada {
       private:
	std::size_t x_;
	std::size_t y_;

       public:
	Coordenada(const std::size_t& x, const std::size_t& y);
	bool operator==(const Coordenada& rhs) const;
	bool operator!=(const Coordenada& rhs) const;
	std::size_t x() const;
	std::size_t y() const;
	std::string mostrar() const;
};
#endif
