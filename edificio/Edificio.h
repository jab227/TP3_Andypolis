#ifndef EDIFICIO_H_
#define EDIFICIO_H_

#include "../material/Material.h"


const int CANT_MATERIALES_EDIFICIOS = 3;
const int PIEDRA = 0, MADERA = 1, METAL = 2;
const string MATERTIALES_EDIFICIOS[] = {"piedra", "madera", "metal"};
const string EDIFICIO_VACIO = "";
enum Resultado_Chequeos {EXITO, NO_EXISTE, MAXIMA_CANTIDAD, NO_MATERIALES, FUERA_RANGO,
	CASILLERO_NO_CONSTRUIBLE, CASILLERO_NO_TRANSITABLE, CASILLERO_OCUPADO, CASILLERO_LIBRE, SALIR};


class Edificio {
//Atrubitos
private:
	string nombre;
	int materiales[CANT_MATERIALES_EDIFICIOS];
	int maximo_permitidos;
	int construidos;
//Metodos:
public:
	//PRE: -
	//POST: crea un edificio con los nombre vacio y datos en 0.
	Edificio();

	//PRE: -
	//POST: crea un edificio con los atributos inicializados.
	Edificio(string nombre, int piedra, int madera, int metal, int maximo_permitidos);

	//PRE: -
	//POST: ejecuta el destructor
	virtual ~Edificio() = 0;

	//PRE: -
	//POST: devuelve el nombre del edificio.
	string obtener_nombre();

	//PRE: -
	//POST: devuelve la cantidad del material ingresado requerido para construirlo. En caso de que
	//no se requiera ese material, deuelve 0.
	int obtener_cant_material(string material);

	//PRE: -
	//PORT: devuleve la cantidad de edificios maximos construidos.
	int obtener_max_permitidos();

	//PRE: -
	//POST: imprime un mensaje por consola
	virtual void saludar() = 0;

	//PRE: -
	//POST: devuelve si el edificio es vacio
	bool vacio();

	//PRE -
	//POST: devuelve el material producido por el edficio en caso de que sea un productor. Devuelve un
	//material vacio en caso contratrio.
	virtual Material producir_material() = 0;

	//PRE -
	//POST: devuelve lo que produce en str.
	virtual string info_producto() = 0;

	//PRE: 0 <= n
	//POST: se modifica el valor de edificios construidos a n
	void modificar_construidos(int n);

	//PRE: -
	//POST: devuelve la cantidad de edificios construidos
	int obtener_construidos();

};

#endif /* EDIFICIO_H_ */
