#include <iostream>

using namespace std;

struct Cola
{
	int arr[10] = {};
	int* head = nullptr;
	int* tail = NULL;
	int nro_elem = 0;

	bool lleno()
	{
		return nro_elem == 10;
	}

	bool vacio()
	{
		return nro_elem == 0;
	}

	bool push(int x)
	{
		if (lleno())
		{
			cout << "cola llena" << endl;
			return 0;
		}
		else
		{
			if (!head)
			{
				head = arr;
				tail = head;
			}
			else
			{
				if (tail == arr + 9 && head > arr)
				{
					tail = arr;
				}
				else
				{
					tail++;
				}				
			}
			*tail = x;
			nro_elem++;
			return 1;
		}
	}

	bool pop(int& x)
	{
		if (vacio())
		{
			cout << "cola vacia" << endl;
			return 0;
		}
		else
		{
			x = *head;
			if (head == arr + 9 && tail > arr)
			{
				head = arr;
			}
			else
			{
				head++;
			}
			nro_elem--;
			if (nro_elem == 0)
			{
				head = NULL;
				tail = NULL;
			}
		}
	}

	void print()
	{
		if (head <= tail)
		{
			for (int* i = head; i <= tail; i++)
			{
				cout << *i << " ";
			}
			cout << endl;
		}
		if (tail < head)
		{
			for (int* i = head; i < arr + 9; i++)
			{
				cout << *i << " ";
			}
			for (int* i = arr; i <= tail; i++)
			{
				cout << *i << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	cout << "-------------------------Cola Circular-------------------------" << endl;
	Cola c;
	int a;
	cout << "agregando elementos con push()" << endl;
	c.push(3);	c.print();
	c.push(5);	c.print();
	c.push(2);	c.print();
	c.push(13);	c.print();
	c.push(23);	c.print();
	c.push(33);	c.print();
	c.push(43);	c.print();
	c.push(53);	c.print();
	c.push(63);	c.print();
	c.push(73);	c.print();
	cout << "eliminando elementos con pop()" << endl;
	c.pop(a);	c.print();
	c.pop(a);	c.print();
	c.pop(a);	c.print();
	cout << "probando circularidad" << endl;
	c.push(8);	c.print();
	c.push(5);	c.print();
	c.push(4);	c.print();
	cout << "---------------------------------------------------------------" << endl;
}