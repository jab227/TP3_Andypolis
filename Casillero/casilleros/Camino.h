#include "../CasilleroTransitable.h"

class Camino: public Casillero_Transitable{
    public:
    //Constructor
    Camino();

    //PRE: -
    //POST: imprime un saludo por terminal. en caso de tener un material, este tambien
    //saluda. de lo contrario, se informa que no hay material.
    void saludar() const override;

};