#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <class T>
struct Greater
{
	bool operator()(T a, T b)
	{
		return a > b;
	}
};

template <class T>
struct Less
{
	bool operator()(T a, T b)
	{
		return a < b;
	}
};


template <class T, class C>
class heap
{
public:

	heap()
	{
		nro_elementos = 0;
	}

	T Top()
	{
		return Heap.front();
	}

	void Push(T valor)
	{
		C comp;
		//1 agregamos el elemento en la posicion n+1 (el final del vector)
		Heap.push_back(valor);
		nro_elementos++;
		//2 reubicacion numerica
		int i = nro_elementos - 1;
		while (i > 0)
		{
			int padre = (i - 1) / 2;
			if (comp(Heap[i], Heap[padre]))
			{
				swap(Heap[i], Heap[padre]);
			}
			else
			{
				break;
			}
			i = padre;
		}
	}

	void Pop()
	{
		C comp;
		//1 cmabio el primer elementos con el ultimo
		swap(Heap.front(), Heap.back());
		//2 "elminamos el ultimo elemento, unicamente lo ignoramos XD"
		Heap.pop_back();
		nro_elementos -= 1;
		//3 reubicacion numerica
		int i = 0;

		while (true)
		{
			int izq = i * 2 + 1;
			int der = i * 2 + 2;
			if (izq >= nro_elementos)
			{
				return;
			}
			int Hijo = izq;
			if (der < nro_elementos && comp(Heap[der], Heap[izq]))
			{
				Hijo = der;
			}
			if (comp(Heap[Hijo], Heap[i]))
			{
				swap(Heap[i], Heap[Hijo]);
			}
			else
			{
				break;
			}
			i = Hijo;
		}
	}

	void Print()
	{
		for (int i = 0; i < nro_elementos; i++)
		{
			cout << Heap[i] << " ";
		}
		cout << endl;
	}	

private:
	vector<T> Heap;
	int nro_elementos;
};

int main() 
{
	heap<int, Greater<int>> maxH;

	maxH.Push(5);
	maxH.Push(2);
	maxH.Push(8);
	maxH.Print();
	maxH.Push(7);
	maxH.Print();
	maxH.Pop();
	maxH.Print();

	heap<int, Less<int>> minH;

	minH.Push(5);
	minH.Push(2);
	minH.Push(8);
	minH.Print();
	minH.Push(7);
	minH.Print();
	minH.Pop();
	minH.Print();
}