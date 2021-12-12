#ifndef OBJETIVOS_TIPOS_MINERO_H_
#define OBJETIVOS_TIPOS_MINERO_H_

#include "../Objetivo.h"

class Minero : public Objetivo{
	private:
	 const Mapa* mapa;
	 bool mina;
	 bool mina_oro;

	 // Pre: -
	 // Pos: True si tanto mina oro como mina estan construidos,
	 // False en otro caso
	 bool estan_construidos(const Lista<Coordenada>& edificios);
	public:
	 Minero(Jugador* jugador, Mapa* mapa);
	 ~Minero();
	 bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_MINERO_H_ */
