#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"

std::string const SI = "si", NO = "no";
const int COORDENADA_VACIA = -1, BOMBAS_VACIAS = -1, COSTO_BOMBAS = 100;


Empresa_Constructora::Empresa_Constructora(){
	this -> almacen = nullptr;
	this -> planos = nullptr;
	this -> mapa = nullptr;
}

Empresa_Constructora::~Empresa_Constructora() {
	if(almacen != nullptr)
		delete this -> almacen;
	if(planos != nullptr)
		delete this -> planos;
	if(mapa != nullptr)
		delete this -> mapa;
}

bool Empresa_Constructora::cargar_archivos(std::string ruta_materiales, std::string ruta_edificios, std::string ruta_mapa, std::string ruta_ubicaiones){
	this -> almacen = new Almacen(ruta_materiales);
	this -> planos = new Planos(ruta_edificios);
	this -> mapa = new Mapa(ruta_mapa);
	//TODO: Reemplazable con el ParserUbicacion
	//Para que no tire error. 
	//return this -> cargar_ubicaciones(ruta_ubicaiones);
	return false;
}

void Empresa_Constructora::mostrar_materiales(Jugador* jugador){
	jugador -> mostrar_inventario();
}

void Empresa_Constructora::mostrar_edificios(){
	this -> planos -> mostrar_edificios();
}

void Empresa_Constructora::mostrar_mapa(){
	this -> mapa -> mostrar_mapa();
}

void Empresa_Constructora::mostrar_construidos(Jugador* jugador){
	jugador -> mostrar_construidos(this -> mapa);
}

void Empresa_Constructora::consultar_coordenada(){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = pedir_coordenadas(coordenada);
	if(resultado == EXITO) this -> mapa -> saludar_coordenada(coordenada);
	mostrar_mensaje_chequeo(resultado);
}

void Empresa_Constructora::guardar_archivos(std::string ruta_materiales, std::string ruta_ubicaciones){
	this -> almacen -> guardar_materiales(ruta_materiales);
	this -> guardar_ubicaciones(ruta_ubicaciones);
}

//TODO: Reemplazable con el ParserUbicacion
bool Empresa_Constructora::cargar_ubicaciones(std::string ruta, Jugador* jugador){
	bool existe = false;
	ifstream archivo(ruta);
	if (archivo.is_open()){
		std::string lectura;
		std::size_t cant_agregados = 0;
		Coordenada coordenada = Coordenada(0,0);
		
		std::string nuevo_contenido;
		while(getline(archivo, lectura, ENTER)){
			nuevo_contenido = procesar_ubicacion(lectura, coordenada);
			sumar_contenido(nuevo_contenido, coordenada, jugador);
			cant_agregados++;
			existe = true;
		}
	}
	archivo.close();
	return existe;
}

void Empresa_Constructora::guardar_ubicaciones(std::string ruta){
	ofstream archivo(ruta);
	std::string contenido;
	if (archivo.is_open()){
		std::size_t fila = 0, columna = 0;
		Coordenada coordenada = Coordenada(fila,columna);
		while(this -> mapa -> es_cordenada_valida(coordenada)){
			while(this -> mapa -> es_cordenada_valida(coordenada)){
				contenido = this -> mapa -> obtener_contenido_ubicacion(coordenada);
				if(contenido != CONTENIDO_VACIO)
					archivo << contenido << " (" << fila << ", " << columna << ')' << std::endl;
				coordenada = Coordenada(fila, ++columna);
			}
			coordenada = Coordenada(++fila, 0);
		}
	}
	archivo.close();
}

//TODO: Reemplazable con el ParserUbicacion
void Empresa_Constructora::sumar_contenido(std::string contenido, Coordenada coordenada, Jugador* jugador){
	if(Planos::existe(contenido)){
		this -> mapa -> construir_edificio_ubicacion(contenido, coordenada);
		Coordenada* ptr_coordenada = new Coordenada(coordenada);
		jugador -> agregar_ubicacion(ptr_coordenada);
	}else
		this -> mapa -> poner_material_ubicacion(contenido, coordenada);

}

void Empresa_Constructora::recolectar_recursos(Jugador * jugador){
	//TODO: Chequear que tenga construidos.
	jugador -> recolectar(this -> mapa);
	jugador -> usar_energia(ENERGIA_RECOLECTAR);
	jugador -> mostrar_inventario();
}

