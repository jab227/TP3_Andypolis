#include "table_printer.h"
#include "../utils/colors.h"

void TablePrinter::print_table_cell(const std::string& str, std::ostream& stream) const{
	stream<< std::left << std::setw(WIDTH) << std::setfill(SEPARATOR) << str;

}	
void TablePrinter::print_row_separator(const std::size_t n_cols, std::ostream& stream) const{
	stream << std::endl << std::string(WIDTH * n_cols, '-') << std::endl;
}	

void TablePrinter::print_row(const Material  material, std::ostream& stream) const{
	print_table_cell( material.obtener_nombre(), stream);
	print_table_cell( std::to_string(material.obtener_cantidad()), stream);
	//TODO: Constante
	print_row_separator(2, stream);
}

void TablePrinter::print_row(const Edificio* edificio, std::ostream& stream) const{
	std::string name = edificio->obtener_nombre();
	print_table_cell( name , stream);
	//for(std::size_t i = 0; i < CANT_MATERIALES_EDIFICIOS; i++)
	print_table_cell( std::to_string(edificio->obtener_cant_material("piedra")), stream );
	print_table_cell( std::to_string(edificio->obtener_cant_material("madera")), stream );
	print_table_cell( std::to_string(edificio->obtener_cant_material("metal")), stream );
	print_table_cell( std::to_string(edificio->obtener_max_permitidos()), stream);
	print_table_cell(edificio->info_producto(), stream);
	//TODO: Constante
	print_row_separator(6, stream);

}

void TablePrinter::print_row(const Lista<std::string> header, std::ostream& stream) const{
	for(std::size_t i = 1; i <= header.consulta_largo(); i++) {
		print_table_cell(header.consulta(i), stream);
	}
	print_row_separator(header.consulta_largo(), stream);
}


void TablePrinter::print_row(const Mapa* mapa, const Coordenada& coordenada, std::ostream& stream) const{
	std::string edificio = mapa -> obtener_contenido_ubicacion(coordenada);
	bool necesita_reparar = (mapa -> reparar_edificio_ubicacion(coordenada, false) == EXITO);
	print_table_cell( edificio, stream);
	print_table_cell( coordenada.a_string(), stream);
	print_table_cell( necesita_reparar? "SI" : "NO", stream);
	//TODO: Constante
	print_row_separator(3, stream);
}
