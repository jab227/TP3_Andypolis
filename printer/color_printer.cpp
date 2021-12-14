#include "color_printer.h"
#include "../utils/colors.h"

void ColorPrinter::color_msg(const std::string& str, const std::string& color,
 					std::ostream& stream) {
	stream << color << str << END_COLOR << std::endl;
}
