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
		cout <<  "Esta ubicacion esta ocupada por otro edificio." << endl;
	}
	return resultado;
}

std::string Casillero_Construible::demoler_edificio(){
	std::string edificio = this -> edificio_ -> obtener_nombre();
	if(this -> esta_ocupado()){
		this -> edificio_ = nullptr;
	}else{
		cout <<  "En esta ubicacion no hay ningun edificio." << endl;
	}
	return edificio;
}

bool Casillero_Construible::esta_ocupado() const{
	return (this -> edificio_ != nullptr);
}

void Casillero_Construible::saludar() const{
	cout << "Soy un casillero construible." << endl;
	if(this -> esta_ocupado()){
		this -> edificio_ -> saludar();
		//Q: Por que esto?
		//cout << "Edificio construido exitosamente!" << endl;
	}else
		cout << "No tengo ningun edificio construido." << endl;
}

//Necesario?
void Casillero_Construible::obtener_contenido(Edificio*& edificio) const{
	edificio = nullptr;
	if( this -> esta_ocupado()){
		edificio = this -> edificio_;
	}
}
void Casillero_Construible::obtener_contenido(Material*& material) const{ material = nullptr; }

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

void Casillero_Construible::recoger_material(Almacen* inventario){
	Material producto = this -> edificio_ -> producir_material();
	inventario -> sumar_cantidad_material(producto.obtener_nombre(), producto.obtener_cantidad());
}
