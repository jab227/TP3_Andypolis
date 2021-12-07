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
<<<<<<< HEAD
	//PRE: ruta debe ser a un archivo exitente de un mapa bien formado
	//POST: se crea un mapa con los datos del archivo
	Mapa(std::string ruta);
=======
	//PRE: -
	//POST: Crea el mapa a partir de un string, el mapa es de filas x columnas. 
	Mapa(const std::string& mapa, std::size_t filas, std::size_t columnas);
>>>>>>> DiccionarioEdificios

	//PRE: -
	//POST: se destruye el mapa liberando toda la memoria utilizada
	~Mapa();

	//PRE: -
	//POST: devuelve true si las coordenadas se encuentran en el rango del mapa y false de lo contrario
	bool es_cordenada_valida(const Coordenada& coordenada);

	//PRE: -
	//POST: se chequea que la ubicacion sea disponible para construir un edificio. devuelve si las coordenadas estan
	//fuera de rango, si el casillero no es construible, si esta ocupado o si no ocurre nada de lo anterior.
	Resultado_Chequeos chequeo_ubicar_edificio(const Coordenada& coordenada);

	//PRE: -
	//POST: se chequea que la ubicacion sea disponible para demoler un edificio. devuelve si las coordenadas estan
	//fuera de rango, si el casillero no es construible, si esta libre o si no ocurre nada de lo anterior. en este ultimo
	//caso, edificio vale el edificio a demoler.
	Resultado_Chequeos chequeo_demoler_edificio(const Coordenada& coordenada, std::string &edificio);

	//PRE: el mapa debe estar cargado
	//POST: se muestra el mapa de los edificios con los terrenos en colores
	void mostrar_mapa();

	//PRE: la posicion debe ser valida
	//POST: se muestra informacion sobre la ubicacion consultada
	void saludar_coordenada(const Coordenada& coordenada);

	//PRE: el edificio y la posicion deben ser validos y el casillero estar vacio
	//POST: se construye el edificio en la posicion ingresada
	Resultado_Chequeos construir_edificio_ubicacion(const std::string & edificio, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida y estar ocupada por un edificio
	//POST: se elimina el edificio de esa posicion y se devuelve el edificio demolido por interfaz
	Resultado_Chequeos demoler_edificio_ubicacion(std::string &edificio, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida y estar ocupada por un edificio
	//POST: 
	Resultado_Chequeos reparar_edificio_ubicacion(std::string& edificio, const Coordenada& coordenada);

	//PRE: el material y la posicion debe ser valido, y el casillero estar vacio
	//POST: se pone el material en la ubicacion ingresda
	void poner_material_ubicacion(std::string material, const Coordenada& coordenada);

	//PRE: la posicion debe ser valida y estar ocupada por un material
	//POST: se elimina el material de esa posicion y se devuelve el material quitado
	void recolectar_material_ubicacion(const Coordenada& coordenada, Almacen* inventario);

	//PRE: -
	//POST: se chequea si se puede poner un material en el casillero ingresado. devuelve si las coordenadas
	//estan fuera de rango, si el casillero no puede contener materiales, si esta ocupado o si no ocurre
	//nada de lo anterior
	Resultado_Chequeos chequeo_poner_material(const Coordenada& coordenada);

	//PRE: -
	//POST: se chequea si se puede sacar un material del casillero ingresado. devuelve si las coordenadas
	//estan fuera de rango, si el casillero no puede contener materiales, si esta libre o si no ocurre
	//nada de lo anterior
	Resultado_Chequeos chequeo_sacar_material(const Coordenada& coordenada);
//WHY: Se usa?
	//PRE: la posicion debe ser valida
	//POST: se devuelve el contenido en la ubicacion ingresada o CONTENIDO_VACIO si el casillero no esta
	//ocupado
	std::string obtener_contenido_ubicacion(const Coordenada& coordenada) const;

	//PRE: -
	//POST: se generan materiales aleatorios por el mapa. devuelve true si no se genero ningun material, y
	//false si se genero al menos 1 material de alguno
	bool generar_materiales_aleatorios();

	//PRE: -
	//POST: se limpia todo el mapa de materiales
	void vaciar_materiales();
private:
//WHY: Se usa?
	//PRE: casillero uno del mapa ocupado por un edificio, coordenadas deben corresponder al casillero
	//POST: se agregan las coordenadas a la lista de coordenadas del edificio correspondiente. si no existe aun esa lista,
	//se la crea y se agrega tambien el nombre del edificio en la lista de nombres
	void agregar_edificio_a_listas(Casillero* casillero, std::size_t* coordenadas, Lista<std::string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas);

	//PRE: lista de coordenadas deben ser distas ubicadas en memoria dinamica con coordenadas en memoria dinamica y el orden de las listas
	//se corresponden con un edificio.
	//POST: se imprime por consola los edificios de la lista junto con la cantidad construidos y sus ubicaciones. tambien se libera la lista
	//de coordenadas
	void mostrar_edificios(Lista<std::string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas);

	//PRE: ruta debe ser a un archivo existente y bien cargado para el mapa
	//POST: se carga el mapa con los casilleros correspondientes a los datos del archivo
	void cargar_terreno(std::string ruta);

	//PRE: lectura debe ser la linea con los terrenos de la fila filas bien formada de largo columnas
	//POST: se agregan los casilleros vacios a la fila segun la lectura
	void  iniciar_filas_casilleros(std::size_t filas, std::string lectura);

	//PRE: el ocupador debe ser un material o edificio valido
	//POST: se devuelve la letra dentificadora del ocupador
	std::string identificador_ocupados(std::string ocupador);

	//PRE: el mapa debe estar bien cargado
	//POST: Devuelve una lista de los casilleros transitables libres en el mapa
	void casilleros_libres_transitables(Lista<Coordenada>*& lista_desocupados);

	//PRE: minimo <= maximo
	//POST: se genera un numero aleatorio que puede ir desde minimo hasta maximo incluido
	std::size_t numero_aleatorio(std::size_t minimo, std::size_t maximo);

	//PRE: material debe ser un material valido y numero_casillero menor a los casilleros libres transitables
	//POST: se crea y ubica un material en el N-esimo casillero transitable libre.
	void generar_material(std::string material, Coordenada coordenada);
};

#endif /* MAPA_H_ */
