#ifndef OBJETIVOS_TIPOS_EXTREMISTA_H_
#define OBJETIVOS_TIPOS_EXTREMISTA_H_

#include "../Objetivo.h"

class Extremista : public Objetivo{
private:
	std::size_t bombas_actuales;
	std::size_t bombas_compradas;
public:
	Extremista(Jugador* jugador);
	~Extremista();
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_EXTREMISTA_H_ */
