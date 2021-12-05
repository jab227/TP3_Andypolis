#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"

string const SI = "si", NO = "no";
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

bool Empresa_Constructora::cargar_archivos(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaiones){
	this -> almacen = new Almacen(ruta_materiales);
	this -> planos = new Planos(ruta_edificios);
	this -> mapa = new Mapa(ruta_mapa);
	return this -> cargar_ubicaciones(ruta_ubicaiones);
}

void Empresa_Constructora::mostrar_materiales(){
	this -> almacen -> mostrar_materiales();
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

void Empresa_Constructora::mostrar_coordenada(){
	Coordenada coordenada = Coordenada(0,0);
	if(pedir_coordenadas(coordenada)){
		this -> mapa -> mostrar_posicion(coordenada);
	}

}

void Empresa_Constructora::guardar_archivos(string ruta_materiales, string ruta_ubicaciones){
	this -> almacen -> guardar_materiales(ruta_materiales);
	this -> guardar_ubicaciones(ruta_ubicaciones);
}

//TODO: Adaptar a coordenada.
bool Empresa_Constructora::cargar_ubicaciones(string ruta){
	bool existe = false;
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		std::size_t cant_agregados = 0;
		Coordenada coordenada = Coordenada(0,0);
		size_t propietario;

		string nuevo_contenido;
		while(getline(archivo, lectura, ENTER)){
			nuevo_contenido = procesar_ubicacion(lectura, coordenada, propietario);
			sumar_contenido(nuevo_contenido, coordenada, propietario);
			cant_agregados++;
			existe = true;
		}
	}
	archivo.close();
	return existe;
}

void Empresa_Constructora::guardar_ubicaciones(string ruta){
	ofstream archivo(ruta);
	string contenido;
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

void Empresa_Constructora::sumar_contenido(string contenido, Coordenada coordenada, std::size_t propietario){
	Edificio* edif = nullptr;
	if(this -> planos -> es_edificio_valido(contenido,edif)){
		this -> mapa -> construir_edificio_ubicacion(edif, coordenada);
		this -> planos -> aumentar_construidos_edificio(edif);
		delete edif;
	}else
		this -> mapa -> poner_material_ubicacion(contenido, coordenada);

}

void Empresa_Constructora::producir_recursos(){
	Lista<Material>* producidos = this -> planos -> obtener_recursos_producidos();
	//TODO: Constante
	this -> almacen -> sumar_lista_materiales(producidos,100);
	delete producidos;
}

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

void Empresa_Constructora::construir_edificio(Jugador* jugador){
	//Se rompe si pongo un numero.
	Edificio* edificio = pedir_edificio();
	if(edificio != nullptr){
		//mostrar_materiales_a_usar(planos, almacen, edificio);
		std::cout << "Desea realmente construir el edificio: " << edificio->obtener_nombre() << "? [si/no]" << std::endl;
		string respuesta = pedir_si_no();
		if(respuesta == SI){
			Coordenada coordenada = Coordenada(0,0);
			Resultado_Chequeos resultado = this -> pedir_coordenadas(coordenada);
			mostrar_mensaje_chequeo(resultado);
			if( resultado == EXITO )
				this -> edificio_construido_confirmado(edificio, coordenada, jugador);
		}else
			std::cout << "No se realizo ningun cambio." << std::endl;
	delete edificio;
	}
}

//TODO:
void Empresa_Constructora::demoler_edificio(Jugador* jugador){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = NO_EXISTE;
	bool fin = false;
	do{
		resultado = this -> pedir_coordenadas(coordenada);
		fin = mostrar_mensaje_chequeo(resultado);
	}while(!fin);
	//Tengo que avisar si se pudo destruir algo o no?
	this -> mapa -> demoler_edificio_ubicacion(coordenada);
	//TODO: Esto va a pasar al jugador. Recuperar materiales, eliminar coordenada
	//this -> almacen sumar_lista_materiales();
}

Edificio* Empresa_Constructora::pedir_edificio(){
	Edificio* edificio = nullptr;
	bool fin = false;
	string edificio_ingresado;
	Resultado_Chequeos chequeo;
	do{
		std::cout << "Elegi el edificio que queres construir o salir" << std::endl << "Edificio: ";
		getline(cin, edificio_ingresado);
		chequeo = chequeo_construir(edificio_ingresado, edificio);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return edificio;
}

//TODO: Constructo de copia?? Asi no tenemos que pasarle una coordenada creada.
Resultado_Chequeos Empresa_Constructora::pedir_coordenadas(Coordenada& coordenada){
	string fila_ingresada, columna_ingresada;
	
	std::cout << "Elegi las coordenadas del edificio que queres construir o salir" << std::endl << "Fila: ";
	getline(cin, fila_ingresada);
	std::cout << "Columna: ";
	getline(cin, columna_ingresada);
	
	coordenada = Coordenada(stoi(fila_ingresada),stoi(columna_ingresada));
	
	return chequeo_coordenadas(fila_ingresada, columna_ingresada, coordenada);
}

Resultado_Chequeos Empresa_Constructora::chequeo_construir(string& edificio_ingresado, Edificio* &edificio){
	Resultado_Chequeos resultado = EXITO;
	if(edificio_ingresado == SALIR_STR)
		resultado = SALIR;
	else{
		resultado = planos -> check_construir_edificio(edificio_ingresado, edificio);
		if(resultado == EXITO){
			Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
			resultado = almacen -> hay_lista_materiales(listado_necesario);
			delete listado_necesario;
			//WHY: Es necesario?
			if(resultado != EXITO)
				edificio_ingresado == EDIFICIO_VACIO;
		}
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_coordenadas(string fila_ingresada, string columna_ingresada, Coordenada coordenada){
	Resultado_Chequeos resultado = EXITO;
	
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada))
		resultado = NO_EXISTE;
	else if(!(this -> mapa -> es_cordenada_valida(coordenada)))
		resultado = FUERA_RANGO;

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
			//mostrar_materiales_insuficientes(edificio);
			break;
		case FUERA_RANGO:
			std::cout <<  "La ubicacion ingresada excede el rango del mapa." << std::endl;
			break;
		case SALIR:
			std::cout << "No se realizo ninguna accion." << std::endl;
			fin = true;
			break;
		default:
			break;
		}
	return fin;
}

string Empresa_Constructora::pedir_si_no(){
	string respuesta;
	std::cout << "Respuesta:   ";
	getline(cin, respuesta);
	while(respuesta != SI && respuesta != NO){
		std::cout << "La respuesta no es valida, solo se acepta si o no." << std::endl;
		std::cout << "Respuesta:   ";
		getline(cin, respuesta);
	}
	return respuesta;
}

void Empresa_Constructora::edificio_construido_confirmado(Edificio* edificio,const Coordenada& coordenada, Jugador* jugador){
	// Decirle al mapa que construya. Si es true, restamos.
	// ¿Si no decimos que la celda no es correcta?
	if(this -> mapa -> construir_edificio_ubicacion(edificio, coordenada)){
		Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
		//TODO: Constante
		this -> almacen -> descontar_lista_materiales(listado_necesario,100);
		delete listado_necesario;
		//TODO: Ya no es lo mismo donde aumentamos, cada uno tiene su contador de edificios.
		this -> planos -> aumentar_construidos_edificio(edificio);
		jugador -> usar_energia(-ENERGIA_CONSTRUIR);
	}
	
}
