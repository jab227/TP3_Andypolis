#ifndef JUEGO_H_
#define JUEGO_H_

#include "../programa/Programa.h"

const std::string RUTA_MATERIALES = "./saves/materiales.txt"; 
const std::string RUTA_EDIFICIOS = "./saves/edificios.txt";
const std::string RUTA_MAPA = "./saves/mapa.txt"; 
const std::string RUTA_UBICACIONES = "./saves/ubicaciones.txt";

class Juego {
    private:
        Programa programa_;
        // Pre: Func es una funcion que valida la opcion, de
        // la forma -> bool funcion(opcion);
        // Pos: Se pide al usuario una opcion y se la valida,
        // en caso de que sea valida se devuelve la opcion
        // como size_t; en otro caso se pide que vuelva a
        // ingresar la opcion.
        template <typename Func>
        std::size_t pedir_opcion_valida(Func funcion) {
            std::string opcion;
	        cout << "Opcion:   " ;
	        getline(cin, opcion);
	        while(!funcion(opcion)) {
		    cout << "La opcion ingresada no es valida." << endl;
		    cout << "Opcion:   " ;
		    getline(cin, opcion);
	    }
	return stoul(opcion);
        };
        // Pre: -
        // Pos: Muestra un mensaje de bienvenida.
        void mensaje_bienvenida() const;
        // Pre: -
        // Pos: Imprime un mensaje al usuario, informandole
        // que no tiene la energia suficiente para realizar
        // la accion.
        void energia_insuficiente() const;
        // Pre: -
        // Pos: Muestra un mensaje de victoria.
        void mensaje_victoria() const;
        // Pre: -
        // Pos: Muestra un mensaje despedida.
        void mensaje_despedida() const;
    public:
        // Pre: -
        // Pos: Construye una nueva instancia de juego.
        Juego();
        // Destructor default
        ~Juego() = default;
        Salida comenzar_juego();
        Salida jugar();
        void finalizar_juego(Salida salida);
};

#endif