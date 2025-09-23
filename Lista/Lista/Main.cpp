#include <iostream>

using namespace std;

struct Node
{
	Node(int valor)
	{
		v = valor;
		next = nullptr;
		prev = nullptr;
	}
	Node* next;
	Node* prev;
	int v;
};

class CList
{
public:
	CList()
	{
		head = nullptr;
		tail = nullptr;
		nro_elem = 0;
	}
	void push_front(int x)
	{
		Node* n = new Node(x);
		n->next = head;
		head == nullptr ? n->prev = nullptr : head->prev = n;
		tail == nullptr ? tail = n : tail = tail;
		head = n;
		nro_elem++;
	}
	void push_back(int x)
	{
		Node* n = new Node(x);
		n->prev = tail;
		head == nullptr ? head = n : head = head;
		tail == nullptr ? n->next = nullptr : tail->next = n;
		tail = n;
		nro_elem++;
	}
	void pop_front()
	{
		Node* n = head->next;
		head->next = NULL;
		n->prev = NULL;
		delete head;
		head = n;
		nro_elem--;
	}
	void pop_back()
	{
		Node* n = tail->prev;
		tail->prev = NULL;
		n->next = NULL;
		delete tail;
		tail = n;
		nro_elem--;
	}
	int& operator[](int i)
	{
		Node* ptr = head;
		for (int o = 0; o < i; o++)
		{
			ptr = ptr->next;
		}
		return ptr->v;
	}
	void print()
	{
		cout << "NULL <-> ";
		for (Node* i = head; i; i = i->next)
		{
			cout << i->v << " <-> ";
		}
		cout << "NULL	" << "nro_elem: " << nro_elem << endl;
	}
private:
	Node* head;
	Node* tail;
	int nro_elem;
};

int main()
{
	cout << "-----------------------------Lista-----------------------------" << endl;
	CList l;
	cout << "agregando elementos con push_front y push_back" << endl;
	l.push_front(3);	l.print();
	l.push_front(4);	l.print();
	l.push_front(5);	l.print();
	l.push_back(10);	l.print();
	cout << "eliminando elementos con pop_front y pop_back" << endl;
	l.pop_front();		l.print();
	l.pop_back();		l.print();
	cout << "modificando elementos con el operador []" << endl;
	l[0] = 1;			l.print();
	cout << "---------------------------------------------------------------" << endl;

	return 0;
}