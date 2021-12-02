#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"

string const SALIR_STR = "salir", SI = "si", NO = "no";
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

void Empresa_Constructora::mostrar_construidos(size_t jugador){
	this -> mapa -> mostrar_construidos(jugador);
}

void Empresa_Constructora::mostrar_coordenada(){
	int fila, columna;
	pedir_posicion(fila, columna);
	if(fila != COORDENADA_VACIA){
		this -> mapa -> mostrar_posicion(fila, columna);
	}

}

void Empresa_Constructora::guardar_archivos(string ruta_materiales, string ruta_ubicaciones){
	this -> almacen -> guardar_materiales(ruta_materiales);
	this -> guardar_ubicaciones(ruta_ubicaciones);
}

bool Empresa_Constructora::cargar_ubicaciones(string ruta){
	bool existe = false;
	ifstream archivo(ruta);
	if (archivo.is_open()){
		string lectura;
		int cant_agregados = 0, fila, columna;
		size_t propietario;
		string nuevo_contenido;
		while(getline(archivo, lectura, ENTER)){
			nuevo_contenido = procesar_ubicacion(lectura, fila, columna, propietario);
			sumar_contenido(nuevo_contenido, fila, columna, propietario);
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
		int fila = 0, columna = 0;
		while(this -> mapa -> es_cordenada_valida(fila, columna)){
			while(this -> mapa -> es_cordenada_valida(fila, columna)){
				contenido = this -> mapa -> obtener_contenido_ubicacion(fila, columna);
				if(contenido != CONTENIDO_VACIO)
					archivo << contenido << " (" << fila << ", " << columna << ')' << endl;
				columna++;
			}
			columna = 0;
			fila++;
		}
	}
	archivo.close();
}

void Empresa_Constructora::sumar_contenido(string contenido, int fila, int columna, size_t propietario){
	if(this -> planos -> es_edificio_valido(contenido)){
		this -> mapa -> construir_edificio_ubicacion(contenido, fila, columna, propietario);
		this -> planos -> aumentar_construidos_edificio(contenido);
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
		cout << "Materiales generados por el mapa!" << endl;
	else
		cout << "No hay espacio disponible para generar materiales. Eliminalos antes." << endl;
}

void Empresa_Constructora::vaciar_materiales(){
	this -> mapa -> vaciar_materiales();
	cout << "Mapa limpiado de materiales!" << endl;
}

void Empresa_Constructora::construir_edificio(Jugador* jugador){
	string edificio = pedir_edificio();

	if(edificio != EDIFICIO_VACIO){
		//mostrar_materiales_a_usar(planos, almacen, edificio);
		cout << "Desea realmente construir el edificio: " << edificio << "? [si/no]" << endl;
		string respuesta = pedir_si_no();
		if(respuesta == SI){
			int fila, columna;
			if(this -> pedir_posicion_libre(fila, columna)){
				this -> edificio_construido_confirmado(edificio, fila, columna, jugador);
				cout << "Edificio construido exitosamente!" << endl;
			}
		}else
			cout << "No se realizo ningun cambio." << endl;
	}
}

void Empresa_Constructora::demoler_edificio(){
	int fila, columna;
	string edificio = pedir_posicion_ocupada(fila, columna);

	if(edificio != EDIFICIO_VACIO){
		//mostrar_materiales_a_obtener(planos, almacen, edificio);
		cout << "Desea realmente demoler el edificio: " << edificio << " ubicado en fila: " << fila
			 << " y columna: " << columna << "? [si/no]" << endl;
		string respuesta = pedir_si_no();
		if(respuesta == SI){
			Lista<Material>* listado_recuperado = planos -> materiales_necesarios(edificio);
			this -> almacen -> sumar_lista_materiales(listado_recuperado, true);
			delete listado_recuperado;
			this -> planos -> disminuir_construidos_edificio(edificio);
			this -> mapa -> demoler_edificio_ubicacion(fila, columna);
			cout << "Edificio demolido exitosamente!" << endl;
		}
		else
			cout << "No se realizo ningun cambio." << endl;
	}
}

string Empresa_Constructora::pedir_edificio(){
	string edificio = EDIFICIO_VACIO;
	bool fin = false;
	string edificio_ingresado;
	Resultado_Chequeos chequeo;
	do{
		cout << "Elegi el edificio que queres construir o salir" << endl << "Edificio: ";
		getline(cin, edificio_ingresado);
		chequeo = chequeo_construir(edificio_ingresado, edificio);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return edificio;
}

bool Empresa_Constructora::pedir_posicion_libre(int &fila, int &columna){
	fila = COORDENADA_VACIA;
	columna = COORDENADA_VACIA;
	bool fin = false;
	string fila_ingresada, columna_ingresada;
	Resultado_Chequeos chequeo;
	do{
		cout << "Elegi las coordenadas del edificio que queres construir o salir" << endl << "Fila: ";
		getline(cin, fila_ingresada);
		cout << "Columna: ";
		getline(cin, columna_ingresada);
		chequeo = chequeo_posicion_libre(fila_ingresada, columna_ingresada, fila, columna);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return chequeo == EXITO;

}

string Empresa_Constructora::pedir_posicion_ocupada(int &fila, int &columna){
	fila = COORDENADA_VACIA;
	columna = COORDENADA_VACIA;
	string edificio = EDIFICIO_VACIO;
	bool fin = false;
	string fila_ingresada, columna_ingresada;
	Resultado_Chequeos chequeo;
	do{
		cout << "Elegi las coordenadas del edificio que queres demoler o salir" << endl << "Fila: ";
		getline(cin, fila_ingresada);
		cout << "Columna: ";
		getline(cin, columna_ingresada);
		chequeo = chequeo_demoler(fila_ingresada, columna_ingresada, fila, columna, edificio);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return edificio;

}

void Empresa_Constructora::pedir_posicion(int &fila, int &columna){
	fila = COORDENADA_VACIA;
	columna = COORDENADA_VACIA;
	bool fin = false;
	string fila_ingresada, columna_ingresada;
	Resultado_Chequeos chequeo;
	do{
		cout << "Elegi las coordenadas que queres consultar o salir" << endl << "Fila: ";
		getline(cin, fila_ingresada);
		cout << "Columna: ";
		getline(cin, columna_ingresada);
		chequeo = chequeo_posicion(fila_ingresada, columna_ingresada, fila, columna);
		fin = mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
}

Resultado_Chequeos Empresa_Constructora::chequeo_construir(string edificio_ingresado, string &edificio){
	Resultado_Chequeos resultado = EXITO;
	if(edificio_ingresado == SALIR_STR)
		resultado = SALIR;
	else{
		resultado = planos -> check_construir_edificio(edificio_ingresado);
		if(resultado == EXITO){
			Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio_ingresado);
			resultado = almacen -> hay_lista_materiales(listado_necesario);
			delete listado_necesario;
			if(resultado == EXITO)
				edificio = edificio_ingresado;
		}
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_demoler(string fila_ingresada, string columna_ingresada, int &fila, int &columna, string &edificio){
	Resultado_Chequeos resultado = EXITO;
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada))
		resultado = NO_EXISTE;
	else{
		resultado = this -> mapa -> chequeo_demoler_edificio(stoi(fila_ingresada), stoi(columna_ingresada), edificio);
		if(resultado == EXITO){
			fila = stoi(fila_ingresada);
			columna = stoi(columna_ingresada);
		}
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_posicion_libre(string fila_ingresada, string columna_ingresada, int &fila, int &columna){
	Resultado_Chequeos resultado = EXITO;
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada))
		resultado = NO_EXISTE;
	else{
		resultado = this -> mapa -> chequeo_ubicar_edificio(stoi(fila_ingresada), stoi(columna_ingresada));
		if(resultado == EXITO){
			fila = stoi(fila_ingresada);
			columna = stoi(columna_ingresada);
		}
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_posicion(string fila_ingresada, string columna_ingresada, int &fila, int &columna){
	Resultado_Chequeos resultado = EXITO;
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada))
		resultado = NO_EXISTE;
	else if(!this -> mapa -> es_cordenada_valida(stoi(fila_ingresada), stoi(columna_ingresada)))
		resultado = FUERA_RANGO;
	else{
		fila = stoi(fila_ingresada);
		columna = stoi(columna_ingresada);
	}
	return resultado;
}

bool Empresa_Constructora::mostrar_mensaje_chequeo(Resultado_Chequeos chequeo){
	bool fin = false;
	switch(chequeo){
		case EXITO:
			fin = true;
			break;
		case NO_EXISTE:
			cout << "La/s opcion/es ingresada/s no es/son valida/s." << endl;
			break;
		case MAXIMA_CANTIDAD:
			cout <<  "Hay la cantidad maxima permitida construida de este edificio." << endl;
			break;
		case NO_MATERIALES:
			cout << "No hay suficientes materiales." << endl;
			//mostrar_materiales_insuficientes(edificio);
			break;
		case FUERA_RANGO:
			cout <<  "La ubicacion ingresada excede el rango del mapa." << endl;
			break;
		case CASILLERO_NO_CONSTRUIBLE:
			cout <<  "La ubicacion ingresada no es construible." << endl;
			break;
		case CASILLERO_OCUPADO:
			cout <<  "Esta ubicacion esta ocupada por otro edificio." << endl;
			break;
		case CASILLERO_LIBRE:
			cout <<  "En esta ubicacion no hay ningun edificio." << endl;
			break;
		case SALIR:
			cout << "No se realizo ninguna accion." << endl;
			fin = true;
			break;
		default:
			break;
		}
	return fin;
}

string Empresa_Constructora::pedir_si_no(){
	string respuesta;
	cout << "Respuesta:   ";
	getline(cin, respuesta);
	while(respuesta != SI && respuesta != NO){
		cout << "La respuesta no es valida, solo se acepta si o no." << endl;
		cout << "Respuesta:   ";
		getline(cin, respuesta);
	}
	return respuesta;
}

void Empresa_Constructora::edificio_construido_confirmado(string edificio, int fila, int columna, Jugador* jugador){
	Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
	this -> almacen -> restar_lista_materiales(listado_necesario);
	delete listado_necesario;
	this -> planos -> aumentar_construidos_edificio(edificio);
	this -> mapa -> construir_edificio_ubicacion(edificio, fila, columna, jugador -> obtener_jugador());
	jugador -> modificar_energia(-ENERGIA_CONSTRUIR);
}

void Empresa_Constructora::comprar_bombas(Jugador* jugador){
	int bombas = this -> pedir_bombas_validas(jugador);

	if(bombas != BOMBAS_VACIAS){
		cout << "Compraste " << bombas << " bombas exitosamente."  << endl;
		jugador -> obtener_inventario() -> modificar_cantidad_material("bombas", bombas);
		jugador -> obtener_inventario() -> modificar_cantidad_material("andycoins", -bombas * COSTO_BOMBAS);
		cout << "Te quedan " << jugador -> obtener_inventario() -> buscar_material("andycoins") << " andycoins." << endl;
	}
}

int Empresa_Constructora::pedir_bombas_validas(Jugador* jugador){
	int bombas = BOMBAS_VACIAS, bombas_comprables = jugador -> obtener_inventario() -> buscar_material("andycoins") % COSTO_BOMBAS;
	bool fin = false;
	string bombas_ingresadas;
	Resultado_Chequeos chequeo;
	do{
		cout << "Se pueden comprar " << bombas_comprables << " bombas." << endl;
		cout << "Ingresa la cantidad de bombas que queres comprar o salir" << endl << "Bombas: ";
		getline(cin, bombas_ingresadas);
		chequeo = this -> chequeo_bombas(bombas_ingresadas, bombas_comprables, bombas);
		fin = this -> mostrar_mensaje_chequeo(chequeo);
	}
	while(!fin);
	return bombas;
}

Resultado_Chequeos Empresa_Constructora::chequeo_bombas(string bombas_ingresadas, int bombas_comprables, int &bombas){
	Resultado_Chequeos resultado = EXITO;
	if(bombas_ingresadas == SALIR_STR)
		resultado = SALIR;
	else if(!es_numero(bombas_ingresadas) || stoi(bombas_ingresadas) < 0)
		resultado = NO_EXISTE;
	else if(stoi(bombas_ingresadas) > bombas_comprables)
		resultado = NO_MATERIALES;
	else{
		bombas = stoi(bombas_ingresadas);
	}
	return resultado;
}
