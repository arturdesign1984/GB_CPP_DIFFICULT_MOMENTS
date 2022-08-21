#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <tuple>
#include <algorithm>
#include <windows.h>
#include "Timer.h"

template<class T>
void Swap(T &&t1, T &&t2)
{
	auto temp = t1;
	t1 = t2;
	t2 = temp;
}

template<class T>
void SortPointers(std::vector<T> &vecT)
{
	std::sort(vecT.begin(), vecT.end(), [](const T &t1, const T &t2)
			  { return *t1 < *t2; });
}

int main(int argc, char** argv)
{
////// 1

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int a = 1, b = 2;
	int *ap = &a, *bp = &b;
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "ap = " << ap << ", bp = " << bp << std::endl;

	Swap(ap, bp);
	std::cout << "Swap" << std::endl;
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "*ap = " << *ap << ", *bp = " << *bp << std::endl;
	std::cout << "ap = " << ap << ", bp = " << bp << '\n' << std::endl;

/////// 2

	std::vector<int> vec = {5, 1, 3, 4, 8, 6, 7, 2, 9};
	std::vector<int *> vecP;
	for (auto iter = 0; iter < vec.size(); iter++)
	{
		vecP.push_back(&vec[iter]);
	}

	for(auto iter : vecP)
	{
		std::cout << *iter << " ";
	}

	SortPointers(vecP);
	std::cout << "\nSortPointers" << std::endl;
	for(auto iter : vecP)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

////// 3

	std::string buffer, book, vowelLetters = {"АаУуОоЫыИиЭэЯяЮюЁёЕеAaàEeèéêIiOoôUuûYy"};

	int count = 0;
	std::fstream file;
	file.open("voina-i-mir.txt");

	if(file.is_open())
	{
		std::cout << "\nФайл открыт." << std::endl;
		for (std::getline(file, buffer); !file.eof(); std::getline(file, buffer))
		{
			book += buffer;
		}
		buffer = "";
		buffer.shrink_to_fit();
	}else
	{
		std::cout << "Файл не открыт!" << std::endl;
	}
	file.close();

///// 3.1

	auto start = std::chrono::steady_clock::now();
	count = std::count_if(book.begin(), book.end(), [&vowelLetters](const auto ch)
						   { return std::find(vowelLetters.begin(), vowelLetters.end(), ch) != vowelLetters.end(); });
	std::cout << std::endl << "Количество гласных = " << count << std::endl;
	count = 0;

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> seconds = end - start;
	std::cout << "count_if и find = " << seconds.count() << "s" << std::endl;

///// 3.2

	start = std::chrono::steady_clock::now();
	count = std::count_if(book.begin(), book.end(), [&vowelLetters](const auto ch)
						{ for(auto iter : vowelLetters)
							{
								if(iter == ch)
								{
									return true;
								}
							}
							return false;
						});
	std::cout << std::endl << "Количество гласных = " << count << std::endl;
	count = 0;

	end = std::chrono::steady_clock::now();
	seconds = end - start;
	std::cout << "count_if и цикл for = " << seconds.count() << "s" << std::endl;

///// 3.3

	start = std::chrono::steady_clock::now();
	for(auto iter : book)
	{
		if(std::find(vowelLetters.begin(), vowelLetters.end(), iter) != vowelLetters.end())
		{
			count++;
		}
	}
	count = std::count_if(book.begin(), book.end(), [&vowelLetters](const auto ch)
						   { return std::find(vowelLetters.begin(), vowelLetters.end(), ch) != vowelLetters.end(); });
	std::cout << std::endl << "Количество гласных = " << count << std::endl;
	count = 0;

	end = std::chrono::steady_clock::now();
	seconds = end - start;
	std::cout << "цикл for и find = " << seconds.count() << "s" << std::endl;

/////3.4

	start = std::chrono::steady_clock::now();
	for(auto iter1 : book)
	{
		for (auto iter2 : vowelLetters)
		{
			if(iter1 == iter2)
			{
				count++;
				break;
			}
		}
	}
	std::cout << std::endl << "Количество гласных = " << count << std::endl;

	end = std::chrono::steady_clock::now();
	seconds = end - start;
	std::cout << "2 цикла for = " << seconds.count() << "s" << std::endl;

	book = "";
	book.shrink_to_fit();

	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	return 0;
}