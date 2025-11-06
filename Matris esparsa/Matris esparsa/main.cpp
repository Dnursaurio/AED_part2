#include <iostream>

using namespace std;

struct Nodo
{
	Nodo(int v)
	{
		valor = v;
		x = 0;
		y = 0;
		der = nullptr;
		abajo = nullptr;
	}

	int valor;
	int x;
	int y;
	Nodo* der;
	Nodo* abajo;
};

class MatrizEsparsa
{
public:
	MatrizEsparsa(int t)
	{
		tam = t;
		/*recordando el array del eje X tiene punteros en Y
		el Y tiene punteros en el eje X*/
		EjeX = new Nodo* [tam];
		EjeY = new Nodo* [tam];
		for (int i = 0; i < tam; i++)
		{
			EjeX[i] = nullptr;
			EjeY[i] = nullptr;
		}
		nro_elem = 0;
	}

	bool FindX(int x, int y, Nodo**& FX)
	{
		//Ingresamos en X y modificamos Y
		FX = &(EjeX[x]);
		while (*FX && (*FX)->y < y)
		{
			FX = &((*FX)->abajo);
		}
		return *FX && (*FX)->y == y;
	}

	bool FindY(int x, int y, Nodo**& FY)
	{
		//Ingresamos en Y y Modificamos X
		FY = &(EjeY[y]);
		while (*FY && (*FY)->x < x)
		{
			FY = &((*FY)->der);
		}
		return *FY && (*FY)->x == x;
	}

	bool Insert(int x, int y, int val)
	{
		Nodo** FX = nullptr;
		Nodo** FY = nullptr;
		bool si_X = FindX(x, y, FX);
		if (si_X)
		{
			return 0;
		}
		else
		{
			Nodo* temp = new Nodo(val);
			temp->x = x;
			temp->y = y;
			temp->abajo = *FX;
			*FX = temp;
			temp->der = *FY;
			*FY = temp;
			nro_elem++;
			return 1;
		}
	}

	bool Remove(int x, int y)
	{
		Nodo** FX = 0;
		Nodo** FY = 0;
		bool si_X = FindX(x, y, FX);
		if (!si_X)
		{
			return 0;
		}
		else
		{
			Nodo* temp = *FX;
			if (temp)
			{
				*FX = temp->abajo;
				*FY = temp->der;
				temp->der = nullptr;
				temp->abajo = nullptr;
				nro_elem--;
			}
			delete temp;
			return 1;
		}
	}

private:
	int tam;
	Nodo** EjeX;
	Nodo** EjeY;
	int nro_elem;
};

int main()
{

}