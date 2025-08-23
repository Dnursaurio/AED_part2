#include <iostream>

using namespace std;

int main()
{
	char sopa_de_letras[10][10] = {
		{'T','P','P','A','P','T','P','R','P','T'},
		{'O','P','A','T','A','P','O','Z','O','J'},
		{'S','A','T','A','T','O','T','A','Z','I'},
		{'A','T','A','P','A','P','A','T','O','S'},
		{'P','A','T','A','N','O','D','O','T','N'},
		{'T','A','A','P','A','T','I','P','A','P'},
		{'R','R','N','A','D','O','T','A','P','O'},
		{'E','D','N','T','A','P','O','T','A','T'},
		{'N','I','I','A','T','I','T','A','P','A'},
		{'P','S','S','N','T','T','T','P','A','P'},
	};

	char(*filas)[10] = sopa_de_letras;
	char* columnas = *filas;

	for (filas; filas < sopa_de_letras + 10; filas++)
	{
		for (columnas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	return 0;
}