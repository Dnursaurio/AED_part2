#include <assert.h>
#include <iostream>

using namespace std;

class CVector
{
public:
	CVector(int size);
	~CVector();
	void expandir();
	void contraer();
	void push_front(int x);
	void push_back(int x);
	void pop_front();
	void pop_back();
	int& operator[](int i);
	void print();

private:
	int* vector;
	int nro_elem;
	int tam;
};

CVector::CVector(int size)
{
	tam = size;
	vector = new int[tam];
	nro_elem = 0;
}

CVector::~CVector()
{
	delete vector;
}

void CVector::expandir()
{
	int* nuevo_vector = new int[tam * 2];
	for (int i = 0; i < tam; i++)
	{
		nuevo_vector[i] = vector[i];
	}
	delete [] vector;
	vector = nuevo_vector;
	tam = 2 * tam;
}

void CVector::contraer()
{
	int* nuevo_vector = new int[tam / 2];
	for (int i = 0; i < nro_elem; i++)
	{
		nuevo_vector[i] = vector[i];
	}
	delete [] vector;
	vector = nuevo_vector;
	tam = tam / 2;
}

void CVector::push_front(int x)
{
	if (nro_elem == tam)
	{
		expandir();
	}
	for (int i = tam - 1; i > 0; i--)
	{
		vector[i] = vector[i - 1];
	}
	vector[0] = x;
	nro_elem++;
}

void CVector::push_back(int x)
{
	if (nro_elem == tam)
	{
		expandir();
	}
	vector[nro_elem] = x;
	nro_elem++;
}

void CVector::pop_front()
{
	if (nro_elem == tam / 2)
	{
		contraer();
	}
	for (int i = 0; i < nro_elem; i++)
	{
		vector[i] = vector[i + 1];
	}
	nro_elem--;
	
}

void CVector::pop_back()
{
	if (nro_elem == tam / 2)
	{
		contraer();
	}
	nro_elem--;
}

int& CVector::operator[](int i)
{
	return vector[i];
}

void CVector::print()
{
	for (int i = 0; i < nro_elem; i++)
	{
		cout << vector[i] << " ";
	}
}

int main()
{
	CVector vector(3);
	vector.push_back(12);
	vector.push_front(90);
	vector.push_front(2);
	vector.push_front(1);
	vector.push_back(41);
	vector.push_back(40);
	vector.push_back(43);
	vector.push_front(44);
	vector.print();

	return 0;
}