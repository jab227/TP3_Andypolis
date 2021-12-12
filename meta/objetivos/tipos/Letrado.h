#ifndef OBJETIVOS_TIPOS_LETRADO_H_
#define OBJETIVOS_TIPOS_LETRADO_H_

#include "../Objetivo.h"

class Letrado : public Objetivo{
	const Mapa* mapa;
	std::size_t contador;
public:
	Letrado(Jugador* jugador, Mapa* mapa);
	~Letrado();
	bool actualizar();
	bool estan_construidos(const Lista<Coordenada>& edificios);
};

#endif /* OBJETIVOS_TIPOS_LETRADO_H_ */
