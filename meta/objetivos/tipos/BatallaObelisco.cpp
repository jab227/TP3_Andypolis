#include "BatallaObelisco.h"
#include "../../../utils/coordenada.h"
#include "../../../empresa/Planos.h"

Batalla_Obelisco::Batalla_Obelisco(Jugador* jugador, Mapa* mapa) : Objetivo("Batalla por el Obelisco",jugador), 
                                                                    mapa(mapa) {
    cumplido = esta_construido(jugador->obtener_edificios());
}

bool Batalla_Obelisco::actualizar() {
    if (!cumplido) {
        cumplido = esta_construido(jugador->obtener_edificios());
    }
    return cumplido;
}

bool Batalla_Obelisco::esta_construido(const Lista<Coordenada>& edificios) {
        std::string nombre_edificio;
        bool construido = false;
        for (std::size_t i = 1; i <= edificios.consulta_largo() && !construido; ++i) {
            nombre_edificio = mapa->obtener_contenido_ubicacion(edificios.consulta(i));
            construido = (nombre_edificio == "obelisco");
        }
    return construido;
}