#ifndef EMPRESACONSTRUCTORA_H_
#define EMPRESACONSTRUCTORA_H_

#include "Almacen.h"
#include "Planos.h"
#include "Mapa.h"
#include "../utils/Lista.h"
#include "../jugador/jugadores/JugadorUno.h"
#include "../jugador/jugadores/JugadorDos.h"

const int ENERGIA_CONSTRUIR = 15, ENERGIA_LISTAR_CONSTRUIDOS = 0, ENERGIA_DEMOLER = 15, ENERGIA_ATACAR = 30,
		  ENERGIA_REPARAR = 25,  ENERGIA_CONSULTAR = 0, ENERGIA_LISTAR_MATERIALES = 0,
		  ENERGIA_OBJETIVOS = 0, ENERGIA_RECOLECTAR = 20, ENERGIA_MOVERSE = 0, ENERGIA_FIN_TURNO = 0, ENERGIA_GUARDAR_SALIR = 0;

class Empresa_Constructora {
//Atributos
private:
	Almacen* almacen;
	Planos* planos;
	Mapa* mapa;
//Metodos
public:
	//PRE: -
	//POST: se crea una empresa constructora vacia.
	Empresa_Constructora();

	//PRE: las rutas del mapa y edificios deben ser a archivos existentes.
	//POST: se inicializan los atributos con las rutas ingresadas y devuelve true si el archivo de ubicaciones
	//existe y no esta vacio, devuelve false en caso contrario.
	bool cargar_archivos(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaiones);

	//PRE: -
	//POST: se libera la memoria utilizada
	~Empresa_Constructora();

	//PRE: los archivos deben estar cargados y el jugador valido con la energia suficiente
	//POST: se construye un edificio pidiendo al usuario en nombre y las coordenadas
	void construir_edificio( Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se destruye un edificio pidiendo al usuario las cordenadas
	void demoler_edificio(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se muestran los edificios existentes junto con sus materiales requeridos para
	//construirlo, la cantidad construida y los que se pueden construir
	void mostrar_edificios();

	//PRE: los archivos deben estar cargados
	//POST: se muestran los materiales disponibles en el stock del almacen
	void mostrar_materiales();

	//PRE: los archivos deben estar cargados
	//POST: se muestra el mapa de terrenos y el de los edificios/materiales ubicados en mapa
	void mostrar_mapa();

	//PRE: los archivos deben estar cargados
	//POST: se pide al usuario una coordenada y se muestra informacion sobre lo que hay en ella
	void mostrar_coordenada();

	//PRE: los archivos deben estar cargados
	//POST: se muestran los edificios que hay construidos junto con sus coordenadas
	void mostrar_construidos(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se guardan los datos de los archivos de materiales y las ubicaciones
	void guardar_archivos(string ruta_materiales, string ruta_ubicaciones);

	//PRE: los archivos deben estar cargados
	//POST: se suman al almacen los recursos producidos por los edificios
	void producir_recursos(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se generan materiales aleatorios en caminos aleatorios del mapa
	void lluvia_de_recursos();

	//PRE: los archivos deben estar cargados
	//POST: se vacian los materiales del mapa
	void vaciar_materiales();


private:
	//PRE: ruta debe ser la ruta a un archivo existente y bien formado. el mapa debe estar cargado.
	//POST: se cargan las ubicaciones en el mapa.
	bool cargar_ubicaciones(string ruta, Jugador* jugador);

	//PRE: ruta debe ser la ruta a un archivo existente. el mapa debe estar cargado.
	//POST: se guardan la informacion de las ubicaciones en el archivo.
	void guardar_ubicaciones(string ruta);

	//PRE: la linea debe estar bien formada con la ubicacion de un edificio o material. fila y columna
	//debe ser valido en el mapa
	//POST: se carga el contenido de la ubicacion en el mapa, sea material o edificio.
 
	void sumar_contenido(string contenido,Coordenada coordenada, Jugador* jugador);
 

	//PRE: -
	//POST: se pide un edificio valido al usuario y devuelve true. de no obtener un edificio valido
	//devuelve false
	std::string pedir_edificio(const Jugador* &jugador);

	//PRE: -
	//POST: devuelve si se ingreso salir, si no existe el edificio, si se llego a la maxima cantidad
	//permitida del edificio, si no alcanzan los materiales o si no ocurre nada de lo anterior. en este
	//ultimo caso, edificio se iguala a edificio_ingresado
	Resultado_Chequeos chequeo_construir(const std::string& edificio_ingresado, const Jugador* &jugador);

	//PRE: -
	//POST: devuelve si se ingreso salir, si lo ingresado no es valido, si las coordenadas estan fuera de rango,
	//si coresponden a un casillero no construible, si el casillero esta libre o si no ocurre nada de lo anterior.
	//en este ultimo caso, fila = fila_ingresada, columna = columna_ingresada y edificio = el ocupado en el casillero.
	Resultado_Chequeos chequeo_demoler(string fila_ingresada, string columna_ingresada, int &fila, int &columna, string &edificio);

	//PRE: -
	//POST: se muestra un mensaje por terminal correspondiente al resultado del chequeo
	bool mostrar_mensaje_chequeo(Resultado_Chequeos chequeo);

	//PRE: -
	//POST: se pide al usuario que ingrese un "si" o un "no" y devuelve true en caso de si y false en caso contrario
	string pedir_si_no();

	//PRE: edificio debe ser valido y fila y columna estar en el rango del mapa.
	//POST: se realizan las acciones al construir un edificio en la fila y columna.
	void edificio_construido_confirmado(const std::string &edificio, const Coordenada& coordenada, Jugador* jugador);

	//PRE: -
	//POST: Pide la fila y la columna. Lo devuelve por coordenada.
	Resultado_Chequeos pedir_coordenadas(Coordenada& coordenada);

	Resultado_Chequeos chequeo_coordenadas(string fila_ingresada, string columna_ingresada, Coordenada coordenada);
};

#endif /* EMPRESACONSTRUCTORA_H_ */
