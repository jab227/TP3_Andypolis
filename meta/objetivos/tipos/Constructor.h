#ifndef OBJETIVOS_TIPOS_CONSTRUCTOR_H_
#define OBJETIVOS_TIPOS_CONSTRUCTOR_H_

#include "../Objetivo.h"

class Constructor : public Objetivo {
	private:
	 const Mapa* mapa;
	 Lista<std::string> claves;
	public:
	 Constructor(Jugador *jugador, Mapa* mapa);
	 ~Constructor();
	 bool actualizar();
	 bool estan_construidos(const Lista<Coordenada>& edificios);
};

#endif /* OBJETIVOS_TIPOS_CONSTRUCTOR_H_ */
