#ifndef COLOR_PRINTER_H_
#define COLOR_PRINTER_H_

#include "printer.h"
#include <string>

class ColorPrinter: public Printer {
public: 
	// Pre: Espera un ostream listo para escribir. 
	// Pos: Imprime str en el stream en color rojo
	static void color_msg(const std::string& str, const std::string& color,
	 std::ostream& stream);
};

#endif

