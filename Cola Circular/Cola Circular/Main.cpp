#include <iostream>

using namespace std;

struct Cola
{
	int arr[10] = {};
	int* head = nullptr;
	int* tail = NULL;

	bool lleno()
	{
		if (!head && !tail)
		{
			return 0;
		}
		int* next = tail + 1;
		if (next == arr + 10)
		{
			next = arr;
		}

		return next == head;
	}

	bool vacio()
	{
		return !head && !tail;
	}

	bool push(int x)
	{
		if (lleno())
		{
			cout << "cola llena" << endl;
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
				tail++;
				if (tail == arr + 10)
				{
					tail = arr;
				}				
			}
			*tail = x;
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
		x = *head;
		if (tail == head)
		{
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			head++;
			if (head == arr + 10)
			{
				head = arr;
			}
		}
		return 1;
	}

	void print()
	{
		if (vacio())
		{
			cout << "cola vacia" << endl;
			return;
		}
		int* i = head;
		while (true)
		{
			cout << *i << " ";
			if (i == tail) break;

			i++;
			if (i == arr + 10) i = arr; // wrap-around
		}
		cout << endl;
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