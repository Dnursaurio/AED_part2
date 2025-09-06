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
	int nro_elementos = 0;
	char palabra_array[100];
	cin >> palabra_array;
	char* deteccion_letras = palabra_array;
	int longitud_original = strlen(palabra_array);
	nro_elementos = nro_elementos + longitud_original;
	cout << "la palabra que usted desea buscar es: " << palabra_array << " con " << nro_elementos << " elementos" << endl;
	int contador_de_palabras = 0;
	//detector de palabras
	//recorriendo de derecha a izquierda
	for (char(*f)[10] = sopa_de_letras; f < sopa_de_letras + 10; f++)
	{
		//recorrer a la derecha
		for (char* col_derecha = *f; col_derecha < *f + 10; col_derecha++)
		{
			if (*col_derecha == *deteccion_letras)
			{
				deteccion_letras++;
				if (deteccion_letras - palabra_array == longitud_original)
				{
					contador_de_palabras++;
					deteccion_letras = palabra_array;
				}
			}
			else
			{
				deteccion_letras = palabra_array;
				continue;
			}
		}
		//recorrido a la izquierda
		deteccion_letras = palabra_array;
		for (char* col_izquierda = *f + 9; col_izquierda >= *f; col_izquierda--)
		{
			if (*col_izquierda == *deteccion_letras)
			{
				deteccion_letras++;
				if (deteccion_letras - palabra_array == longitud_original)
				{
					contador_de_palabras++;
					deteccion_letras = palabra_array;
				}
			}
			else
			{
				deteccion_letras = palabra_array;
				continue;
			}
		}
	}

	//recorriendo de arriba a abajo
	for (int col = 0; col < 10; col++)
	{
		//recorrer de arriba a abajo
		deteccion_letras = palabra_array;
		for (char(*fil)[10] = sopa_de_letras; fil < sopa_de_letras + 10; fil++)
		{
			char letra = *(*(fil)+col);
			if (letra == *deteccion_letras)
			{
				deteccion_letras++;
				if (deteccion_letras - palabra_array == longitud_original)
				{
					contador_de_palabras++;
					deteccion_letras = palabra_array;
				}
			}
			else
			{
				deteccion_letras = palabra_array;
				continue;
			}
		}

		//recorrer de abajo a arriba
		deteccion_letras = palabra_array;
		for (char(*fil)[10] = sopa_de_letras + 9; fil >= sopa_de_letras; fil--)
		{
			char letra = *(*(fil)+col);
			if (letra == *deteccion_letras)
			{
				deteccion_letras++;
				if (deteccion_letras - palabra_array == longitud_original)
				{
					contador_de_palabras++;
					deteccion_letras = palabra_array;
				}
			}
			else
			{
				deteccion_letras = palabra_array;
				continue;
			}
		}
	}

	cout << "La cantidad de veces que aparece " << palabra_array << " en la sopa de letras es " << contador_de_palabras << " veces" << endl;
	return 0;
}