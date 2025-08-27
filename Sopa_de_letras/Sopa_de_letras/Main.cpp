#include <iostream>
#include <cstring>

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
	cout << "ingrese la palabra que quiere buscar: ";
	char palabra_clave;
	cin >> palabra_clave;
	char palabra_array[100];
	cout << "la palabra que usted desea buscar es: " << palabra_array << endl;
	int contador_de_palabras = 0;
	char* deteccion_letras = palabra_array;
	//detector de palabras
	char*deteccion;
	deteccion = new char[100];
	//recorriendo a la derecha

	for (char(*f)[10] = sopa_de_letras; f < sopa_de_letras + 10; f++)
	{

	}

	cout << "La cantidad de veces que aparece " << palabra_clave << " en la sopa de letras es " << contador_de_palabras << " veces" << endl;
	return 0;
}