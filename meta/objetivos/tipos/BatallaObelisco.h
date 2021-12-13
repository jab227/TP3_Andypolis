#ifndef BATALLA_OBELISCO_H_
#define BATALLA_OBELISCO_H_

#include "../Objetivo.h"

class Batalla_Obelisco : public Objetivo {
    private:
     const Mapa* mapa;
    public:
     Batalla_Obelisco(Jugador* jugador, Mapa* mapa);
     bool actualizar() override;
};

#endif