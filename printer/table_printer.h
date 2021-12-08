#ifndef TABLE_PRINTER_H_
#define TABLE_PRINTER_H_

#include "printer.h"
#include "../edificio/Edificio.h"
#include "../material/Material.h"
#include "../utils/Lista.h"
#include "../empresa/Mapa.h"
#include "../utils/coordenada.h"
#include <ostream>
#include <iomanip>


const char SEPARATOR = ' ';
const int WIDTH = 20;

class TablePrinter: public Printer {
public: 
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime la informacion del material en formato fila en el stream. 
	void print_row(const Material* material, std::ostream& stream) const;
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime la informacion del building en formato fila en el stream. 
	void print_row(const Edificio* edificio, std::ostream& stream) const;
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime el vector de string en formato fila de tabla. 
	void print_row(const Lista<std::string> header, std::ostream& stream) const;
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime el contenido del casillero que se encuentra en la coordenada del mapa en
	// string en formato fila de tabla. 
	void print_row(const Mapa* mapa, const Coordenada& coordenada, std::ostream& stream) const;
	// Pre: n_cols >0. Espera un ostream listo para escribir. 
	// Pos: Imprime una linea punteada en el stream. 
	void print_row_separator(const std::size_t n_cols, std::ostream& stream) const;
private: 
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime el str en el stream en formato celda de tabla. 
	void print_table_cell(const std::string& str, std::ostream& stream) const;
	

};

#endif
