#ifndef EDIFICIO_H_
#define EDIFICIO_H_

#include "../material/Material.h"

const std::size_t CANT_MATERIALES_EDIFICIOS = 3, NINGUNO = 0;
const std::size_t PIEDRA = 0, MADERA = 1, METAL = 2, ANDYCOINS = 3, BOMBAS = 4;
const std::string MATERIALES_EDIFICIOS[] = {"piedra", "madera", "metal"};
const std::string EDIFICIO_VACIO = "";
enum Resultado_Chequeos { 
	EXITO, 
	NO_EXISTE, 
	MAXIMA_CANTIDAD, 
	NO_MATERIALES, 
	FUERA_RANGO,
	CASILLERO_NO_CONSTRUIBLE, 
	CASILLERO_NO_TRANSITABLE, 
	CASILLERO_OCUPADO, 
	CASILLERO_LIBRE,
	SALIR, 
	NO_REPARABLE, 
	REPARABLE, 
	DESTRUIDO, 
	NO_ENERGIA, 
	OBELISCO, 
	NO_PERTENECE, 
	NO_PERTENECE_OPONENTE, 
	CASILLERO_OCUPADO_JUGADOR
};


class Edificio {
//Atributos
private:
	std::string nombre;
	std::size_t vida;
	std::size_t materiales[CANT_MATERIALES_EDIFICIOS];
	std::size_t maximo_permitidos;
//Metodos:
public:
	//PRE: -
	//POST: crea un edificio con los nombre vacio y datos en 0.
	Edificio();

	//PRE: -
	//POST: crea un edificio con los atributos inicializados.
	Edificio(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos);
	Edificio(std::string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t vida);

	// PRE: -
	// POST: Sobreescribiendo el operador igual.
	Edificio& operator=(const Edificio& rhs);

	// PRE: -
	// POST: ejecuta el destructor
	virtual ~Edificio();

	// PRE: -
	// POST: devuelve el nombre del edificio.
	std::string obtener_nombre() const;

	//PRE: -
	//POST: devuelve la cantidad del material ingresado requerido para construirlo. En caso de que
	//no se requiera ese material, devuelve 0.
	std::size_t obtener_cant_material(std::string material) const;

	//PRE: -
	//POST: devuelve la vida del edificio.
	std::size_t obtener_vida() const;

	//PRE: -
	//POST: devuleve la cantidad de edificios maximos construidos.
	std::size_t obtener_max_permitidos() const;

	// PRE: -
	// POST: imprime un mensaje por consola
	virtual void saludar() = 0;

	// PRE: -
	// POST: devuelve si el edificio es vacio
	bool vacio();

	//PRE: -
	//POST: devuelve true si los construidos es igual o mayor a los permitidos.
	Resultado_Chequeos esta_maxima_capacidad(const std::size_t &construidos);
	
	//PRE -
	//POST: devuelve el material producido por el edficio en caso de que sea un productor. Devuelve un
	//material vacio en caso contratrio.
	virtual Material producir_material() = 0;

	//PRE -
	//POST: devuelve lo que produce en str.
	virtual std::string info_producto() const = 0;

	//PRE: -
	//POST: Devuelve true si el nombre es el mimso.
	bool operator==(const Edificio &rhs);
	
	//PRE: -
	//POST: Devuelve true si el nombre es el mimso.
	bool operator!=(const Edificio &rhs);

	//TODO: Hacer a_string() que devuelva la info para guardar.
	std::string a_string();
	
	//PRE: -
	//POST: Devuelve NO_REPARABLE si la vida est?? al m??ximo. Devuelve REPARABLE si 0 < vida < MAX_VIDA.
	//se puede elegir si reparar o no el edificio con true o false, por defecto los edificios se reparan
	virtual Resultado_Chequeos reparar(bool reparar_edificio = true) = 0;

	//PRE: -
	//POST: Resta 1 de vida al edificio. Devuelve DESTRUIDO si el edificio tiene 0 de vida. Devuelve REPARABLE si a??n tiene.
	Resultado_Chequeos disminuir_vida();

protected: // Solo me interesa que puedan cambiarlo las hijas si lo necesitan.
	//PRE: -
	//POST: Suma 1 de vida al edificio.
	void recuperar_vida();
};

#endif /* EDIFICIO_H_ */
