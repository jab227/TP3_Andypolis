#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"
#include "../printer/color_printer.h"

std::string const SI = "si", NO = "no";
const std::size_t COORDENADA_VACIA = -1, BOMBAS_VACIAS = -1, COSTO_BOMBAS = 100;


Empresa_Constructora::Empresa_Constructora(){
	this -> almacen = nullptr;
	this -> planos = nullptr;
	this -> mapa = nullptr;
}

Empresa_Constructora::Empresa_Constructora(Planos* plano): almacen(nullptr), planos(plano), mapa(nullptr) {}

Empresa_Constructora::~Empresa_Constructora() {
	if(almacen != nullptr)
		delete this -> almacen;
	if(planos != nullptr)
		delete this -> planos;
	if(mapa != nullptr)
		delete this -> mapa;
}

bool Empresa_Constructora::cargar_archivos(std::string ruta_materiales, std::string ruta_edificios, std::string ruta_mapa, std::string ruta_ubicaciones){
	//TODO: Poner parsers.
	return false;
}

void Empresa_Constructora::mostrar_materiales(Jugador* jugador){
	jugador -> mostrar_inventario();
}

void Empresa_Constructora::mostrar_edificios(){
	this -> planos -> mostrar_edificios();
}

void Empresa_Constructora::modificar_edificios(){
	std::string nombre;
	Resultado_Chequeos chequeo = pedir_edificio(nombre);
	std::size_t madera, piedra, metal;
	if(chequeo == EXITO){
		chequeo = pedir_materiales(madera, piedra, metal);
	}
	if(chequeo == EXITO){
		this -> planos -> modificar_edificio(nombre, madera, piedra, metal);
	}
	mostrar_mensaje_chequeo(chequeo);
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
		jugador -> agregar_ubicacion(coordenada);
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
	std::string edificio = pedir_edificio_construir(jugador);
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

Resultado_Chequeos Empresa_Constructora::chequeo_edificio(const std::string& edificio_ingresado){
	Resultado_Chequeos resultado = EXITO;
	if(edificio_ingresado == SALIR_STR) resultado = SALIR;
	else if(es_numero(edificio_ingresado)) resultado = NO_EXISTE;
	else resultado = planos -> existe(edificio_ingresado);
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::pedir_edificio(std::string& edificio_ingresado){
	Printer::print_str("Elegir el edificio. Escribir \"salir\" si así lo desea." , std::cout);
	getline(cin, edificio_ingresado);
	return chequeo_edificio(edificio_ingresado);
}

std::string Empresa_Constructora::pedir_edificio_construir( Jugador* jugador){
	bool fin = false;
	std::string edificio_ingresado;
	Resultado_Chequeos chequeo;
	do{	
		chequeo = pedir_edificio(edificio_ingresado);
		if( chequeo == EXITO)
			chequeo = planos -> chequeo_construir(edificio_ingresado, jugador, this -> mapa);
		fin = mostrar_mensaje_chequeo(chequeo);
	}while(!fin);
	return edificio_ingresado;
}
Resultado_Chequeos Empresa_Constructora::pedir_materiales( std::size_t &piedra, std::size_t &madera, std::size_t &metal){
	std::string piedra_ingresada, madera_ingresada,  metal_ingresada;
	
	std::cout << "Elegir cantidad de piedra: ";
	getline(std::cin, piedra_ingresada);	
	std::cout << "Elegir cantidad de madera: ";
	getline(std::cin, madera_ingresada);	
	std::cout <<"Elegir cantidad de metal: ";
	getline(std::cin, metal_ingresada);


	madera = std::stoul(madera_ingresada);
	piedra = std::stoul(piedra_ingresada);
	metal = std::stoul(metal_ingresada);
	return chequeo_materiales( piedra_ingresada, madera_ingresada, metal_ingresada);
}


//TODO: Constructo de copia?? Asi no tenemos que pasarle una coordenada creada.
//RTA: La coordenada es un parametro de salida, no de entrda, por eso se le pasa una creada
Resultado_Chequeos Empresa_Constructora::pedir_coordenadas(Coordenada& coordenada){
	std::string fila_ingresada, columna_ingresada;
	
	std::cout << "Elegi las coordenadas del edificio o salir \n Fila: " << std::endl;
	getline(cin, fila_ingresada);
	std::cout << "Columna: " << std::endl;
	getline(cin, columna_ingresada);

	//coordenada = Coordenada(stoi(fila_ingresada),stoi(columna_ingresada)); No se puede hacer STOI si no sabes si son numeros
	return chequeo_coordenadas(fila_ingresada, columna_ingresada, coordenada);
}

Resultado_Chequeos Empresa_Constructora::chequeo_coordenadas(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada){
	Resultado_Chequeos resultado = EXITO;
	coordenada = Coordenada(COORDENADA_VACIA, COORDENADA_VACIA);
	
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR) resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada)) resultado = NO_EXISTE;
	else if(!(this -> mapa -> es_cordenada_valida(Coordenada(stoi(fila_ingresada), stoi(columna_ingresada))))) resultado = FUERA_RANGO;
	else coordenada = Coordenada(stoi(fila_ingresada), stoi(columna_ingresada));

	return resultado;
}

