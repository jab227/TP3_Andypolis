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
	Planos* planos;
	Mapa* mapa;
//Metodos
public:
	//PRE: -
	//POST: se crea una empresa constructora vacia.
	Empresa_Constructora();
	Empresa_Constructora(Planos* plano, Mapa* mapa);

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
	//POST: 
	void modificar_edificios();

	//PRE: los archivos deben estar cargados
	//POST: se muestran los materiales disponibles en el stock del almacen
	void mostrar_materiales(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se muestra el mapa de terrenos y el de los edificios/materiales ubicados en mapa
	void mostrar_mapa();

	//PRE: los archivos deben estar cargados
	//POST: se pide al usuario una coordenada y se muestra informacion sobre lo que hay en ella
	void consultar_coordenada();

	//PRE: el juegador y el mapa deben estar bien cargados
	//POST: se pide al usuario que ingrese coordenadas validas y se cambia la posicion del jugador
	//a las coordenadas ingresadas (no se mueve por recorrido)
	void iniciar_coordenadas_jugador(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se muestran los edificios que hay construidos junto con sus coordenadas
	void mostrar_construidos(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se guardan los datos de los archivos de materiales y las ubicaciones
	void guardar_archivos(std::string ruta_materiales, std::string ruta_ubicaciones);

	//PRE: los archivos deben estar cargados
	//POST: se suman al almacen los recursos producidos por los edificios
	void recolectar_recursos(Jugador* jugador);

	//PRE: los archivos deben estar cargados
	//POST: se generan materiales aleatorios en caminos aleatorios del mapa
	void lluvia_de_recursos();

	//PRE: los archivos deben estar cargados
	//POST: se vacian los materiales del mapa
	void vaciar_materiales();

	void reparar_edificio(Jugador* jugador);

	void comprar_bombas(Jugador* jugador);
	
	void atacar_edificio(Jugador* jugador_activo, Jugador* jugador_inactivo);
	
	void mover_jugador(Jugador* jugador);

	//void ver_objetivos(); Implementado en jugadores

	//La idea es que devuelven en string lo que hay que imprimir en el archivo de salida.

	std::string estado_actual_planos(); // por si modifican el archivo al comenzar la partida.
	
	std::string estado_actual_ubicaciones(Lista<Jugador*> jugadores);


private:
	//PRE: ruta debe ser la ruta a un archivo existente y bien formado. el mapa debe estar cargado.
	//POST: se cargan las ubicaciones en el mapa.
	bool cargar_ubicaciones(std::string ruta, Jugador* jugador);

	//PRE: ruta debe ser la ruta a un archivo existente. el mapa debe estar cargado.
	//POST: se guardan la informacion de las ubicaciones en el archivo.
	void guardar_ubicaciones(std::string ruta);

	//PRE: la linea debe estar bien formada con la ubicacion de un edificio o material. fila y columna
	//debe ser valido en el mapa
	//POST: se carga el contenido de la ubicacion en el mapa, sea material o edificio.
 
	void sumar_contenido(std::string contenido,Coordenada coordenada, Jugador* jugador);
 

	//PRE: -
	//POST: se pide un edificio valido al usuario y devuelve true. de no obtener un edificio valido
	//devuelve false
	std::string pedir_edificio_construir( Jugador* jugador);

	//PRE: -
	//POST: se pide un edificio valido al usuario y devuelve true. de no obtener un edificio valido
	//devuelve false
	Resultado_Chequeos pedir_edificio(std::string& edificio);

	//PRE: -
	//POST: devuelve si se ingreso salir, si no existe el edificio, si se llego a la maxima cantidad
	//permitida del edificio, si no alcanzan los materiales o si no ocurre nada de lo anterior. en este
	//ultimo caso, edificio se iguala a edificio_ingresado
	Resultado_Chequeos chequeo_edificio(const std::string& edificio_ingresado);

	//PRE: -
	//POST: devuelve si se ingreso salir, si lo ingresado no es valido, si las coordenadas estan fuera de rango,
	//si coresponden a un casillero no construible, si el casillero esta libre o si no ocurre nada de lo anterior.
	//en este ultimo caso, fila = fila_ingresada, columna = columna_ingresada y edificio = el ocupado en el casillero.
	Resultado_Chequeos chequeo_demoler(std::string fila_ingresada, std::string columna_ingresada, int &fila, int &columna, std::string &edificio);

	//PRE:
	//POST: devuelve si no alcanzan los materiales o si el edificio no necesita reparacion. En caso de que alcancen y el edificio lo necesite,
	//se repara el edificio y devuelve exito.
	Resultado_Chequeos chequeo_reparar_edificio(Jugador* jugador, Lista<Material> listado_necesario, Coordenada coordenada);

	//PRE: -
	//POST: se muestra un mensaje por terminal correspondiente al resultado del chequeo
	bool mostrar_mensaje_chequeo(Resultado_Chequeos chequeo);

	//PRE: -
	//POST: se pide al usuario que ingrese un "si" o un "no" y devuelve true en caso de si y false en caso contrario
	std::string pedir_si_no();

	//PRE: edificio debe ser valido y fila y columna estar en el rango del mapa.
	//POST: se realizan las acciones al construir un edificio en la fila y columna.
	void edificio_construido_confirmado(const std::string &edificio, const Coordenada& coordenada, Jugador* jugador);

	//PRE: -
	//POST: Pide la fila y la columna. Lo devuelve por coordenada.
	Resultado_Chequeos pedir_coordenadas(Coordenada& coordenada);

	Resultado_Chequeos chequeo_coordenadas(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada);
	
	Resultado_Chequeos pedir_bombas(std::size_t &bombas);
	
	Resultado_Chequeos chequeo_bombas(std::string bombas_ingresadas, std::size_t &bombas);

	Resultado_Chequeos pedir_materiales(std::string nombre, std::size_t &madera, std::size_t &piedra, std::size_t &metal);

	Resultado_Chequeos chequeo_materiales(std::string nombre, std::string madera_ingresada, std::string piedra_ingresada, std::string metal_ingresada, std::size_t &piedra, std::size_t &madera, std::size_t &metal);

	void bombardear_coordenadas(Coordenada coordenada, Jugador* jugador_inactivo);

	//La idea es que resuelven en string lo que hay que imprimir en el archivo de salida.
	std::string estado_actual_materiales_mapa();

	std::string estado_actual_edificios_mapa(Jugador* jugador);

};

#endif /* EMPRESACONSTRUCTORA_H_ */
