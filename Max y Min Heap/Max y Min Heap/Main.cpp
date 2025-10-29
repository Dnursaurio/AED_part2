#include <iostream>
#include <vector>

using namespace std;

template <class T>
T Greater(T a, T b)
{
	return a > b;
}

template <class T>
T Less(T a, T b)
{
	return a < b;
}

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
		//1 agregamos el elemento en la posicion n+1 (el final del vector)
		Heap.push_back(valor);
		nro_elementos++;
		//2 reubicacion numerica
		int i = (nro_elementos - 1) / 2;
		while (Heap.size() > 1)
		{
			C(Heap[i], valor) ? swap(Heap[i], valor) : break;
			i = (i - 1) / 2;
		}
	}

	void Pop()
	{
		//1 cmabio el primer elementos con el ultimo
		swap(heap.top(), Heap[nro_elementos - 1]);
		//2 "elminamos el ultimo elemento, unicamente lo ignoramos XD"
		nro_elementos -= 1;
		//3 reubicacion numerica
		int principal = heap.top();
		//hijo "izquierdo"
		int* izq = &(heap.top() * 2 + 1);
		//Hijo Derecho
		int* der = &(heap.top() * 2 + 2);
		while (Heap.size() > 1)
		{
			C(principal, C(*izq, *der)) ? swap(principal, C(*izq, *der)) : break;

		}
	}
private:
	vector<T> Heap;
	T nro_elementos;
};

int main() 
{
	
}