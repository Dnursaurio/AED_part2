#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void suma(int ini, int fin,int fila_ini, int arr[][4], int& suma)
{
	suma = 0;
	for (int o = ini; o < fin; o++)
	{
		suma += arr[fila_ini][o];
	}
}

int main()
{
	int nro_nucleos = thread::hardware_concurrency();
	cout << "El numero de nucleos de este PC es: " << nro_nucleos << endl;

	//Reto 1 Matriz con 6 threads
	vector<thread>VT(6);
	int almacen[6] = {0,0,0,0,0,0};
	int arr[4][4]
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};

	//primeros 2 threads
	int fila_ini = 0;
	for (int i = 0; i < VT.size() - 4; i++)
	{
		VT[i] = thread(suma, 0, 4, fila_ini, arr, ref(almacen[i]));
		fila_ini++;
	}
	//lo demas
	for (int i = 2; i < VT.size(); i++)
	{
		if (VT.size() % 2 == 0)
		{
			VT[i] = thread(suma, 0, 2, fila_ini, arr, ref(almacen[i]));
			i++;
		}
		VT[i] = thread(suma, 2, 4, fila_ini, arr, ref(almacen[i]));
		fila_ini++;
	}
	//sincronizando los threads
	for (int i = 0; i < VT.size(); i++)
	{
		VT[i].join();
	}

	int suma_total = 0;
	for (int i = 0; i < 6; i++)
	{
		suma_total += almacen[i];
	}
	cout << "la suma total de la matriz es " << suma_total << endl;

	return 0;
}