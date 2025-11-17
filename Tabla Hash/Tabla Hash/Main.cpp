#include <iostream>
#include <string>
#include <type_traits>
#include "List.h"

using namespace std;

template<class T>
struct ToInt
{
	int operator()(T x)
	{
		if constexpr (is_same_v<T, int>)
		{
			return x;
		}
		else if constexpr (is_same_v<T, float>)
		{
			return static_cast<int>(x);
		}
		else if constexpr (is_same_v<T, long>)
		{
			return static_cast<int>(x);
		}
		else if constexpr (is_same_v<T, char>)
		{
			return static_cast<int>(x);
		}
		else if constexpr (is_same_v<T, string>)
		{
			int string_int = stoi(x);
			return string_int;
		}
		else
		{
			return 0;
		}
	}
};

template<class T, class Cont, class F, int tam>
class Hash
{
public:
	Hash()
	{
		vectorC = new  Cont[tam];
	}

	void Insert(T x)
	{
		int i = func(x) % tam;
		vectorC[i].InsX(x);
	}

	void Remove(T x)
	{
		int i = func(x) % tam;
		vectorC[i].RemX(x);
	}

	bool FnX(T x)
	{
		int i = func(x) % tam;
		return vectorC[i].FindX(x);
	}

private:
	F func;
	Cont* vectorC;
};

int main()
{
	Hash<int, List<int>, ToInt<int>, 16> ht;
	ht.Insert(8);
	return 0;
}