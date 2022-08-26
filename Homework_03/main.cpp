#include <iostream>
#include <list>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <tuple>
#include <algorithm>
#include <windows.h>

void Middle(std::list<double> &list)
{
	double temp = .0;
	for(auto iter : list)
	{
		temp += iter;
	}
	list.push_back(temp / list.size());
}

////////////////////////////////////////////////////////////////////////

template <class T>
class Matrix
{
private:
	std::vector<std::vector<T>> mat;
public:
	Matrix(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3)
	{
			this->mat.push_back(std::vector<T>{a1,a2,a3});
			this->mat.push_back(std::vector<T>{b1,b2,b3});
			this->mat.push_back(std::vector<T>{c1,c2,c3});
	}
	T GetDeterminant()
	{
		T determinant = 0;
		for (size_t iter = 0; iter < 3; iter++)
		{
			determinant += mat[0][iter] * mat[1][(iter + 1) % 3] * mat[2][(iter + 2) % 3];
		}
		for (size_t iter = 0; iter < 3; iter++)
		{
			determinant -= mat[0][(iter + 2) % 3] * mat[1][(iter + 1) % 3] * mat[2][iter];
		}
		return determinant;
	}
};

///////////////////////////////////////////////////////////////////////////

class MyIter
{
public:
	MyIter(){};
	MyIter(int &val) { Ptr = &val; };
	int operator*() { return *Ptr; }
	void operator=(int val) { *Ptr = val; }
	void operator++() { Ptr++; }
	void operator--() { Ptr--; }

private:
	int *Ptr;
};



int main(int argc, char** argv)
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::list<double> list;
	list.push_back(0.5);
	list.push_back(0.7);

	Middle(list);
	std::cout << std::fixed;
	std::cout.precision(50);
	std::cout << list.back() << std::endl;
	std::cout << std::endl;

	////////////////////////////////

	Matrix m(1, 2, 2, 4, 5, 4, 7, 8, 9);

	std::cout << m.GetDeterminant() << std::endl;
	std::cout << std::endl;

	///////////////////////////////

	int Arr[5] = { 0, 5, 7, 9, 10 };
	MyIter it = *std::end(Arr);
	--it;
	std::cout << *it << " ";
	--it;
	std::cout << *it << " ";
	std::cout << std::endl;

	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	return 0;
}