//TODO: Adaptar a las bolsitas de recursos.
void Empresa_Constructora::lluvia_de_recursos(){
	if(!this -> mapa -> generar_materiales_aleatorios())
		std::cout << "Materiales generados por el mapa!" << std::endl;
	else
		std::cout << "No hay espacio disponible para generar materiales. Eliminalos antes." << std::endl;
}

void Empresa_Constructora::vaciar_materiales(){
	this -> mapa -> vaciar_materiales();
	std::cout << "Mapa limpiado de materiales!" << std::endl;
}

void Empresa_Constructora::construir_edificio( Jugador* jugador){
	std::string edificio = pedir_edificio(jugador);
	if(edificio != EDIFICIO_VACIO){
		std::cout << "Desea realmente construir el edificio: " << edificio << "? [si/no]" << std::endl;
		std::string respuesta = pedir_si_no();
		if(respuesta == SI){
			Coordenada coordenada = Coordenada(0,0);
			Resultado_Chequeos resultado = this -> pedir_coordenadas(coordenada);
			mostrar_mensaje_chequeo(resultado);
			if( resultado == EXITO )
				this -> edificio_construido_confirmado(edificio, coordenada, jugador);
		}else
			std::cout << "No se realizó ningún cambio." << std::endl;
	}
}

//TODO: Embellecer
void Empresa_Constructora::demoler_edificio(Jugador* jugador){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = NO_EXISTE;
	do resultado = this -> pedir_coordenadas(coordenada);
	while(!mostrar_mensaje_chequeo(resultado));
	std::size_t indice = jugador -> existe_ubicacion(coordenada);
	if(indice){ //Chequeo que le pertenece.
		std::string nombre_edificio = EDIFICIO_VACIO;
		resultado = this -> mapa -> demoler_edificio_ubicacion(nombre_edificio, coordenada);
		if(resultado == EXITO){
			//demoler_edificio_confirmado()
			Edificio* edificio = Planos::buscar(nombre_edificio);
			Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
			jugador -> recuperar_lista_materiales(listado_necesario);
			jugador -> eliminar_ubicacion(coordenada);
			jugador -> usar_energia(ENERGIA_DEMOLER);
			delete listado_necesario;
		}
	} 
	mostrar_mensaje_chequeo( resultado );
}

std::string Empresa_Constructora::pedir_edificio( Jugador* jugador){
	bool fin = false;
	std::string edificio_ingresado;
	Resultado_Chequeos chequeo;
	do{
		std::cout << "Elegi el edificio que queres construir o salir" << std::endl << "Edificio: ";
		getline(cin, edificio_ingresado);
		chequeo = chequeo_construir(edificio_ingresado, jugador);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return edificio_ingresado;
}

//TODO: Constructo de copia?? Asi no tenemos que pasarle una coordenada creada.
Resultado_Chequeos Empresa_Constructora::pedir_coordenadas(Coordenada& coordenada){
	std::string fila_ingresada, columna_ingresada;
	
	std::cout << "Elegi las coordenadas del edificio que queres construir o salir" << std::endl << "Fila: ";
	getline(cin, fila_ingresada);
	std::cout << "Columna: ";
	getline(cin, columna_ingresada);
	
	coordenada = Coordenada(stoi(fila_ingresada),stoi(columna_ingresada));
	
	return chequeo_coordenadas(fila_ingresada, columna_ingresada, coordenada);
}

Resultado_Chequeos Empresa_Constructora::chequeo_construir(const std::string& edificio_ingresado, Jugador* jugador){
	Resultado_Chequeos resultado = EXITO;

	if(edificio_ingresado == SALIR_STR) resultado = SALIR;
	else if(es_numero(edificio_ingresado)) resultado = NO_EXISTE;
	else resultado = planos -> permitido_construir(edificio_ingresado, jugador, this -> mapa);

	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_coordenadas(std::string fila_ingresada, std::string columna_ingresada, Coordenada coordenada){
	Resultado_Chequeos resultado = EXITO;
	
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR) resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada)) resultado = NO_EXISTE;
	else if(!(this -> mapa -> es_cordenada_valida(coordenada))) resultado = FUERA_RANGO;

	return resultado;
}

