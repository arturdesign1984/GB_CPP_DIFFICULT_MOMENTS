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
// #include "Timer.h"

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
	size_t matrixSize = 0;
	std::vector<std::vector<double>> mat;
public:
	Matrix(){}
	Matrix(size_t matrixSize, std::vector<T>& vec) : matrixSize(matrixSize)
	{
		for (size_t iter1 = 0; iter1 < matrixSize; iter1++)
		{
			std::vector<double> temp;
			for(size_t iter2 = 0; iter2 < matrixSize; iter2++)
			{
				temp.push_back((double)vec[iter1*matrixSize+iter2]);
			}
			this->mat.push_back(temp);
			temp.clear();
		}
	}
	T GetDeterminant()
	{
		double multiplier = .0;
		std::vector<std::vector<double>> temp(mat);
		for (size_t iter1 = 1,iter2 = 0; iter1 < matrixSize; iter1++,iter2++)
		{
			for (size_t iter4 = iter1; iter4 < matrixSize; iter4++)
			{
				multiplier = temp[iter4][iter2] / temp[iter1 - 1][iter2];
				for (size_t iter3 = 0; iter3 < matrixSize; iter3++)
				{
					temp[iter4][iter3] = temp[iter4][iter3] - temp[iter1 - 1][iter3] * multiplier;
				}
			}
		}
		double result = temp[0][0];
		for (size_t i = 1; i < matrixSize; i++)
		{
			result *= temp[i][i];
		}
		return (T)result;
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

	std::vector vec1 = {2.,2.,2.,0.,3.,5.,5.,3.,1.,3.,2.,0.,1.,0.,3.,2.};
	Matrix m1(4, vec1);

	std::cout.precision(2);
	std::cout << m1.GetDeterminant() << std::endl;
	std::cout << std::endl;

	std::vector vec2 = {2.,2.,2.,0.};
	Matrix m2(2, vec2);

	std::cout << m2.GetDeterminant() << std::endl;
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