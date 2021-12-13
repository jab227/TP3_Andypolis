#ifndef EMPRESACONSTRUCTORA_H_
#define EMPRESACONSTRUCTORA_H_

#include "Almacen.h"
#include "Planos.h"
#include "Mapa.h"
#include "../utils/Lista.h"
#include "../jugador/Jugador.h"
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
	//POS: se crea una empresa constructora vacia.
	Empresa_Constructora();

	//PRE: -
	//POS: se crea una empresa constructora con plano y mapa.
	Empresa_Constructora(Planos* plano, Mapa* mapa);

	//PRE: -
	//POS: se libera la memoria utilizada
	~Empresa_Constructora();

	//PRE: -
	//POS: se muestran los edificios existentes junto con sus materiales requeridos para
	//construirlo y los que se pueden construir
	void mostrar_edificios();

	//PRE: planos != nullptr;
	//POS: Permite modificar los materiales de construccion 
	//necesarios para los edificios que se encuentran en planos.
	void modificar_edificios();

	//PRE: mapa != nullptr;
	//POS: se muestra el mapa de terrenos y el de los edificios/materiales/jugadores ubicados en mapa
	void mostrar_mapa(Lista<Jugador*> jugadores);

	//PRE: jugador != nullptr;
	//POS: Muestra los edificios construidos por el jugador y sus coordenadas.
	void mostrar_construidos(Jugador* jugador);

	//PRE: jugador != nullptr;
	//POS: Permite al jugador moverse a traves del mapa.
	void mover_jugador(Jugador* jugador);

	//PRE: jugador_activo != nullptr, jugador_inactivo != nullptr;
	//POS: se pide al usuario una coordenada y se muestra informacion sobre lo que hay en ella
	void consultar_coordenada(Jugador* jugador_activo, Jugador* jugador_inactivo);

	//PRE: jugador != nullptr, mapa != nullptr; 
	//POS: se pide al usuario que ingrese coordenadas validas y se cambia la posicion del jugador
	//a las coordenadas ingresadas (no se mueve por recorrido)
	void iniciar_coordenadas_jugador(Jugador* jugador);

	//PRE: jugador != nullptr;
	//POS: se suman al almacen los recursos producidos por los edificios.
	void recolectar_recursos(Jugador* jugador);

	//PRE: jugador1 y jugador2 deben ser Coordenadas validas.
	//POS: se generan materiales aleatorios en caminos aleatorios del mapa
	void lluvia_de_recursos(Coordenada jugador1, Coordenada jugador2);

	//PRE: jugador != nullptr
	//POS: se construye un edificio pidiendo al usuario en nombre y las coordenadas
	void construir_edificio(Jugador* jugador);

	//PRE:  jugador != nullptr; mapa != nullptr;
	//POS: se destruye un edificio pidiendo al usuario las cordenadas
	void demoler_edificio(Jugador* jugador);

	//PRE: jugador != nullptr; planos != nullptr;
	//POS: se repara un edificio del jugador, si es posible, pidiendo al usuario las coordenadas.
	void reparar_edificio(Jugador* jugador);

	//PRE: jugador != nullptr; planos != nullptr;
	//POS: se ataca un edificio del jugador_inactivo, utilizando una bomba del jugador_activo y pidiendo al usuario las coordenadas.
	void atacar_edificio(Jugador* jugador_activo, Jugador* jugador_inactivo);
	
	//PRE: jugador != nullptr; planos != nullptr;
	//POS: se compran bombas para el jugador, pidiendole al usuario la cantidad a comprar.
	void comprar_bombas(Jugador* jugador);
	
	//PRE: planos != nullptr;
	//POS: Devuelve un string con loa edificios de manera estructurada para guardar.
	std::string estado_actual_planos(); 
	
	//PRE: -
	//POS: Devuelve un string con las ubicaciones de los materiales, jugadores y sus edificios, estructurado para guardar.
	std::string estado_actual_ubicaciones(Lista<Jugador*> jugadores);
	
	//PRE: jugador != nullptr;
	//POS: Almacena en las reservas del jugador los materiales producidos por sus edificios.
	void producir_materiales(Jugador* jugador);