Resultado_Chequeos Empresa_Constructora::chequeo_materiales(std::string piedra_ingresada, std::string madera_ingresada, std::string metal_ingresada){
	Resultado_Chequeos resultado = EXITO;
	
	if(madera_ingresada == SALIR_STR || piedra_ingresada == SALIR_STR || metal_ingresada == SALIR_STR ) resultado = SALIR;
	else if(!es_numero(madera_ingresada) || !es_numero(piedra_ingresada) || !es_numero(metal_ingresada)) resultado = NO_EXISTE;
	return resultado;
}


bool Empresa_Constructora::mostrar_mensaje_chequeo(Resultado_Chequeos chequeo){
	bool fin = false;
	switch(chequeo){
		case EXITO:
			fin = true;
			break;
		case NO_EXISTE:
			ColorPrinter::color_msg("La/s opcion/es ingresada/s no es/son valida/s.", ROJO, std::cout);
			break;
		case MAXIMA_CANTIDAD:
			ColorPrinter::color_msg("Hay la cantidad maxima permitida construida de este edificio.", ROJO, std::cout);
			break;
		case NO_MATERIALES:
			ColorPrinter::color_msg("No hay suficientes materiales.", ROJO, std::cout);
			//TODO: mostrar_materiales_insuficientes(edificio);
			break;
		case FUERA_RANGO:
			ColorPrinter::color_msg( "La ubicacion ingresada excede el rango del mapa.", ROJO, std::cout);
			break;
		case SALIR:
			ColorPrinter::color_msg( "No se realizo ninguna accion.", ROJO, std::cout);
			fin = true;
			break;
		case CASILLERO_NO_CONSTRUIBLE:
			ColorPrinter::color_msg("La ubicacion ingresada no es construible.", ROJO, std::cout);
			break;
		case CASILLERO_OCUPADO:
			ColorPrinter::color_msg("Esta ubicacion esta ocupada por otro edificio.", ROJO, std::cout);
			break;
		case NO_REPARABLE:
			ColorPrinter::color_msg("El edificio no necesita reparación.", ROJO, std::cout);
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
		ColorPrinter::color_msg("La respuesta no es valida, solo se acepta si o no.", ROJO, std::cout);
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
		jugador -> agregar_ubicacion(coordenada);
	}
}

void Empresa_Constructora::reparar_edificio(Jugador* jugador){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = NO_EXISTE;
	do resultado = this -> pedir_coordenadas(coordenada);
	while(!mostrar_mensaje_chequeo(resultado));
	std::size_t indice = jugador -> existe_ubicacion(coordenada);
	if(indice && coordenada.x != COORDENADA_VACIA){ //Chequeo que le pertenece y que no se ingreso salir.
		std::string nombre_edificio = this -> mapa -> obtener_contenido_ubicacion(coordenada);
		Edificio* edificio = Planos::buscar(nombre_edificio);
		Lista<Material>* listado_necesario = planos -> materiales_necesarios(edificio);
		resultado = this -> chequeo_reparar_edificio(jugador, listado_necesario, coordenada);
		if(resultado == EXITO){
			//reparar_edificio_confirmado()
			jugador -> cobrar_reparacion(listado_necesario);
			jugador -> usar_energia(ENERGIA_REPARAR);
		}
		delete listado_necesario;
		mostrar_mensaje_chequeo( resultado );
	} else if(!indice)
		std::cout << "No hay un edificio tuyo en estas coordenadas." <<std::endl;
}

Resultado_Chequeos Empresa_Constructora::chequeo_reparar_edificio(Jugador* jugador, Lista<Material>* listado_necesario, Coordenada coordenada){
	Resultado_Chequeos resultado = EXITO;
	if(!jugador -> tiene_materiales_reparar(listado_necesario))
		resultado = NO_MATERIALES;
	else
		resultado = this -> mapa -> reparar_edificio_ubicacion(coordenada);
	return resultado;
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
	std::cout << "¿Cuantas bombas desea comprar? (Precio: " << COSTO_BOMBAS << "andycoins): ";
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
