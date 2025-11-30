#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Greater
{
	bool operator ()(T a, T b)
	{
		return a > b;
	}
};

template <class T>
struct Less
{
	bool operator ()(T a, T b)
	{
		return a < b;
	}
};

template<class T, class C>
class Heap
{
public:
	Heap()
	{
		nro_elem = 0;
	}

	void Push(T valor)
	{
		C comp;
		arbol.push_back(valor);
		nro_elem++;
		int i = nro_elem - 1;
		while (i > 0)
		{
			int padre = (i - 1) / 2;
			if (comp(arbol[i], arbol[padre]))
			{
				swap(arbol[i], arbol[padre]);
				i = padre;
			}
			else
			{
				break;
			}
		}
	}

	void Pop()
	{
		C comp;
		if (arbol.size() > 0)
		{
			swap(arbol.front(), arbol.back());
			arbol.pop_back();
		}
		nro_elem--;
		int i = 0;
		while (true)
		{
			int izq = i * 2 + 1;
			int der = i * 2 + 2;
			if (izq >= nro_elem - 1)
			{
				return;
			}
			int Hijo_mas_util = izq;
			if (der < nro_elem && comp(arbol[izq], arbol[der]))
			{
				Hijo_mas_util = der;
			}
			if (comp(arbol[Hijo_mas_util], arbol[i]))
			{
				swap(arbol[i], arbol[Hijo_mas_util]);
			}
			else
			{
				break;
			}
			i = Hijo_mas_util;
		}
	}

	void Print()
	{
		for (int i = 0; i < nro_elem; i++)
		{
			cout << arbol[i] << " ";
		}
		cout << endl;
	}

private:
	int nro_elem;
	vector<T> arbol;
};

int main()
{
	Heap<int, Greater<int>> maxHeap;
	maxHeap.Push(10);
	maxHeap.Push(1);
	maxHeap.Push(14);
	maxHeap.Push(2);
	maxHeap.Push(0);
	maxHeap.Print();
	maxHeap.Pop();
	maxHeap.Pop();
	maxHeap.Pop();
	maxHeap.Print();
	Heap<int, Less<int>> minHeap;
	minHeap.Push(10);
	minHeap.Push(34);
	minHeap.Push(20);
	minHeap.Push(13);
	minHeap.Push(12);
	minHeap.Print();
	minHeap.Pop();
	minHeap.Pop();
	minHeap.Pop();
	minHeap.Print();

	return 0;
}