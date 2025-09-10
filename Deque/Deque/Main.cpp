#include <iostream>

using namespace std;

struct Deque
{
	Deque(int size)
	{
		tam = size;
		nro_elem = 0;
		mapa = new int* [size];
		inicio_mapa = mapa + tam / 2;
		fin_mapa = mapa + tam / 2;
		*inicio_mapa = new int[tam];
		*fin_mapa = *inicio_mapa;
		inicio_vector = *inicio_mapa + tam / 2;
		fin_vector = *fin_mapa + tam / 2;
	}

	void push_front(int x)
	{
		if (inicio_mapa == mapa)
		{
			//luego veremos una expansion
			cout << "deque frontal lleno" << endl;
			return;
		}
		else
		{
			if (inicio_vector < *inicio_mapa)
			{
				inicio_mapa--;
				*inicio_mapa = new int[tam];
				inicio_vector = *inicio_mapa + tam - 1;
			}
			if (nro_elem != 0)
			{
				inicio_vector--;
			}
			*inicio_vector = x;
			nro_elem++;
		}
	}
	void push_back(int x)
	{
		if (fin_mapa == mapa + tam - 1)
		{
			//luego veremos una expansion
			cout << "deque trasero lleno" << endl;
			return;
		}
		else
		{
			if (fin_vector > *fin_mapa + tam - 1)
			{
				fin_mapa++;
				*fin_mapa = new int[tam];
				fin_vector = *fin_mapa;
			}
			if (nro_elem != 0)
			{
				fin_vector++;
			}
			*fin_vector = x;
			nro_elem++;
		}
	}
	void pop_front()
	{
		inicio_vector++;
		if (inicio_vector > *inicio_mapa + tam - 1)
		{
			int** borrador = inicio_mapa;
			inicio_mapa++;
			delete *borrador;
			inicio_vector = *inicio_mapa;
		}
		nro_elem--;
	}
	void pop_back()
	{
		fin_vector--;
		if (fin_vector < *fin_mapa)
		{
			int** borrador = fin_mapa;
			fin_mapa--;
			delete *borrador;
			fin_vector = *fin_mapa + tam - 1;
		}
		nro_elem--;
	}
	int& operator[](int i)
	{
		int indice_0 = i + (inicio_vector - *inicio_mapa);
		int bloque = indice_0 / tam;
		int pos = indice_0 % tam;
		return *(*(inicio_mapa + bloque) + pos);
	}

	void print()
	{
		cout << "[ ";
		for (int i = 0; i < nro_elem; i++)
		{
			cout << (*this)[i] << " ";
		}
		cout << "]" << endl;
	}

	int** mapa;
	int** inicio_mapa;
	int** fin_mapa;
	int* inicio_vector;
	int* fin_vector;
	int tam;
	int nro_elem;
};

int main()
{
	cout << "----------------------------------Deque----------------------------------" << endl;
	Deque dq(5);
	dq.push_front(2);	dq.print();
	dq.push_front(3);	dq.print();
	dq.push_front(5);	dq.print();
	dq.push_back(16);	dq.print();
	dq[3] = 12;			dq.print();
	dq.pop_front();		dq.print();
	dq.pop_back();		dq.print();
	cout << "-------------------------------------------------------------------------" << endl;

	return 0;
}