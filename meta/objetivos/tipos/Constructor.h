#ifndef OBJETIVOS_TIPOS_CONSTRUCTOR_H_
#define OBJETIVOS_TIPOS_CONSTRUCTOR_H_

#include "../Objetivo.h"

class Constructor : public Objetivo {
	private:
	 const Mapa* mapa;
	public:
	 Constructor(Jugador *jugador, Mapa* mapa);
	 ~Constructor();
	 bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_CONSTRUCTOR_H_ */
