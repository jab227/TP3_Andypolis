#include "../CasilleroTransitable.h"

class Betun: public Casillero_Transitable{
    public:
    //Constructor
    Betun();

    //PRE: -
    //POST: Imprime un saludo por terminal y si esta ocupado pide al material que salude. Si no tiene, avisa por terminal.
    void saludar() const override;

	//PRE:
	//POS: Retorna BETUN.
    char obtener_identificador();

};
