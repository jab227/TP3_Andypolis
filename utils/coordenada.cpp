#include "coordenada.h"


Coordenada::Coordenada(const std::size_t& x, const std::size_t& y) : x_(x), y_(y) {}

std::size_t Coordenada::x() const {
	return x_;
}

std::size_t Coordenada::y() const {
	return y_;
}

std::string Coordenada::a_string() const {
	return "(" + std::to_string(x()) + ", " + std::to_string(y()) + ")";
}

bool Coordenada::operator==(const Coordenada& rhs) const {
	return (x() == rhs.x() && y() == rhs.y());
}

bool Coordenada::operator!=(const Coordenada& rhs) const {
	return !(*this == rhs);
}