bool Empresa_Constructora::mostrar_mensaje_chequeo(Resultado_Chequeos chequeo){
	bool fin = false;
	switch(chequeo){
		case EXITO:
			fin = true;
			break;
		case NO_EXISTE:
			std::cout << "La/s opcion/es ingresada/s no es/son valida/s." << std::endl;
			break;
		case MAXIMA_CANTIDAD:
			std::cout <<  "Hay la cantidad maxima permitida construida de este edificio." << std::endl;
			break;
		case NO_MATERIALES:
			std::cout << "No hay suficientes materiales." << std::endl;
			//TODO: mostrar_materiales_insuficientes(edificio);
			break;
		case FUERA_RANGO:
			std::cout <<  "La ubicacion ingresada excede el rango del mapa." << std::endl;
			break;
		case SALIR:
			std::cout << "No se realizo ninguna accion." << std::endl;
			fin = true;
			break;
		case CASILLERO_NO_CONSTRUIBLE:
			cout <<  "La ubicacion ingresada no es construible." << endl;
			break;
		case CASILLERO_OCUPADO:
			cout <<  "Esta ubicacion esta ocupada por otro edificio." << endl;
			break;
		case NO_REPARABLE:
			cout <<  "El edificio no necesita reparación." << endl;
			break;
		default:
			break;
		}
	return fin;
}

std::string Empresa_Constructora::pedir_si_no(){
	std::string respuesta;
	std::cout << "Respuesta:   ";
	getline(cin, respuesta);
	while(respuesta != SI && respuesta != NO){
		std::cout << "La respuesta no es valida, solo se acepta si o no." << std::endl;
		std::cout << "Respuesta:   ";
		getline(cin, respuesta);
	}
	return respuesta;
}

void Empresa_Constructora::edificio_construido_confirmado(const std::string &nombre_edificio,const Coordenada& coordenada, Jugador* jugador){
	Resultado_Chequeos resultado = this -> mapa -> construir_edificio_ubicacion(nombre_edificio, coordenada);
	if(mostrar_mensaje_chequeo(resultado)){
		Edificio* edificio = Planos::buscar(nombre_edificio);
		Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
		jugador -> usar_lista_materiales(listado_necesario);
		delete listado_necesario;
		jugador -> usar_energia(ENERGIA_CONSTRUIR);
		Coordenada* ptr_coordenada = new Coordenada(coordenada);
		jugador -> agregar_ubicacion(ptr_coordenada);
	}
}


void Empresa_Constructora::reparar_edificio(Jugador* jugador){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = NO_EXISTE;
	do resultado = this -> pedir_coordenadas(coordenada);
	while(!mostrar_mensaje_chequeo(resultado));
	std::size_t indice = jugador -> existe_ubicacion(coordenada);
	if(indice){ //Chequeo que le pertenece.
		std::string nombre_edificio = EDIFICIO_VACIO;
		resultado = this -> mapa -> reparar_edificio_ubicacion(nombre_edificio, coordenada);
		if(resultado == EXITO){
			//reparar_edificio_confirmado()
			Edificio* edificio = Planos::buscar(nombre_edificio);
			Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
			jugador -> cobrar_reparacion(listado_necesario);
			jugador -> usar_energia(ENERGIA_REPARAR);
			delete listado_necesario;
		}
	} 
	mostrar_mensaje_chequeo( resultado );
}



void Empresa_Constructora::comprar_bombas(Jugador* jugador){
	std::size_t cantidad_bombas = 0;
	mostrar_mensaje_chequeo(pedir_bombas(cantidad_bombas));
	if(mostrar_mensaje_chequeo(jugador -> obtener_inventario() -> comprar_bombas(cantidad_bombas))){
		jugador -> usar_energia(ENERGIA_COMPRAR_BOMBAS);
	}
}

Resultado_Chequeos Empresa_Constructora::pedir_bombas(std::size_t& bombas){
	std::string cantidad_ingresada;
	std::cout << "¿Cuantas bombas desea comprar? (Precio: " << COSTO_BOMBAS << " andycoins): ";
	getline(cin, cantidad_ingresada);
	
	return chequeo_bombas(cantidad_ingresada, bombas);
}

Resultado_Chequeos Empresa_Constructora::chequeo_bombas(std::string bombas_ingresadas, std::size_t &bombas){
	Resultado_Chequeos resultado = EXITO;
	if(bombas_ingresadas == SALIR_STR) resultado = SALIR;
	else if(!es_numero(bombas_ingresadas)) resultado = NO_EXISTE;
	else bombas = stoul(bombas_ingresadas);
	return resultado;
}
