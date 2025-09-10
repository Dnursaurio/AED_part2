#include <iostream>

using namespace std;

int main()
{
	cout << "---------------------------Laberinto A_B---------------------------" << endl;
	char laberinto[10][10] = {
		{'A','*',' ',' ',' ',' ',' ',' ',' ','*'},
		{' ','*',' ',' ',' ',' ','*','*',' ','*'},
		{' ','*',' ','*','*',' ','*','*','*','*'},
		{' ','*',' ','*',' ',' ','*',' ',' ',' '},
		{' ',' ',' ','*',' ',' ',' ',' ','*','*'},
		{' ','*','*','*','*','*',' ',' ','*',' '},
		{' ',' ',' ',' ','*',' ',' ',' ',' ',' '},
		{' ','*','*',' ','*',' ',' ','*','*','*'},
		{'*','*',' ',' ','*',' ',' ','*',' ',' '},
		{' ',' ',' ','*','*',' ',' ',' ',' ','B'}
	};

	//Graficamos el laberinto
	for (char(*filas)[10] = laberinto; filas < laberinto + 10; filas++)
	{
		for (char* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			cout << *columnas << " ";
		}
		cout <<"|" << endl;
	}
	cout << "---------------------" << endl;
	//recorriendo el array pero con una malla de 3*3 paea detectar espacios vacios
	for (char(*filas)[10] = laberinto; filas < laberinto + 10; filas++)
	{
		for (char* columnas = *filas; columnas < *filas + 10; columnas++)
		{
			int caminos_posibles = 0;
			//aqui que detecte el 3*3a
			int fila_actual =filas - laberinto;
			int columnas_actual = columnas - *filas;


		}
	}
	cout << "-------------------------------------------------------------------" << endl;
}