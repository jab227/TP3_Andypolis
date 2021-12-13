#ifndef MAPA_H_
#define MAPA_H_

#include "../edificio/Edificio.h"
#include "../material/Material.h"
#include "../Casillero/Casillero.h"
#include "../Casillero/Casillero.h"
#include "../utils/Lista.h"
#include "../utils/coordenada.h"

class Mapa {
//Atributos
private:
	std::size_t filas, columnas;
	Casillero*** terreno;
//Metodos
public:
	//PRE: -
	//POST: Crea el mapa a partir de un string, el mapa es de filas x columnas. 
	Mapa(const std::string& mapa, std::size_t filas, std::size_t columnas);

	//PRE: -
	//POST: se destruye el mapa liberando toda la memoria utilizada
	~Mapa();

	//PRE: -
	//POST: devuelve true si las coordenadas se encuentran en el rango del mapa y false de lo contrario
	bool es_coordenada_valida(const Coordenada& coordenada);

	//PRE: el terreno debe estar cargado
	//POST: Muestra el identificador del casillero con color.
	void mostrar_casillero(Coordenada coordenada, std::string contenido);

	//PRE: la posicion debe ser valida
	//POST: se muestra informacion sobre la ubicacion consultada
	void saludar_coordenada(const Coordenada& coordenada);

	//PRE: el edificio y la posicion deben ser validos y el casillero estar vacio
	//POST: se construye el edificio en la posicion ingresada
	Resultado_Chequeos construir_edificio_ubicacion(const std::string & edificio, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida
	//POST: se elimina el edificio de esa posicion y se devuelve el nombre del edificio demolido por interfaz
	Resultado_Chequeos demoler_edificio_ubicacion(std::string &edificio, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida
	//POST: Pide al casillero ubicado en la coordenada que se repare cuando reparar es true. Si reparar es false, 
	// es solo para saber si debe repararse o no el edificio.
	Resultado_Chequeos reparar_edificio_ubicacion(const Coordenada& coordenada, bool reparar = true) const;

	//PRE: el material y la posicion debe ser valido, y el casillero estar vacio
	//POST: se pone el material en la ubicacion ingresda
	void poner_material_ubicacion(std::string material, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida y estar ocupada por un material
	//POST: se elimina el material de esa posicion y se devuelve el material quitado
	void recolectar_material_ubicacion(const Coordenada& coordenada, Material& material);

	//PRE: la posicion debe ser valida
	//POST: se devuelve el contenido en la ubicacion ingresada o CONTENIDO_VACIO si el casillero no esta
	//ocupado
	std::string obtener_contenido_ubicacion(const Coordenada& coordenada) const;

	//PRE: -
	//POST: se generan materiales aleatorios por el mapa. devuelve true si no se genero ningun material, y
	//false si se genero al menos 1 material de alguno
	bool generar_materiales_aleatorios(Coordenada jugador1, Coordenada jugador2);

	//PRE: las coordenadas deben ser un edificio
	//POST: se resta 1 de vida al edificio. Si el edificio queda en 0 de vida se destruye y devuelve true.
	bool explota_bomba(std::string &edificio, Coordenada coordenadas);

	//PRE: la coordenada debe ser valida
	//POST: devuelve el identificador del casillero en la coordenada
	char obtener_identificador_casillero(Coordenada coordenada);

	//PRE: terreno != nullptr;
	//POST: Retorna en un string los materiales que se encuentran en el mapa con sus coordenadas.
	std::string estado_actual_materiales();

private:
	//PRE: ruta debe ser a un archivo existente y bien cargado para el mapa
	//POST: se carga el mapa con los casilleros correspondientes a los datos del archivo
	void cargar_terreno(const std::string& terreno);

	//PRE: lectura debe ser la linea con los terrenos de la fila filas bien formada de largo columnas
	//POST: se agregan los casilleros vacios a la fila segun la lectura
	void  iniciar_filas_casilleros(std::size_t fila, const std::string& mapa);

	//PRE: el ocupador debe ser un material o edificio valido
	//POST: se devuelve la letra dentificadora del ocupador
	std::string identificador_ocupados(std::string ocupador);

	//PRE: el mapa debe estar bien cargado
	//POST: Devuelve una lista de los casilleros transitables libres en el mapa
	void casilleros_libres_transitables(Lista<Coordenada>& lista_desocupados, Coordenada jugador1, Coordenada jugador2);

	//PRE: minimo <= maximo
	//POST: se genera un numero aleatorio que puede ir desde minimo hasta maximo incluido
	std::size_t numero_aleatorio(std::size_t minimo, std::size_t maximo);

	//PRE: material debe ser un material valido y numero_casillero menor a los casilleros libres transitables
	//POST: se crea y ubica un material en el N-esimo casillero transitable libre.
	void generar_material(std::string material, Coordenada coordenada);

	//PRE: -
	//POST: genera un conjunto del material con su cantidad predeterminada o devuelve nullptr si el material no existe
	Material generar_conjunto_material(std::string material);


};

#endif /* MAPA_H_ */
