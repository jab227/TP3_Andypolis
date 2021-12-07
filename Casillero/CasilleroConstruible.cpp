#include "CasilleroConstruible.h"
#include "../empresa/Planos.h"
#include <iostream>

Casillero_Construible::Casillero_Construible(): Casillero(VERDE + NEGRO) {
	this -> edificio_ = nullptr;
}

Casillero_Construible::~Casillero_Construible() {
	delete this -> edificio_;
}

Resultado_Chequeos Casillero_Construible::construir_edificio(Edificio* edificio){
	Resultado_Chequeos resultado=CASILLERO_OCUPADO;
	if(!(this -> esta_ocupado())){
		this -> edificio_ = edificio;
		resultado = EXITO;
	}else{
		std::cout <<  "Esta ubicacion esta ocupada por otro edificio." << std::endl;
	}
	return resultado;
}

Resultado_Chequeos Casillero_Construible::demoler_edificio(){
	// Reveer.
	Resultado_Chequeos resultado = SALIR;
	if(this -> esta_ocupado()){
		this -> edificio_ = nullptr;
		resultado = EXITO;
	}
	return resultado;
}

bool Casillero_Construible::esta_ocupado() const{
	return (this -> edificio_ != nullptr);
}

void Casillero_Construible::saludar() const{
	std::cout << "Soy un casillero construible." << std::endl;
	if(this -> esta_ocupado()){
		this -> edificio_ -> saludar();
	}else
		std::cout << "No tengo ningun edificio construido." << std::endl;
}

//Necesario?
std::string Casillero_Construible::obtener_contenido() const{
	std::string edificio = EDIFICIO_VACIO; 
	if( this -> esta_ocupado()){
		edificio = this -> edificio_ -> obtener_nombre();
	}
	return edificio;
}

//Necesario? 
//PRE: Comentado porque necesita adaptarse a la lista de coordenadas de cada jugador.
Edificio* Casillero_Construible::agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos){
/*	if(this -> esta_ocupado()){
		Edificio* edificio = this -> edificio_; 
		Planos::existe(edificio -> obtener_nombre());
		//Necesitamos acceso al diccionario.
		//TODO: Agregar que necesitan reparacion. (!)
		if(indice == NO_ESTA){
			lista_nombres.alta_al_final(edificio);
			indice = (int) lista_nombres.consulta_largo();
		}
	}
*/
	return this -> edificio_;
}

//Provisorio
bool Casillero_Construible::es_casillero_transitable(){return false;}

//En teoria deberia ser impoisble pedirle materiales al obelisco porque termina el juego.
Resultado_Chequeos Casillero_Construible::recoger_material(Almacen* inventario){
	Material producto = this -> edificio_ -> producir_material();
	inventario -> sumar_cantidad_material(producto.obtener_nombre(), producto.obtener_cantidad());
	return EXITO;
}


Resultado_Chequeos Casillero_Construible::reparar_edificio(){
	Resultado_Chequeos resultado = NO_EXISTE;
	if(this->esta_ocupado())
		resultado = this -> edificio_ -> reparar();
	return resultado;
}

Resultado_Chequeos Casillero_Construible::atacar_edificio() {
	Resultado_Chequeos resultado = NO_EXISTE;
	if(this->esta_ocupado())
		resultado = this -> edificio_ -> disminuir_vida();
	return resultado;
}