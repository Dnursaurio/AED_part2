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

	for (char(*filas)[10] = sopa_de_letras; filas < sopa_de_letras + 10; filas++)
	{
		for (char* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	cout << "ingrese la palabra que quiere buscar: ";
	char palabra_array[100];
	cin >> palabra_array;
	int longitud_original = strlen(palabra_array);
	cout << "la palabra que usted desea buscar es: " << palabra_array << " con " << longitud_original << " elementos" << endl;
	int contador_de_palabras = 0;
	
	//recorrido de izquierda a derecha
	for (char(*filas)[10] = sopa_de_letras; filas < sopa_de_letras + 10; filas++)
	{
		for (char* columnas = *filas; columnas <= *filas + 10 - longitud_original; columnas++)
		{
			bool coincidencia = true;
			for (int i = 0; i < longitud_original; i++)
			{
				if (*(columnas + i) != palabra_array[i])
				{
					coincidencia = false;
					break;
				}
			}
			if (coincidencia)
			{
				contador_de_palabras++;
			}
		}
	}

	//recorrido de derecha a izquierda
	for (char(*filas)[10] = sopa_de_letras; filas < sopa_de_letras + 10; filas++)
	{
		for (char* columnas = *filas + 9; columnas >= *filas + longitud_original - 1; columnas--)
		{
			bool coincidencia = true;
			for (int i = 0; i < longitud_original; i++)
			{
				if (*(columnas - i) != palabra_array[i])
				{
					coincidencia = false;
					break;
				}
			}
			if (coincidencia)
			{
				contador_de_palabras++;
			}
		}
	}

	//recorrido de arriba a abajo
	for (int columnas = 0; columnas < 10; columnas++)
	{
		for (char(*filas)[10] = sopa_de_letras; filas <= sopa_de_letras + 10 - longitud_original; filas++)
		{
			bool coincidencia = true;
			for (int i = 0; i < longitud_original; i++)
			{
				if (*(*(filas + i) + columnas) != palabra_array[i])
				{
					coincidencia = false;
					break;
				}
			}
			if (coincidencia)
			{
				contador_de_palabras++;
			}
		}
	}

	//recorrido de abajo hacia arriba
	for (int columnas = 0; columnas < 10; columnas++)
	{
		for (char(*filas)[10] = sopa_de_letras + 9; filas >= sopa_de_letras + longitud_original - 1; filas--)
		{
			bool coincidencia = true;
			for (int i = 0; i < longitud_original; i++)
			{
				if (*(*(filas - i) + columnas) != palabra_array[i])
				{
					coincidencia = false;
					break;
				}
			}
			if (coincidencia)
			{
				contador_de_palabras++;
			}
		}
	}

	cout << "La cantidad de veces que aparece " << palabra_array << " en la sopa de letras es " << contador_de_palabras << " veces" << endl;
	return 0;
}