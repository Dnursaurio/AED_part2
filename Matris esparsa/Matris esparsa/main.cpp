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

	struct objx
	{
		objx(MatrizEsparsa* matriz, int x, int y)
		{
			mtr = matriz;
			cx = x;
			cy = y;
		}

		objx operator= (int v)
		{
			mtr->Set(cx, cy, v);
			return *this;
		}

		operator int()
		{
			return mtr->Get(cx, cy);
		}

		MatrizEsparsa* mtr;
		int cx;
		int cy;
	};

	objx operator() (int x, int y)
	{
		return objx(this, x, y);
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
		if (x > tam - 1 || y > tam - 1)
		{
			cout << "Posicion (" << x << ", " << y << ") fuera de rango" << endl;
			return 0;
		}
		else
		{
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
	}
};

int main()
{
	MatrizEsparsa me(4);
	me(0, 0) = 1;
	me(0, 1) = 2;
	me(0, 2) = 3;
	me(0, 3) = 4;
	me(1, 0) = 5;
	me(1, 1) = 6;
	me(1, 2) = 7;
	me(1, 3) = 8;
	me(2, 0) = 9;
	me(2, 1) = 10;
	me(2, 2) = 11;
	me(2, 3) = 12;
	me(3, 0) = 13;
	me(3, 1) = 14;
	me(3, 2) = 15;
	me(3, 3) = 16;

	
	me.print();
	cout << "------------------------------------" << endl;
	int a = 0; 
	a = me(1, 0);
	a = me(3, 2);
	a = me(4, 0);
	me(0, 0) = 0;
	me.print();
	cout << "------------------------------------" << endl;
	me(0, 0) = 0;
	me(0, 1) = 35;
	me.print();
	cout << "------------------------------------" << endl;
	a = me(0, 0);
	a = me(3, 1);

	return 0;
}