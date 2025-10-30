#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*template <class U>
U Greater(U a, U b)
{
	return a > b;
}

template <class U>
U Less(U a, U b)
{
	return a < b;
}*/

template <class T, class C>
class heap
{
public:

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
		int i = (nro_elementos - 1) / 2;
		while (Heap.size() > 1)
		{
			if (comp(Heap[i], valor))
				swap(Heap[i], valor);
			else
				swap(valor, valor);
			i = (i - 1) / 2;
		}
	}

	void Pop()
	{
		C comp;
		//1 cmabio el primer elementos con el ultimo
		Heap.swap(Heap.front(), Heap.back());
		//2 "elminamos el ultimo elemento, unicamente lo ignoramos XD"
		nro_elementos -= 1;
		//3 reubicacion numerica
		int* principal = &(Heap.front());
		//hijo "izquierdo"
		int* izq = &(Heap.front() * 2 + 1);
		//Hijo Derecho
		int* der = &(Heap.front() * 2 + 2);
		while (Heap.size() > 1)
		{
			int* guardar = &(C(*izq, *der));
			if (comp(C(*izq,*der), *principal))
				swap(C(*izq, *der), *principal);
			else
				swap(*principal, *principal);
			principal = guardar;
			izq = &(principal * 2 + 1);
			der = &(principal * 2 + 2);
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
	T nro_elementos;
};

int main() 
{
	heap<int, greater<int>(int,int)> maxH;

	maxH.Push(5);
	maxH.Push(2);
	maxH.Push(8);
	maxH.Print();
}