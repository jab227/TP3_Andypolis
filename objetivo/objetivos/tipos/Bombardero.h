#ifndef OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_
#define OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_

#include "../Objetivo.h"

class Bombardero : public Objetivo{
private:
	int bombas_actuales;
	int bombas_usadas;
public:
	Bombardero();
	bool actualizar();
};

#endif /* OBJETIVO_OBJETIVOS_TIPOS_BOMBARDERO_H_ */
