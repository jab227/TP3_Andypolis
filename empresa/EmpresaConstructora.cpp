#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"

string const SALIR_STR = "salir", SI = "si", NO = "no";
const int COORDENADA_VACIA = -1;


Empresa_Constructora::Empresa_Constructora(string ruta_materiales, string ruta_edificios, string ruta_mapa, string ruta_ubicaiones){
	this -> almacen = new Almacen(ruta_materiales);
	this -> planos = new Planos(ruta_edificios);
	this -> mapa = new Mapa(ruta_mapa);
	this -> cargar_ubicaciones(ruta_ubicaiones);
}

Empresa_Constructora::~Empresa_Constructora() {
	delete this -> almacen;
	delete this -> planos;
	delete this -> mapa;
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

void Empresa_Constructora::mostrar_construidos(){
	this -> mapa -> mostrar_construidos();
}

void Empresa_Constructora::mostrar_coordenada(){
	std::size_t fila, columna;
	pedir_coordenadas(fila, columna);
	if(fila == EXITO){
		this -> mapa -> mostrar_posicion(fila, columna);
	}

}

void Empresa_Constructora::guardar_archivos(string ruta_materiales, string ruta_ubicaciones){
	this -> almacen -> guardar_materiales(ruta_materiales);
	this -> guardar_ubicaciones(ruta_ubicaciones);
}

void Empresa_Constructora::cargar_ubicaciones(string ruta){
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		std::size_t cant_agregados = 0, fila, columna;
		string nuevo_contenido;
		while(getline(archivo, lectura, ENTER)){
			nuevo_contenido = procesar_ubicacion(lectura, fila, columna);
			sumar_contenido(nuevo_contenido, fila, columna);
			cant_agregados++;
		}
	}
	archivo.close();
}

void Empresa_Constructora::guardar_ubicaciones(string ruta){
	ofstream archivo(ruta);
	string contenido;
	if (archivo.is_open()){
		int fila = 0, columna = 0;
		while(this -> mapa -> es_cordenada_valida(fila, columna)){
			while(this -> mapa -> es_cordenada_valida(fila, columna)){
				contenido = this -> mapa -> obtener_contenido_ubicacion(fila, columna);
				if(contenido != CONTENIDO_VACIO)
					archivo << contenido << " (" << fila << ", " << columna << ')' << std::endl;
				columna++;
			}
			columna = 0;
			fila++;
		}
	}
	archivo.close();
}

void Empresa_Constructora::sumar_contenido(string contenido, std::size_t fila, std::size_t columna){
	Edificio* edif = nullptr;
	//Deberia tener una capa mas de abstraccion. Mapa agregar_ubicacion()?
	if(this -> planos -> es_edificio_valido(contenido,edif)){
		this -> mapa -> construir_edificio_ubicacion(edif, fila, columna);
		this -> planos -> aumentar_construidos_edificio(edif);
		delete edif;
	}else
		this -> mapa -> poner_material_ubicacion(contenido, fila, columna);

}

void Empresa_Constructora::producir_recursos(){
	Lista<Material>* producidos = this -> planos -> obtener_recursos_producidos();
	this -> almacen -> sumar_lista_materiales(producidos);
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

void Empresa_Constructora::construir_edificio(){
	//Se rompe si pongo un numero.
	Edificio* edificio = pedir_edificio();
	if(edificio != nullptr){
		//mostrar_materiales_a_usar(planos, almacen, edificio);
		std::cout << "Desea realmente construir el edificio: " << edificio->obtener_nombre() << "? [si/no]" << std::endl;
		string respuesta = pedir_si_no();
		if(respuesta == SI){
			std::size_t fila, columna;
			Resultado_Chequeos resultado = this -> pedir_coordenadas(fila, columna);
			mostrar_mensaje_chequeo(resultado);
			if( resultado == EXITO )
				this -> edificio_construido_confirmado(edificio, fila, columna);

		}else
			std::cout << "No se realizo ningun cambio." << std::endl;
	delete edificio;
	}
}

//Adaptar a Edificio*
void Empresa_Constructora::demoler_edificio(){
	std::size_t fila, columna;
	Resultado_Chequeos resultado = NO_EXISTE;
	bool fin = false;
	do{
		resultado = this -> pedir_coordenadas(fila, columna);
		fin = mostrar_mensaje_chequeo(resultado);
	}while(!fin);
	this -> mapa -> demoler_edificio_ubicacion(fila, columna);
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

Resultado_Chequeos Empresa_Constructora::pedir_coordenadas(std::size_t& fila, std::size_t& columna){
	string fila_ingresada, columna_ingresada;
	
	std::cout << "Elegi las coordenadas del edificio que queres construir o salir" << std::endl << "Fila: ";
	getline(cin, fila_ingresada);
	std::cout << "Columna: ";
	getline(cin, columna_ingresada);
	
	fila = stoi(fila_ingresada);
	columna = stoi(columna_ingresada);
	
	return chequeo_coordenadas(fila_ingresada, columna_ingresada, fila, columna);
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
			//Es necesario?
			if(resultado != EXITO)
				edificio_ingresado == EDIFICIO_VACIO;
		}
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_coordenadas(string fila_ingresada, string columna_ingresada, std::size_t fila, std::size_t columna){
	Resultado_Chequeos resultado = EXITO;
	
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada))
		resultado = NO_EXISTE;
	else if(!(this -> mapa -> es_cordenada_valida(fila, columna)))
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

void Empresa_Constructora::edificio_construido_confirmado(Edificio* edificio, std::size_t fila, std::size_t columna){
	// Decirle al mapa que construya. Si es true, restamos.
	// ¿Si no decimos que la celda no es correcta?
	if(this -> mapa -> construir_edificio_ubicacion(edificio, fila, columna)){
		Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
		this -> almacen -> restar_lista_materiales(listado_necesario);
		delete listado_necesario;
		this -> planos -> aumentar_construidos_edificio(edificio);
	}
	
}
