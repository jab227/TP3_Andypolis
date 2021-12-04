#include "CasilleroConstruible.h"
#include <iostream>

Casillero_Construible::Casillero_Construible(): Casillero(VERDE + NEGRO) {
	this -> edificio_ = nullptr;
}

Casillero_Construible::~Casillero_Construible() {
	delete this -> edificio_;
}

bool Casillero_Construible::construir_edificio(Edificio* edificio){
	bool resultado=false;
	if(!(this -> esta_ocupado())){
		this -> edificio_ = edificio;
		resultado = true;
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
	return !(this -> edificio_ == nullptr);
}

void Casillero_Construible::saludar() const{
	cout << "Soy un casillero construible." << endl;
	if(this -> esta_ocupado()){
		this -> edificio_ -> saludar();
		cout << "Edificio construido exitosamente!" << endl;
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

Edificio* Casillero_Construible::agregar_lista_edificio( std::size_t fila, std::size_t columna, Lista<string> &lista_nombres,Lista<Lista<std::size_t*>*> &lista_coordenadas){
	if(this -> esta_ocupado()){
		std::size_t* coordenadas = new std::size_t[2];
		coordenadas[0] = fila;
		coordenadas[1] = columna;
		std::string edificio_ = this -> edificio_ -> obtener_nombre();	 
		//Agregar que necesitan reparacion.
		int indice = lista_nombres.buscar_indice(edificio_);
		if(indice == NO_ESTA){
			lista_nombres.alta_al_final(edificio_);
			Lista<std::size_t*>* auxiliar = new Lista<std::size_t*>;
			lista_coordenadas.alta_al_final(auxiliar);
			indice = (int) lista_nombres.consulta_largo();
		}
		lista_coordenadas.consulta(indice) -> alta_al_final(coordenadas);
	}
	return this -> edificio_;
}

//Provisorio
bool Casillero_Construible::es_casillero_transitable(){return false;}

void Casillero_Construible::recoger_material(Almacen* inventario){
	Material producto = this -> edificio_ -> producir_material();
	inventario -> sumar_cantidad_material(producto.obtener_nombre(), producto.obtener_cantidad());
}