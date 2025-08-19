#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	srand(time(0));
	int campo_minado[10][10] = {};
	int minas = 0;

	cout << "cuidado,campo minado" << endl;
	
	//dibuja el campo minado vacio
	for (int (*filas)[10] = campo_minado; filas < campo_minado + 10; filas++)
	{
		for(int*columnas=*filas;columnas<*filas+10;columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	cout << "ignrese el numero de minas para detectar: ";
	cin >> minas;
	cout << "se han detectado " << minas << " en el campo, tenga cuidado" << endl;

	//añade las minas de manera aleatoria
	for (int i = 0; i < minas; i++)
	{
		int f = rand() % 10;
		int c = rand() % 10;
		*(*(campo_minado + f) + c) = -1;
	}

	//calcular la cantidad de minar en cada espacio
	for (int (*filas)[10] = campo_minado; filas < campo_minado + 10; filas++)
	{
		for (int* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			if (*columnas == -1)
			{
				continue;
			}
		}
		cout << endl;
	}

	//dibujar el campo minado
	for (int (*filas)[10] = campo_minado; filas < campo_minado + 10; filas++)
	{
		for (int* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	return 0;
}