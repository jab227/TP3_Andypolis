#include "EmpresaConstructora.h"
#include <fstream>
#include "../utils/LecturaArchivos.h"
#include "../printer/color_printer.h"

std::string const SI = "si", NO = "no";
const std::size_t COSTO_BOMBAS = 100;


Empresa_Constructora::Empresa_Constructora() : planos(nullptr), mapa(nullptr){}

Empresa_Constructora::Empresa_Constructora(Planos* plano, Mapa* mapa): planos(plano), mapa(mapa) {}

Empresa_Constructora::~Empresa_Constructora() {
	if(planos != nullptr)
		delete this -> planos;
	if(mapa != nullptr)
		delete this -> mapa;
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
	std::size_t piedra, madera, metal;
	if(chequeo == EXITO){
		chequeo = pedir_materiales(nombre, piedra, madera, metal);
	}
	if(chequeo == EXITO){
		this -> planos -> modificar_edificio(nombre, piedra, madera, metal);
	}
	mostrar_mensaje_chequeo(chequeo);
}

void Empresa_Constructora::mostrar_mapa(){
	this -> mapa -> mostrar_mapa();
}

void Empresa_Constructora::mostrar_construidos(Jugador* jugador){
	jugador -> mostrar_construidos(this -> mapa);
}

void Empresa_Constructora::mover_jugador(Jugador* jugador){
	jugador -> mover(this -> mapa);
}

void Empresa_Constructora::consultar_coordenada(){
	Coordenada coordenada;
	std::cout << "Elegi las coordenadas a consultar o salir." << std::endl;
	Resultado_Chequeos resultado = pedir_coordenadas(coordenada);
	if(resultado == EXITO) this -> mapa -> saludar_coordenada(coordenada);
	mostrar_mensaje_chequeo(resultado);
}

void Empresa_Constructora::iniciar_coordenadas_jugador(Jugador* jugador){
	Coordenada coordenada;
	Resultado_Chequeos resultado;
	do{
		std::cout << "Jugador "<< jugador -> obtener_jugador() << ": Eliga las coordenadas donde empezar el juego:" << endl;
		resultado = pedir_coordenadas(coordenada);
		if(resultado == SALIR)
			ColorPrinter::color_msg("No se puede salir, se deben ingresar coordenadas",  ROJO, std::cout);
	}while(!mostrar_mensaje_chequeo(resultado) || resultado == SALIR);
	jugador -> mover_a_coordenada(coordenada, mapa);
}

void Empresa_Constructora::guardar_archivos(std::string ruta_materiales, std::string ruta_ubicaciones){
	//Implementar.
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
	jugador -> recolectar(this -> mapa);
	jugador -> usar_energia(ENERGIA_RECOLECTAR);
	//Mensajito con los recursos recolectados.
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
			mapa -> mostrar_mapa();
			Coordenada coordenada;
			std::cout << "Elegi las coordenadas del edificio a construir o salir." << std::endl;
			Resultado_Chequeos resultado = this -> pedir_coordenadas(coordenada);
			mostrar_mensaje_chequeo(resultado);
			if( resultado == EXITO ){
				this -> edificio_construido_confirmado(edificio, coordenada, jugador);
				mapa -> mostrar_mapa();
			}

		}else
			ColorPrinter::color_msg("No se realizó ningún cambio.",	 ROJO, std::cout);
	}
}

//TODO: Embellecer
void Empresa_Constructora::demoler_edificio(Jugador* jugador){
	Coordenada coordenada = Coordenada(0,0);
	Resultado_Chequeos resultado = NO_EXISTE;
	std::cout << "Elegi las coordenadas del edificio a demoler o salir." << std::endl;
	do resultado = this -> pedir_coordenadas(coordenada);
	while(!mostrar_mensaje_chequeo(resultado));
	std::size_t indice = jugador -> existe_ubicacion(coordenada);
	if(indice){ //Chequeo que le pertenece.
		std::string nombre_edificio = EDIFICIO_VACIO;
		resultado = this -> mapa -> demoler_edificio_ubicacion(nombre_edificio, coordenada);
		if(resultado == EXITO){
			//demoler_edificio_confirmado()
			Lista<Material> listado_necesario = planos -> materiales_necesarios(nombre_edificio);
			jugador -> recuperar_lista_materiales(listado_necesario);
			jugador -> eliminar_ubicacion(coordenada);
			jugador -> usar_energia(ENERGIA_DEMOLER);
		}
	} 
	mostrar_mensaje_chequeo( resultado );
}

Resultado_Chequeos Empresa_Constructora::pedir_edificio(std::string& edificio_ingresado){
	Printer::print_str("Elegir el edificio. Escribir \"salir\" si así lo desea." , std::cout);
	std::cout << "Edificio: ";
	getline(cin, edificio_ingresado);
	return chequeo_edificio(edificio_ingresado);
}

