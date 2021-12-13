#ifndef OBJETIVOS_TIPOS_CONSTRUCTOR_H_
#define OBJETIVOS_TIPOS_CONSTRUCTOR_H_

#include "../Objetivo.h"

class Constructor : public Objetivo {
	private:
	 const Mapa* mapa;
	 Lista<std::string> claves;
	 // Pre: -
	 // Pos: True si fue construido un edificio de cada tipo,
	 // False en otro caso.
	 bool estan_construidos(const Lista<Coordenada>& edificios);
	public:
     // Pre: jugador != nullptr y mapa != nullptr
     // Pos: Construye el objetivo Constructor.
	 Constructor(Jugador *jugador, Mapa* mapa);
	 // Destructor por defecto.
	 ~Constructor() = default;
	 // Pre: -
     // Pos: se actualiza el objetivo, True si esta
	 // cumplido, false en otro caso.
	 bool actualizar() override;
};

#endif /* OBJETIVOS_TIPOS_CONSTRUCTOR_H_ */
