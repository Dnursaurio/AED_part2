#ifndef LIST_H
#define LIST_H
#include <list>

using namespace std;

template<class T>
class List : public list<T>
{
public:
	bool FindX(const T& x)
	{
		typename list<T>::iterator finder = this->begin();
		for (; finder != this->end() && *finder != x; finder++);
		return finder != this->end();
	}
	bool InsX(const T& x)
	{
		if (!FindX(x))
		{
			this->push_back(x);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool RemX(const T& x)
	{
		if (FindX(x))
		{
			this->remove(x);
			return 1;
		}
		else
		{ 
			return 0;
		}
	}
};

#endif // !LIST_H