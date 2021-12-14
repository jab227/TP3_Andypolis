#include <iostream>
#include "../utils/Lista.h"
#include "diccionario.h"
using namespace std;
int main()
{
	Diccionario<int, char> d;
	char cs [5] = {'a','b','c','d','e'};
	for (int i = 0; i < 5; ++i) {
		d[i] = cs[i]; 
	}
	Lista<int> l = d.claves();
	for (size_t i = 1; i < l.consulta_largo() + 1; ++i)
		cout << l.consulta(i) << " ";
	
	cout << endl;
	return 0;
}
