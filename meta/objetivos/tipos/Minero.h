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
     // Pre: jugador != nullptr y mapa != nullptr
     // Pos: Construye el objetivo Minero.
	 Minero(Jugador* jugador, Mapa* mapa);
	// Pre: -
     // Pos: se actualiza el objetivo, True si esta
	 // cumplido, false en otro caso.
	 bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_MINERO_H_ */
