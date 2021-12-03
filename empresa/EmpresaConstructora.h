#ifndef EMPRESACONSTRUCTORA_H_
#define EMPRESACONSTRUCTORA_H_

#include "Almacen.h"
#include "Planos.h"
#include "../utils/Lista.h"
#include "Mapa.h"

class Empresa_Constructora {
//Atributos
private:
	Almacen* almacen;
	Planos* planos;
	Mapa* mapa;
//Metodos
public:
	//PRE: las rutas deben ser validas a archivos existentes.
	//POST: se inicializan los atributos con las rutas ingresadas.
	Empresa_Constructora(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaiones);

	//PRE: -
	//POST: se libera la memoria utilizada
	~Empresa_Constructora();

	//PRE: -
	//POST: se construye un edificio pidiendo al usuario en nombre y las coordenadas
	void construir_edificio();

	//PRE: -
	//POST: se destruye un edificio pidiendo al usuario las cordenadas
	void demoler_edificio();

	//PRE: -
	//POST: se muestran los edificios existentes junto con sus materiales requeridos para
	//construirlo, la cantidad construida y los que se pueden construir
	void mostrar_edificios();

	//PRE: -
	//POST: se muestran los materiales disponibles en el stock del almacen
	void mostrar_materiales();

	//PRE: -
	//POST: se muestra el mapa de terrenos y el de los edificios/materiales ubicados en mapa
	void mostrar_mapa();

	//PRE: -
	//POST: se pide al usuario una coordenada y se muestra informacion sobre lo que hay en ella
	void mostrar_coordenada();

	//PRE: -
	//POST: se muestran los edificios que hay construidos junto con sus coordenadas
	void mostrar_construidos();

	//PRE: -
	//POST: se guardan los datos de los archivos de materiales y las ubicaciones
	void guardar_archivos(string ruta_materiales, string ruta_ubicaciones);

	//PRE: -
	//POST: se suman al almacen los recursos producidos por los edificios
	void producir_recursos();

	//PRE: -
	//POST: se generan materiales aleatorios en caminos aleatorios del mapa
	void lluvia_de_recursos();

	//PRE: -
	//POST: se vacian los materiales del mapa
	void vaciar_materiales();
private:
	//PRE: ruta debe ser la ruta a un archivo existente y bien formado. el mapa debe estar cargado.
	//POST: se cargan las ubicaciones en el mapa.
	void cargar_ubicaciones(string ruta);

	//PRE: ruta debe ser la ruta a un archivo existente. el mapa debe estar cargado.
	//POST: se guardan la informacion de las ubicaciones en el archivo.
	void guardar_ubicaciones(string ruta);

	//PRE: la linea debe estar bien formada con la ubicacion de un edificio o material. fila y columna
	//debe ser valido en el mapa
	//POST: se carga el contenido de la ubicacion en el mapa, sea material o edificio.
	void sumar_contenido(string linea, std::size_t fila, std::size_t columna);

	//PRE: -
	//POST: se pide un edificio valido al usuario y devuelve true. de no obtener un edificio valido
	//devuelve false
	Edificio* pedir_edificio();

	//PRE: -
	//POST: devuelve si se ingreso salir, si no existe el edificio, si se llego a la maxima cantidad
	//permitida del edificio, si no alcanzan los materiales o si no ocurre nada de lo anterior. en este
	//ultimo caso, edificio se iguala a edificio_ingresado
	Resultado_Chequeos chequeo_construir(string& edificio_ingresado, Edificio* &edificio);

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
	void edificio_construido_confirmado(Edificio* edificio, std::size_t fila, std::size_t columna);

	//PRE: -
	//POST: Pide la fila y la columna. Lo devuelve por coordenada.
	Resultado_Chequeos pedir_coordenadas(std::size_t& fila, std::size_t& columna);

	Resultado_Chequeos chequeo_coordenadas(string fila_ingresada, string columna_ingresada, std::size_t fila, std::size_t columna);
};

#endif /* EMPRESACONSTRUCTORA_H_ */
