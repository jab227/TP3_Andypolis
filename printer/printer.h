#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
#include <ostream>

class Printer {
public: 
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime el str en stream. 
	static void print_str(const std::string& str, std::ostream& stream);
	// Pre: -
	// Pos: Limpia la pantalla.
	static void clear_screen();
};

#endif