Resultado_Chequeos Empresa_Constructora::chequeo_edificio(const std::string& edificio_ingresado){
	Resultado_Chequeos resultado = EXITO;
	if(edificio_ingresado == SALIR_STR) resultado = SALIR;
	else {
		resultado = planos -> existe(edificio_ingresado);
		if(resultado == EXITO)
			if(edificio_ingresado == "obelisco")
				resultado = OBELISCO;
	}
	return resultado;
}

std::string Empresa_Constructora::pedir_edificio_construir( Jugador* jugador){
	bool fin = false;
	std::string edificio_ingresado;
	Resultado_Chequeos chequeo;
	do{
		chequeo = pedir_edificio(edificio_ingresado);
		if( chequeo == EXITO){
			std::cout << "debug: El nombre ingresado es valido." << std::endl;
			chequeo = planos -> chequeo_construir(edificio_ingresado, jugador, this -> mapa);
		}
		fin = mostrar_mensaje_chequeo(chequeo);
	}while(!fin);
	return edificio_ingresado;
}

Resultado_Chequeos Empresa_Constructora::pedir_materiales(std::string nombre,  std::size_t &piedra, std::size_t &madera, std::size_t &metal){
	std::string piedra_ingresada, madera_ingresada,  metal_ingresada;
	std::cout << "Ingrese la cantidad de cada material, salir o para no modificar la cantidad presione enter." << std::endl;
	std::cout << "Elegir cantidad de piedra: ";
	getline(std::cin, piedra_ingresada);	
	std::cout << "Elegir cantidad de madera: ";
	getline(std::cin, madera_ingresada);	
	std::cout <<"Elegir cantidad de metal: ";
	getline(std::cin, metal_ingresada);

	return chequeo_materiales(nombre, piedra_ingresada, madera_ingresada, metal_ingresada, piedra, madera, metal);
}

Resultado_Chequeos Empresa_Constructora::chequeo_materiales(std::string nombre, std::string piedra_ingresada, std::string madera_ingresada, std::string metal_ingresada,
			 std::size_t &piedra, std::size_t &madera, std::size_t &metal){

	Resultado_Chequeos resultado = EXITO;
	Edificio* edificio = this -> planos -> buscar(nombre);
	if(piedra_ingresada == "")
		piedra_ingresada = to_string(edificio -> obtener_cant_material(MATERIALES_EDIFICIOS[PIEDRA]));
	if(madera_ingresada == "")
		madera_ingresada = to_string(edificio -> obtener_cant_material(MATERIALES_EDIFICIOS[MADERA]));
	if(metal_ingresada == "")
		metal_ingresada = to_string(edificio -> obtener_cant_material(MATERIALES_EDIFICIOS[METAL]));

	if(madera_ingresada == SALIR_STR || piedra_ingresada == SALIR_STR || metal_ingresada == SALIR_STR )
		resultado = SALIR;
	else if(!es_numero(madera_ingresada) || !es_numero(piedra_ingresada) || !es_numero(metal_ingresada))
		resultado = NO_EXISTE;
	else{
		madera = std::stoul(madera_ingresada);
		piedra = std::stoul(piedra_ingresada);
		metal = std::stoul(metal_ingresada);
	}
	return resultado;
}

Resultado_Chequeos Empresa_Constructora::pedir_coordenadas(Coordenada& coordenada){
	std::string fila_ingresada, columna_ingresada;
	
	std::cout << "Fila: ";
	getline(cin, fila_ingresada);
	std::cout << "Columna: ";
	getline(cin, columna_ingresada);

	return chequeo_coordenadas(fila_ingresada, columna_ingresada, coordenada);
}

Resultado_Chequeos Empresa_Constructora::chequeo_coordenadas(std::string fila_ingresada, std::string columna_ingresada, Coordenada &coordenada){
	Resultado_Chequeos resultado = EXITO;
	coordenada = Coordenada(COORDENADA_VACIA, COORDENADA_VACIA);
	
	if(fila_ingresada == SALIR_STR || columna_ingresada == SALIR_STR) resultado = SALIR;
	else if(!es_numero(fila_ingresada) || !es_numero(columna_ingresada)) resultado = NO_EXISTE;
	else if(!(this -> mapa -> es_cordenada_valida(Coordenada(stoul(fila_ingresada), stoul(columna_ingresada))))) resultado = FUERA_RANGO;
	else coordenada = Coordenada(stoul(fila_ingresada), stoul(columna_ingresada));

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
		case OBELISCO:
			ColorPrinter::color_msg("Al obelisco no se pueden modificar sus materiales.", ROJO, std::cout);
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
		Lista<Material> listado_necesario = planos -> materiales_necesarios(nombre_edificio);
		jugador -> usar_lista_materiales(listado_necesario);
		jugador -> usar_energia(ENERGIA_CONSTRUIR);
		jugador -> agregar_ubicacion(coordenada);
	}
}

