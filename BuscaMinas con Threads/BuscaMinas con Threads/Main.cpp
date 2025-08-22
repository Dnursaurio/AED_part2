#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>
using namespace std;

void NUmeros_Detectores(int campo_minado[10][10], int fila_inicio, int fila_fin)
{
	for (int (*filas)[10] = campo_minado + fila_inicio; filas < campo_minado + fila_fin; filas++)
	{
		for (int* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			int contador = 0;
			//evitar chancar el numero detector encima de la mina
			if (*columnas == -1)
			{
				continue;
			}
			//detectar las minas
			else
			{
				//recorremos el campo para ennumerar los espacios
				int fila_actual = filas - campo_minado;
				int columna_actual = columnas - *filas;
				//los numeros detectores oslo recorren en una matriz de 3*3
				for (int fila_deteccion = fila_actual - 1; fila_deteccion < fila_actual + 2; fila_deteccion++)
				{
					if (fila_deteccion < 0 || fila_deteccion >= 10)
					{
						continue;
					}
					for (int columna_deteccion = columna_actual - 1; columna_deteccion < columna_actual + 2; columna_deteccion++)
					{
						if (columna_deteccion < 0 || columna_deteccion >= 10)
						{
							continue;
						}
						if (campo_minado[fila_deteccion][columna_deteccion] == -1)
						{
							contador++;
						}
					}
				}
				*columnas = contador;
			}
		}
	}
}

int main()
{
	srand(time(0));
	int campo_minado[10][10] = {};
	int minas = 0;
	int (*filas)[10] = campo_minado;
	int* columnas = *filas;

	cout << "cuidado,campo minado" << endl;

	//dibuja el campo minado vacio
	for (filas; filas < campo_minado + 10; filas++)
	{
		for (columnas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	cout << "ingrese el numero de minas para detectar: ";
	cin >> minas;
	cout << "se han detectado " << minas << " en el campo, tenga cuidado" << endl;

	//añade las minas de manera aleatoria
	for (int i = 0; i < minas; i++)
	{
		int f = rand() % 10;
		int c = rand() % 10;
		*(*(campo_minado + f) + c) = -1;
	}

	//calcular la cantidad de minas en cada espacio
	vector<thread> hilos;
	for (int i = 0; i < 4; i++)
	{
		int inicio = i * 10 / 4;
		int fin = (i + 1) * 10 / 4;
		hilos.push_back(thread(NUmeros_Detectores, campo_minado, inicio, fin));
	}

	for (auto& h : hilos)
	{
		h.join();
	}

	//dibujar el campo minado
	for (int (*filas)[10] = campo_minado; filas < campo_minado + 10; filas++)
	{
		for (int *columnas = *filas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout << endl;
	}

	return 0;
}