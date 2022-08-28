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


template <class T>
void printContainer(const T& con)
{
	for(auto iter : con)
	{
		std::cout << iter << ' ';
	}
	std::cout << std::endl;
}

template <class T1,class T2>
void insert_sorted(T1& container, T2&& value)
{
	auto it = std::find_if(std::begin(container), std::end(container), [value](auto containerValue)
						   { return containerValue > value; });
	container.emplace(it, value);
}

int main(int argc, char** argv)
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::vector<int> vec1 = {1, 2, 3, 5, 6, 7, 9};
	printContainer(vec1);

	insert_sorted(vec1, 4);
	printContainer(vec1);

	std::list<int> list1 = {1, 2, 3, 5, 6, 7, 9};
	printContainer(list1);

	insert_sorted(list1, 8);
	printContainer(list1);
	std::cout << std::endl;

	//////////////////////////////////////////////////////
	std::cout << std::endl;

	std::srand(std::time(nullptr));

	std::vector<double> a;
	a.resize(100);
	std::generate(a.begin(), a.end(), []()
				  { double temp = std::rand();
					return temp / 1000 ; });
	printContainer(a);
	std::cout << std::endl;

	std::vector<int> b;
	b.resize(100);
	std::copy(a.begin(), a.end(), b.begin());
	printContainer(b);
	std::cout << std::endl;

	double errorRange = 0;
	std::for_each(a.begin(), a.end(), [&b, &errorRange](auto &value)
				  { static size_t iter = 0;
					errorRange += (value - b.at(iter))*(value - b.at(iter));
					iter++;
					});
	std::cout << "Величина ошибки: " << errorRange;
	std::cout << std::endl;


	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	return 0;
}