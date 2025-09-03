#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
	Node(int val)
	{
		valor = val;
		next = nullptr;
	}

	int valor;
	Node* next;
};

class CForwardList
{
public:
	CForwardList();
	~CForwardList();
	void push_front(int x);
	void pop_front();
	void push_back(int x);
	void pop_back();
	int& operator[](int i);
	void print();
private:
	Node* head;
	int nro_elem;
};

CForwardList::CForwardList()
{
	head = NULL;
	nro_elem = 0;
}

//hacer luego el destructor
CForwardList::~CForwardList()
{
	Node* borrador = head;
	while (borrador)
	{
		borrador = borrador->next;
		delete head;
		head = borrador;
	}
}

void CForwardList::push_front(int x)
{
	Node* n = new Node(x);
	n->next = head;
 	head = n;
	nro_elem++;
}

void CForwardList::push_back(int x)
{
	Node* n = new Node(x);
	Node** ptr = &head;
	for (ptr; *ptr != NULL; ptr = &(*ptr)->next);
	*ptr = n;
	nro_elem++;
}

void CForwardList::pop_front()
{
	Node* borrador = head;
	head = head->next;
	delete[] borrador;
	nro_elem--;
}

void CForwardList::pop_back()
{
	Node** p = &head;
	for (p;p != NULL && (*p)->next != NULL; p = &(*p)->next);
	delete* p;
	*p = NULL;
	nro_elem--;
	p = NULL;
}

int& CForwardList::operator[](int i)
{
	assert(i < nro_elem);
	Node* n = head;
	for (int j = 0; j < i; j++)
	{
		n = n->next;
	}
	return  n->valor;
}

void CForwardList::print()
{
	Node* printer;
	for (printer = head; printer != NULL; printer = printer->next)
	{
		cout << printer->valor << " -> ";
	}
	cout << "//";
	cout << "	nro_elem: " << nro_elem;
	cout << endl;
}

int main()
{
	cout << "--------------------------------Forward List--------------------------------" << endl;
	CForwardList fl;
	cout << "agragando elementos con push_front y push_back" << endl;
	fl.push_front(3);	fl.print();
	fl.push_back(14);	fl.print();
	fl.push_back(16);	fl.print();
	fl.push_front(41);	fl.print();
	cout << "eliminando elementos con pop_front y pop_back()" << endl;
	fl.pop_back();		fl.print();
	fl.pop_front();		fl.print();
	cout << "acceciendo a elementos con el operador []" << endl;
	fl[1] = 2;	fl.print();
	fl[0] = 21;	fl.print();
	cout << "agregando un elemento mas" << endl;
	fl.push_back(13);	fl.print();
	cout << "----------------------------------------------------------------------------" << endl;
}