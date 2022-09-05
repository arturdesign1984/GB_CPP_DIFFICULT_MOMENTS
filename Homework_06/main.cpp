#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <cmath>
#include <windows.h>

std::mutex mutexPcout;
template<class T>
void pcout(T value, size_t &&color = 15)
{
	mutexPcout.lock();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << value << ' ';
	SetConsoleTextAttribute(hConsole, 15);
	mutexPcout.unlock();
}

void func1()
{
	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pcout(i, 10);
	}
}

void func2()
{
	for (int i = 10; i < 20; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pcout(i, 14);
	}
}

void func3()
{
	for (int i = 20; i < 30; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pcout(i, 10);
	}
}

///////////////////////////////////////////////////////////////


bool isPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
return true;
}

int primeNombers(int n)
{
	if(n == 2 || n == 3)
	{
		return n;
	}
	int result = 3;
	for (int i = 3; i <= n; i++)
	{
		for(++result; !isPrime(result); result++)
		{}
	}
	return result;
}

////////////////////////////////////////////////////

std::mutex humanMutex;
std::mutex thiefMutex;
void human(std::vector<int> &vec)
{
	auto key = GetKeyState(VK_ESCAPE);
	while(key == GetKeyState(VK_ESCAPE))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::scoped_lock L{humanMutex, thiefMutex};
		srand(time(NULL));
		vec.push_back(rand()%100);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD {0, 0});
		for(auto iter : vec)
		{
			std::cout << iter << ' ';
		}
		std::cout << "     ";
	}
}

void thief(std::vector<int> &vec)
{
	auto key = GetKeyState(VK_ESCAPE);
	while(key == GetKeyState(VK_ESCAPE))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::scoped_lock L{humanMutex, thiefMutex};
		if(!vec.empty())
		{
			vec.erase(std::max_element (vec.begin(), vec.end()));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD {0, 0});
			for(auto iter : vec)
			{
				std::cout << iter << ' ';
			}
			std::cout << "     ";
		}
	}
}

int main(int argc, char** argv)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	system("cls");
	SetConsoleCursorPosition(hConsole,coord = {0, 4});
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::mutex m1;
	m1.lock();
	std::thread t2(func2);
	std::thread t1(func1);
	t1.join();
	t2.join();
	m1.unlock();

	//////////////////////////////////////////////

	int nomber = 1000;
	int result = 0;
	while(m1.try_lock())
	{}
	std::mutex m2;
	std::lock_guard lgd(m2);
	{
		std::thread t3([&,nomber]()
					{ result = primeNombers(nomber);
					});
		t3.join();
		std::cout << "\n " << nomber << "-е простое число: " << result << std::endl;
	}

	//////////////////////////////////////////////
	
	while(m2.try_lock())
	{}
	SetConsoleCursorPosition(hConsole,coord = {0, 2});
	std::cout << " Нажмите ESC для завершения...";
	std::vector<int> things = {1,100,200,52,11,95,216,2,3};
	std::thread t4(human, std::ref(things));
	std::thread t5(thief, std::ref(things));
	t4.join();
	t5.join();

	SetConsoleCursorPosition(hConsole,coord = {0, 2});
	system("pause");
	system("cls");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	return 0;
}