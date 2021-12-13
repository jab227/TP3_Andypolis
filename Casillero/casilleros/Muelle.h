#include "../CasilleroTransitable.h"

class Muelle: public Casillero_Transitable{
    public:
    //Constructor
    Muelle();

     //PRE: -
    //POST: Imprime un saludo por terminal y si esta ocupado pide al material que salude. Si no tiene, avisa por terminal. void saludar() const override;
    void saludar() const override;

    //PRE: -
    //POST: devuelve un identificador de esta clase.
    char obtener_identificador();
};
