#ifndef OBJETIVOS_TIPOS_MINERO_H_
#define OBJETIVOS_TIPOS_MINERO_H_

#include "../Objetivo.h"

class Minero : public Objetivo{
	private:
	 const Mapa* mapa;
	public:
	 Minero(Jugador* jugador, Mapa* mapa);
	 ~Minero();
	 bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_MINERO_H_ */
