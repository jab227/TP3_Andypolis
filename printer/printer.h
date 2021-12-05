#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
#include <ostream>

//TODO: Heredados del printer. Colocar en el lugar correspondiente.S
static const std::string RESET = "\e\[0m";
static const std::string BOLD = "\e\[1m";
static const std::string UNDERLINE = "\e\[4m";
static const std::string CLEAR = "\e\[H\e[2J";
static const std::string GREEN = "\e\[32m";
static const std::string RED = "\e\[31m";
static const std::string YELLOW = "\e\[33m";
static const std::string BLUE = "\e\[34m";

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
