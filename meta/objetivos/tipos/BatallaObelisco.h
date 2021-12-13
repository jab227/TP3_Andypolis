#ifndef BATALLA_OBELISCO_H_
#define BATALLA_OBELISCO_H_

#include "../Objetivo.h"

class Batalla_Obelisco : public Objetivo {
    private:
     const Mapa* mapa;
     // Pre: -   
     // Pos: Recorre la lista de coordenadas, si en alguna de estas
     // coordenadas se encuetra el obelisco devuelve True; False
     // en otro caso.
     bool esta_construido(const Lista<Coordenada>& edificios);
    public:
     // Pre: jugador != nullptr y mapa != nullptr
     // Pos: Construye el objetivo Batalla_Obelisco.
     Batalla_Obelisco(Jugador* jugador, Mapa* mapa);
     // Destructor por defecto.
     ~Batalla_Obelisco() = default;
	 // Pre:  -
     // Pos: se actualiza el objetivo, True si esta
	 // cumplido, false en otro caso.
     bool actualizar() override;
};

#endif