#ifndef OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_
#define OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_

#include "../Objetivo.h"

class Bombardero : public Objetivo{
private:
	std::size_t bombas_actuales;
	std::size_t bombas_usadas;
public:
	Bombardero(Jugador* jugador);
	~Bombardero();
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_ */