private:
	//PRE: jugador != nullptr;
	//POS: se pide un edificio valido para construir por el jugador al usuario y devuelve true. De no obtener un edificio valido
	//devuelve false
	std::string pedir_edificio_construir( Jugador* jugador);

	//PRE: -
	//POS: se pide un edificio existente al usuario y chequea lo que ingresa.
	Resultado_Chequeos pedir_edificio(std::string& edificio);

	//PRE: -
	//POS: se pide al usuario que ingrese un "si" o un "no" y devuelve true en caso de si y false en caso contrario
	std::string pedir_si_no();

	//PRE: -
	//POS: Pide la fila y la columna y chequea que sean validas. En caso de serlo, Lo devuelve la coordenada por interfaz.
	//En caso de no ser valida, devuelve por interfaz la Coordenada(COORDENADA_VACIA,COORDENADA_VACIA).
	Resultado_Chequeos pedir_coordenadas(Coordenada& coordenada);

	//PRE: -
	//POS: Pide una cantidad de bombas y chequea que sean validas. En caso de serlo, Lo devuelve por bombas.
	//En caso de no ser valida, no modifica bombas.
	Resultado_Chequeos pedir_bombas(std::size_t &bombas);

	//PRE: -
	//POS: Pide el nombre y los materiales de construccion de un edificio, luego chequea que los valores sean validos.
	//En caso de serlos, los devuelve por interfaz.
	Resultado_Chequeos pedir_materiales(std::string nombre, std::size_t &madera, std::size_t &piedra, std::size_t &metal);

	//PRE: -
	//POS: devuelve si se ingreso salir, si no existe el edificio, si se llego a la maxima cantidad
	//permitida del edificio, si no alcanzan los materiales o si no ocurre nada de lo anterior. en este
	//ultimo caso, edificio se iguala a edificio_ingresado
	Resultado_Chequeos chequeo_edificio(const std::string& edificio_ingresado);

	//PRE: -
	//POS: devuelve si se ingreso salir, si los valores no son numeros. Por interfaz devuelve los valores en sitze_t en caso de ser validos.
	Resultado_Chequeos chequeo_materiales(std::string nombre, std::string madera_ingresada, std::string piedra_ingresada, std::string metal_ingresada, std::size_t &piedra, std::size_t &madera, std::size_t &metal);

	//PRE: 
	//POS: Devuelve si se desea salir, si los valores son numeros, si se encuentran dentro del mapa. Si la coordenada es valida, lo devuelve por interfaz.
	// En caso contrario devuelve Coordenada(COORDENADA_VACIA,COORDENADA_VACIA).
	Resultado_Chequeos chequeo_coordenadas(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada);
	
	//PRE:
	//POS: devuelve si no alcanzan los materiales o si el edificio no necesita reparacion. En caso de que alcancen y el edificio lo necesite,
	//se repara el edificio y devuelve exito.
	Resultado_Chequeos chequeo_reparar_edificio(Jugador* jugador, Lista<Material> listado_necesario, Coordenada coordenada);

	//PRE:
	//POS: devuelve si se desea salir, si es numero el numero ingresado.
	Resultado_Chequeos chequeo_bombas(std::string bombas_ingresadas, std::size_t &bombas);

	//PRE: -
	//POS: se muestra un mensaje por terminal correspondiente al resultado del chequeo
	bool mostrar_mensaje_chequeo(Resultado_Chequeos chequeo);

	//PRE: edificio debe ser valido y fila y columna estar en el rango del mapa.
	//POS: se realizan las acciones al construir un edificio en la fila y columna.
	void edificio_construido_confirmado(const std::string &edificio, const Coordenada& coordenada, Jugador* jugador);

	//PRE: edificio debe ser valido y fila y columna estar en el rango del mapa.
	//POS: se realizan las acciones al demoler un edificio en la fila y columna.
	void edificio_demolido_confirmado(const std::string &edificio, const Coordenada& coordenada, Jugador* jugador);

	//PRE: jugador_invactivo != nullptr; coordenada valida
	//POS: Realiza el ataque al edificio que se encuentra en la coordenada.
	void bombardear_coordenadas(Coordenada coordenada, Jugador* jugador_inactivo);

	//PRE: -
	//POS: Devuelve en un string los materiales y sus ubicaciones en el mapa de forma estructurada para guardar en un archivo.
	std::string estado_actual_materiales_mapa();

	//PRE: jugador != nullptr;
	//POS: Devuelve en un string los edificios de jugador y sus ubicaciones en el mapa de forma estructurada para guardar en un archivo.
	std::string estado_actual_edificios_mapa(Jugador* jugador);
};

#endif /* EMPRESACONSTRUCTORA_H_ */
