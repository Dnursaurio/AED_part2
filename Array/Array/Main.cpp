#include <assert.h>
#include <iostream>

using namespace std;

class CArray
{
public:
	CArray(int tam)
	{
		//construimos un array de tamaño size (este sera estatico)
		size = tam;
		ini = new int[size];
		nro_elem = 0;
	}
	~CArray()
	{
		delete ini;
	}
	void push_front(int x);
	void push_back(int x);
	void pop_front();
	void pop_back();
	int& operator[](int i);
	void print();
private:
	int nro_elem;
	int size;
	int* ini;
};

void CArray::push_front(int x)
{
	assert(nro_elem != size);
	for (int i = nro_elem; i > 0; i--)
	{
		ini[i] = ini[i - 1];
	}
	ini[0] = x;
	nro_elem++;
}

void CArray::push_back(int x)
{
	assert(nro_elem != size);
	ini[nro_elem] = x;
	nro_elem ++;
}

void CArray::pop_front()
{
	assert(nro_elem != 0);
	for (int i = 0; i < nro_elem; i++)
	{
		ini[i] = ini[i + 1];
	}
	nro_elem--;
}

void CArray::pop_back()
{
	assert(nro_elem != 0);
	nro_elem--;
}

int& CArray::operator[](int i)
{
	assert(i < nro_elem);
	return ini[i];
}

void CArray::print()
{
	for (int i = 0; i < nro_elem; i++)
	{
		cout << ini[i] << " ";
	}
	cout << endl;
}

int main()
{
	CArray arr(5);

	cout << "------------------------Array------------------------" << endl;
	cout << "agregando elementos con push_front y push_back" << endl;
	arr.push_front(7);	arr.print();
	arr.push_back(18);	arr.print();
	arr.push_back(5);	arr.print();
	arr.push_front(20);	arr.print();
	arr.push_back(16);	arr.print();
	cout << "quitando elementos con pop_front y pop_back" << endl;
	arr.pop_front();	arr.print();
	arr.pop_back();		arr.print();
	cout << "modificando elementos con el operador []" << endl;
	arr[2] = 0;			arr.print();
	cout << "-----------------------------------------------------" << endl;

	return 0;
}