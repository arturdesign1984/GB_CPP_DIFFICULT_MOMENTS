#include "MyNamespace.h"

int main(int argc, char** argv)
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::vector<int> aver1{50,100,88,75,64,92};
	std::vector<int> aver2{84,16,85,37,61,52,65,95,13,48,6,26,9};
	MyNamespace::StudentsGroup group1("Антонов", "Антон", "Антонович", aver2);
	group1.addStudent("Сергеев", "Сергей", aver2);
	std::cout << "\tgroup1.GetAllInfo() :\n\n";
	std::cout << group1.GetAllInfo();
	MyNamespace::StudentsGroup group2;
	std::cout << "\tgroup2.GetAllInfo() :  // Должно быть пусто\n\n";
	std::cout << group2.GetAllInfo();
	std::cout << "\tSave group1 & Open group2\n\tgroup2.GetAllInfo() :\n\n";
	group1.Save();
	group2.Open();
	std::cout << group2.GetAllInfo();
	std::cout << "\tgroup2.GetAllInfo(MyNamespace::FullName(\"Сергеев\", \"Сергей\")) :\n\n";
	std::cout << group2.GetAllInfo(MyNamespace::FullName("Сергеев", "Сергей"));
	
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	return 0;
}