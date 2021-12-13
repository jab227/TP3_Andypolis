#ifndef OBJETIVOS_TIPOS_LETRADO_H_
#define OBJETIVOS_TIPOS_LETRADO_H_

#include "../Objetivo.h"

class Letrado : public Objetivo{
	const Mapa* mapa;
	bool estan_construidos(const Lista<Coordenada>& edificios);
public:

	Letrado(Jugador* jugador, Mapa* mapa);
	bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_LETRADO_H_ */
