#include <iostream>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>


template <class T>
void PrintUniq(T begin, T end)
{
	std::set<std::string> temp;
	temp.insert(begin, end);
	for(auto iter : temp)
	{
		std::cout << iter << std::endl;
	}
	temp.clear();
}

int main(int argc, char** argv)
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::vector<std::string> str1 = {"А","я","иду","А", "шагаю","А", "по", "москве"};
	PrintUniq(str1.begin(), str1.end());
	std::cout << std::endl;

	std::list<std::string> str2 = {"А","я","иду","А", "шагаю","А", "по", "москве"};
	PrintUniq(str2.begin(), str2.end());

	std::multimap<int, std::string> notes;
	std::string str3 = "";

	std::cout << "\n\n Нажмите \"End\" и \"Enter\" для прекращения ввода" << std::endl;

	while (!GetKeyState(VK_END))
	{
		getline(std::cin, str3);
		
		if(str3.size())
		{
			str3.erase(std::unique(str3.begin(), str3.end(), [](auto ch1, auto ch2)
								   { return ch1 == ' ' && ch2 == ' '; }),
					   str3.end());
			if(*(str3.begin()) == ' ')
			{
				str3 = std::string(++str3.begin(), str3.end());
			}
			if(*(--str3.end()) == ' ')
			{
				str3.pop_back();
			}

			notes.insert(std::make_pair(std::count_if(str3.begin(), str3.end(), [](auto ch)
												  { return ch == ' '; }) +
										1,
									str3));
		}
		str3 = "";
	}

	for(auto iter : notes)
	{
		std::cout << iter.second << " | Количество слов: " << iter.first << std::endl;
	}


	SetConsoleCP(866);
	SetConsoleOutputCP(866);
	return 0;
}