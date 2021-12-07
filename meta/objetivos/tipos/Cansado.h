#ifndef OBJETIVOS_TIPOS_CANSADO_H_
#define OBJETIVOS_TIPOS_CANSADO_H_

#import "../Objetivo.h"

class Cansado : public Objetivo{
public:
	Cansado(Jugador* jugador);
	bool actualizar();
};

#endif /* OBJETIVOS_TIPOS_CANSADO_H_ */
