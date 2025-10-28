#include <iostream>
#include <deque>

using namespace std;

template <class T,class C>
class CStack: public C
{
public:
	void Push(T x)
	{
		this->push_back(x);
	}
	void Pop()
	{
		this->pop_back();
	}
	T Top()
	{
		return this->back();
	}
};

int main()
{
	CStack<int, deque<int>> s;
	s.Push(3);
}