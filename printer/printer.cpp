#include "printer.h"

#include "../utils/colors.h"
#include <iostream>


void Printer::print_str(const std::string& str, std::ostream& stream) {
	stream << str << std::endl;
}

void Printer::clear_screen() { std::cout << CLEAR << std::endl; }
