#include "juego.h"
#include "../printer/color_printer.h"
#include "../utils/Titulos.h"

Juego::Juego() : programa_(Programa(RUTA_MATERIALES, RUTA_EDIFICIOS,
                                    RUTA_MAPA, RUTA_UBICACIONES)) {}

Salida Juego::comenzar_juego() {
    mensaje_inicial_bienvenida();
    std::size_t opcion;
    Salida salida;
    do
    {
        programa_.mostrar_menu_inicio();
        opcion = pedir_opcion_valida([&](std::string opcion)
                                     { return programa_.es_opcion_valida_inicio(opcion); });
        programa_.limpiar_pantalla();
        salida = programa_.procesar_opcion_inicio(opcion);
    } while (salida != GUARDAR_Y_SALIR && salida != COMENZAR_JUEGO);
    return salida;
}

Salida Juego::jugar() {
    std::size_t opcion;
    Salida salida = CONTINUAR;
    if (!programa_.victoria())
    {
        do
        {
            programa_.mostrar_menu_juego();
            opcion = pedir_opcion_valida(
                [&](std::string opcion)
                { return programa_.es_opcion_valida_juego(opcion); });
            programa_.limpiar_pantalla();
            if (programa_.es_energia_suficiente(opcion))
                salida = programa_.procesar_opcion_juego(opcion);
            else
                energia_insuficiente();
        } while (salida != GUARDAR_Y_SALIR && salida != VICTORIA);
    }
    else
    {
        salida = VICTORIA;
    }
    return salida;
}

void Juego::finalizar_juego(Salida salida) {
    programa_.limpiar_pantalla();
    if (salida == VICTORIA){
    	if(programa_.jugador_activo_actual() == 1)
    		mensaje_victoria_jugador1();
    	else
    		mensaje_victoria_jugador2();
    }
    programa_.guardar_archivos(RUTA_UBICACIONES,
                               RUTA_MATERIALES, RUTA_EDIFICIOS);
    mensaje_despedida();
}

void Juego::mensaje_inicial_bienvenida() const {
    programa_.limpiar_pantalla();
    mensaje_bienvenida();
}

void Juego::energia_insuficiente() const {
    cout << "Energia insuficiente para realizar la accion" << endl;
}

void Juego::mensaje_victoria_jugador1() const {
    mensaje_jugador_1();
}

void Juego::mensaje_victoria_jugador2() const {
    mensaje_jugador_2();
}

void Juego::mensaje_despedida() const
{
    std::cout << "Adios" << std::endl;
}
