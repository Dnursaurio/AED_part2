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

	void Set(int x, int y, int val)
	{
		Nodo** FX;
		if (val == 0)
		{
			if (!FindX(x, y, FX))
			{
				return;
			}
			Remove(x, y);
			return;
		}
		else
		{
			if (FindX(x, y, FX))
			{
				(*FX)->valor = val;
				return;
			}
			Insert(x, y, val);
			return;
		}
	}

	int Get(int x, int y)
	{
		Nodo** FX;
		if (!FindX(x, y, FX))
		{
			cout << "Alli no hay nada (valor vacio 0)" << endl;
			return 0;
		}
		else
		{
			cout << "el valor en la posicion: (" << x << ", " << y << ") es " << (*FX)->valor << endl;
			return (*FX)->valor;
		}
	}

	void print()
	{
		for (int x = 0; x < tam; x++)
		{
			Nodo* actual = EjeX[x];
			for (int y = 0; y < tam; y++)
			{
				if (actual && actual->y == y)
				{
					cout << actual->valor << " ";
					actual = actual->abajo;
				}
				else
				{
					cout << "0 ";
				}
			}
			cout << endl;
		}
	}

private:
	int tam;
	Nodo** EjeX;
	Nodo** EjeY;
	int nro_elem;

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
		bool si_Y = FindY(x, y, FY);

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
		bool si_Y = FindY(x, y, FY);

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
};

int main()
{
	MatrizEsparsa me(4);
	me.Set(0, 0, 1);
	me.Set(0, 1, 2);
	me.Set(0, 2, 3);
	me.Set(0, 3, 4);
	me.Set(1, 0, 5);
	me.Set(1, 1, 6);
	me.Set(1, 2, 7);
	me.Set(1, 3, 8);
	me.Set(2, 0, 9);
	me.Set(2, 1, 10);
	me.Set(2, 2, 11);
	me.Set(2, 3, 12);
	me.Set(3, 0, 13);
	me.Set(3, 1, 14);
	me.Set(3, 2, 15);
	me.Set(3, 3, 16);
	me.print();
	cout << "------------------------------------" << endl;
	me.Get(1, 0);
	me.Set(0, 0, 0);
	me.print();
	cout << "------------------------------------" << endl;
	me.Set(0, 0, 0);
	me.Set(0, 1, 35);
	me.print();
	cout << "------------------------------------" << endl;
	me.Get(0, 0);

	return 0;
}