void Empresa_Constructora::reparar_edificio(Jugador* jugador){
	Coordenada coordenada;
	Resultado_Chequeos resultado = NO_EXISTE;

	std::cout << "Elegi las coordenadas del edificio a reparar o salir." << std::endl;
	do resultado = this -> pedir_coordenadas(coordenada);
	while(!mostrar_mensaje_chequeo(resultado));
	//Va a buscar el indice a pesar de pedir salir, no coincide e imprime el msj de las coordenadas.
	std::size_t indice = jugador -> existe_ubicacion(coordenada);
	if(indice){ //Chequeo que la coordenada este en la lista de ubicaciones.
		std::string nombre_edificio = this -> mapa -> obtener_contenido_ubicacion(coordenada);
		Lista<Material> listado_necesario = planos -> materiales_necesarios(nombre_edificio);
		resultado = this -> chequeo_reparar_edificio(jugador, listado_necesario, coordenada);
		if(resultado == EXITO){
			//reparar_edificio_confirmado()
			jugador -> cobrar_reparacion(listado_necesario);
			jugador -> usar_energia(ENERGIA_REPARAR);
		}
		mostrar_mensaje_chequeo( resultado );
	} else // Ojo porque puede querer salir y va a mostrar este msj.
		ColorPrinter::color_msg("No hay un edificio tuyo en estas coordenadas.", ROJO, std::cout);
}

void Empresa_Constructora::atacar_edificio(Jugador* jugador_activo, Jugador* jugador_inactivo){
	Resultado_Chequeos resultado = EXITO;
	Material bombas = jugador_activo -> obtener_inventario().obtener_material("bombas");
	if(!(bombas.obtener_cantidad() > 0))
		resultado = NO_MATERIALES;
	this -> mostrar_mensaje_chequeo(resultado);
	Coordenada coordenada(0,0);
	if(resultado == EXITO){
		mapa -> mostrar_mapa();
		std::cout << "Elegi las coordenadas del edificio a atacar o salir." << std::endl;
		do resultado = this -> pedir_coordenadas(coordenada);
		while(!mostrar_mensaje_chequeo(resultado));
		std::size_t indice = jugador_inactivo -> existe_ubicacion(coordenada);
		if(indice){
			jugador_activo -> usar_energia(ENERGIA_ATACAR);
			jugador_activo -> obtener_inventario().restar_cantidad_material(bombas.obtener_nombre(), 1);
			this -> bombardear_coordenadas(coordenada, jugador_inactivo);
		}else
			ColorPrinter::color_msg("No hay un edificio del otro jugador en estas coordenadas.", ROJO, std::cout);
	}
}

void Empresa_Constructora::bombardear_coordenadas(Coordenada coordenada, Jugador* jugador){
	std::string edificio;
	bool destruido = this -> mapa -> explota_bomba(edificio, coordenada);
	if(destruido){
		jugador -> eliminar_ubicacion(coordenada);
		ColorPrinter::color_msg( coordenada.a_string() + ": ¡Destruido!", TEXTO_VERDE, std::cout);
	}else
		ColorPrinter::color_msg(coordenada.a_string() + ": Todavia se mantiene en pie.", TEXTO_VERDE, std::cout);
}

Resultado_Chequeos Empresa_Constructora::chequeo_reparar_edificio(Jugador* jugador, Lista<Material> listado_necesario, Coordenada coordenada){
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
	if(mostrar_mensaje_chequeo(jugador -> obtener_inventario().comprar_bombas(cantidad_bombas))){
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

std::string Empresa_Constructora::estado_actual_materiales_mapa(){
	return mapa -> estado_actual_materiales();
}

std::string Empresa_Constructora::estado_actual_planos(){
	return planos -> estado_actual_edificios();
}

std::string Empresa_Constructora::estado_actual_edificios_mapa(Jugador* jugador){
	std::string texto = jugador -> a_string() + "\n";
	Lista<Coordenada> coordenadas = jugador -> obtener_edificios();
	Coordenada coordenada;
	for(std::size_t i = 1; i <= coordenadas.consulta_largo(); i++){
		coordenada = coordenadas.consulta(i);
		texto += mapa -> obtener_contenido_ubicacion(coordenada) + " ";
		texto += coordenada.a_string(); 
		texto += "\n";
	}
	return texto;
}

std::string Empresa_Constructora::estado_actual_ubicaciones(Lista<Jugador*> jugadores){
	std::string texto;
	texto = estado_actual_materiales_mapa();
	for(std::size_t i = 1; i <= jugadores.consulta_largo(); i++)
			texto += estado_actual_edificios_mapa(jugadores.consulta(i));
	return texto;
}