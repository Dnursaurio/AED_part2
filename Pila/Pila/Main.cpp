#include <iostream>

using namespace std;

template <class T>
struct Stack
{
	T arr[10] = {};
	T* top = NULL;

	bool lleno()
	{
		return top == arr + 9;
	}
	bool vacio()
	{
		return !top;
	}
	bool push(T a)
	{
		if (lleno())
		{
			cout << "pila llena" << endl;
			return 0;
		}
		else
		{
			if (!top)
			{
				top = arr;
			}
			else
			{
				top++;
			}
			*top = a;
			return 1;
		}
	}
	bool pop(T& a)
	{
		if (vacio())
		{
			cout << "pila vacia" << endl;
			return 0;
		}
		else
		{
			a = *top;
			top--;
			if (top < arr)
			{
				top = NULL;
			}
			return 1;
		}
	}
	void print()
	{
		for (T* i = arr; i < arr + 10; i++)
		{
			cout << *i << " ";
		}
		cout << endl;
	}
};

int main()
{
	cout << "---------------------Pila---------------------" << endl;
	Stack<int> pila;
	int a;
	cout << "agregando elementos con push()" << endl;
	pila.push(16);	pila.print();
	pila.push(18);	pila.print();
	pila.push(11);	pila.print();
	pila.push(14);	pila.print();
	pila.push(17);	pila.print();
	cout << "eliminando elementos con pop()" << endl;
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	cout << "excediendo elementos" << endl;
	pila.push(26);	pila.print();
	pila.push(28);	pila.print();
	pila.push(21);	pila.print();
	pila.push(24);	pila.print();
	pila.push(27);	pila.print();
	pila.push(30);	pila.print();
	pila.push(35);	pila.print();
	pila.push(37);	pila.print();
	pila.push(47);	pila.print();
	pila.push(48);	pila.print();
	cout << "excediendo al vacio" << endl;
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	pila.pop(a);	pila.print();
	cout << "rellenando pa que veas qe si es cierto" << endl;
	pila.push(1);	pila.print();
	cout << "----------------------------------------------" << endl;
}