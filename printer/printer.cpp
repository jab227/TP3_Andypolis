#include "printer.h"

#include "../utils/colors.h"
#include <iostream>

static const std::string LIMPIAR_PANTALLA = "\e\[H\e[2J";

void Printer::print_str(const std::string& str, std::ostream& stream) {
	stream << str << std::endl;
}

void Printer::clear_screen() { std::cout << LIMPIAR_PANTALLA << std::endl; }