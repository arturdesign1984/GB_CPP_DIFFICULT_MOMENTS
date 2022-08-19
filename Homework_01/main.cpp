#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <tuple>
#include <algorithm>
#include <windows.h>


// #define DEBUG

enum Pers
{
	SURNAME,
	NAME,
	PATRONYMIC
};

class Person
{
	private:
		std::string surname, name;
		std::optional<std::string> patronymic;
	public:
	Person(){}
	Person(std::string surname, std::string name, std::optional<std::string> patronymic) : surname(surname), name(name), patronymic(patronymic) {}
	Person(std::string &&personData)
	{
		size_t separator = SURNAME;
		std::string temp = "";
		for(auto iter : personData)
		{
			if(iter == ' ')
			{
				switch(separator)
				{
					case (SURNAME):
						this->surname = temp;
						temp = "";
						break;
					case (NAME):
						this->name = temp;
						temp = "";
						break;
				}
				separator++;
			}else
			{
				temp.push_back(iter);
			}
		}
		if(separator == NAME && !temp.empty())
		{
			this->name = temp;
			temp = "";
			temp.shrink_to_fit();
			separator++;
		}
		if(separator == PATRONYMIC && !temp.empty())
		{
			this->patronymic = temp;
			temp = "";
			temp.shrink_to_fit();
		}else
		{
			this->patronymic = std::nullopt;
		}
	}
	~Person()
	{
		this->name = "";
		this->name.shrink_to_fit();
		this->surname = "";
		this->surname.shrink_to_fit();
		this->patronymic = "";
		this->patronymic.reset();
	}
	friend bool operator<(const Person &p1, const Person &p2);
	friend bool operator==(const Person &p1, const Person &p2);
	friend std::ostream &operator<<(std::ostream &os, const Person &p);
};
bool operator<(const Person &p1, const Person &p2)
{
	return std::tie(p1.surname, p1.name, p1.patronymic) < std::tie(p2.surname, p2.name, p2.patronymic);
}
bool operator==(const Person &p1, const Person &p2)
{
	if(p2.name.empty())
	{
		return p1.surname == p2.surname;
	}
	return std::tie(p1.surname, p1.name, *p1.patronymic) == std::tie(p2.surname, p2.name, *p2.patronymic);
}
std::ostream &operator<<(std::ostream &os, const Person &p)
{
	os << std::right << std::setw(15 + (p.surname.size()/2)) << p.surname << std::right << std::setw(15+(p.name.size()/2)) << p.name << '\t';
	if(p.patronymic)
	{
		os << std::setw(15+((*p.patronymic).size()/2)) << *(p.patronymic) << "\t\t";
	}else
	{
		os << "\t\t\t";
	}
	return os;
}

enum Phone
{
	COUNTRY,
	CITY,
	NOMBER,
	ADDNOMBER
};

class PhoneNumber
{
	private:
		int country, city;
		std::string nomber;
		std::optional<int> additionalNumber;
	public:
	PhoneNumber(){}
	PhoneNumber(int country, int city, std::string nomber, std::optional<int> additionalNumber) : 
			country(country), city(city), nomber(nomber), additionalNumber(additionalNumber) {}
	PhoneNumber(std::string &&nomberData)
	{
		size_t separator = COUNTRY;
		std::string temp = "";
		for(auto iter : nomberData)
		{
			if(iter == '(' || iter == ')' || iter == ' ')
			{
				switch (separator)
				{
					case (COUNTRY):
						this->country = std::atoi(temp.c_str());
						temp = "";
						break;
					case (CITY):
						this->city = std::atoi(temp.c_str());
						temp = "";
						break;
					case (NOMBER):
						this->nomber = temp;
						temp = "";
						break;
				}
				separator++;
			}else
			{
				temp.push_back(iter);
			}
		}
		if (separator == NOMBER && !temp.empty())
		{
			this->nomber = temp;
			temp = "";
			temp.shrink_to_fit();
			separator++;
		}
		if (separator == ADDNOMBER && !temp.empty())
		{
			this->additionalNumber = std::atoi(temp.c_str());
			temp = "";
			temp.shrink_to_fit();
		}else
		{
			this->additionalNumber = std::nullopt;
		}
	}
	friend bool operator<(const PhoneNumber &p1, const PhoneNumber &p2);
	friend bool operator==(const PhoneNumber &p1, const PhoneNumber &p2);
	friend std::ostream &operator<<(std::ostream &os, const PhoneNumber &p);
};
bool operator<(const PhoneNumber &p1, const PhoneNumber &p2)
{
	return std::tie(p1.country, p1.city, p1.nomber, *p1.additionalNumber) < std::tie(p2.country, p2.city, p2.nomber, *p2.additionalNumber);
}
bool operator==(const PhoneNumber &p1, const PhoneNumber &p2)
{
	return std::tie(p1.country, p1.city, p1.nomber, *p1.additionalNumber) == std::tie(p2.country, p2.city, p2.nomber, *p2.additionalNumber);
}
std::ostream &operator<<(std::ostream &os, const PhoneNumber &p)
{
	os << "+" << p.country << "(" << p.city << ")" << p.nomber;
	if(p.additionalNumber)
	{
		os << " " << *p.additionalNumber;
	}
	return os;
}

class PhoneBook
{
	private:
		std::vector<std::pair<Person, PhoneNumber>> phoneBook;
	public:
	PhoneBook(){}
	PhoneBook(std::ifstream &filePhoneBook){
		std::string temp;
		while(!filePhoneBook.eof())
		{
			std::getline(filePhoneBook, temp);
			
			phoneBook.push_back(std::pair<Person, PhoneNumber>(std::string(temp.substr(0, temp.find('+') - 1)), std::string(temp.substr(temp.find('+') + 1, ((temp.size() - 1)-temp.find('+'))))));
		}
		auto i = temp.substr(0, temp.find('+') - 2);
	}
	friend std::ostream &operator<<(std::ostream &os, const PhoneBook &pb);
	void SortByName()
	{
		std::sort(phoneBook.begin(), phoneBook.end(), [](const std::pair<Person, PhoneNumber> &a, const std::pair<Person, PhoneNumber> &b)
				  { return a.first < b.first; });
	}
	void SortByPhone()
	{
		std::sort(phoneBook.begin(), phoneBook.end(), [](const std::pair<Person, PhoneNumber> &a, const std::pair<Person, PhoneNumber> &b)
				  { return a.second < b.second; });
	}
	std::tuple<std::string, PhoneNumber> GetPhoneNumber(std::string targetSurname)
	{
		std::vector<std::vector<std::pair<Person, PhoneNumber>>::iterator> personsFound;
		for (auto iter = phoneBook.begin(); iter != phoneBook.end(); iter++)
		{
			if((*iter).first == Person(targetSurname,"",std::nullopt))
			{
				personsFound.push_back(iter);
			}
		}
		if(!personsFound.empty())
		{
			if(personsFound.size() > 1)
			{
				return std::make_tuple("found more than 1", PhoneNumber(0,0,"000",std::nullopt));
			}
			return std::tie("", (*personsFound[0]).second);
		}
		return std::make_tuple("not found", PhoneNumber(0,0,"000",std::nullopt));
	}
	void ChangePhoneNumber(Person per, PhoneNumber pn)
	{
		for (auto iter = phoneBook.begin(); iter != phoneBook.end(); iter++)
		{
			if((*iter).first == per)
			{
				(*iter).second = pn;
			}
		}
	}
};
std::ostream &operator<<(std::ostream &os, const PhoneBook &pb)
{
	for(auto iter : pb.phoneBook)
	{
		os << iter.first  << iter.second << std::endl;
	}
	return os;
}

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::ifstream file("PhoneBook.txt");
	if(!file)
	{
		std::cout << "Файл не открыт." << std::endl;
	} else
	{
		std::cout << "Файл открыт.\n" << std::endl;
		PhoneBook book(file);
		std::cout << book << std::endl;
		
		std::cout << std::left << std::setw(47) << std::setfill('@') << "1 SortByName  " << std::setfill(' ') << std::endl << std::endl;
		book.SortByName();
		std::cout << book << std::endl;

		std::cout << std::left << std::setw(47) << std::setfill('@') << "2 SortByPhone  " << std::setfill(' ') << std::endl << std::endl;
		book.SortByPhone();
		std::cout << book << std::endl;

		std::cout << std::left << std::setw(47) << std::setfill('@') << "3 GetPhoneNumber  " << std::setfill(' ') << std::endl << std::endl;

		auto print_phone_number = [&book](const std::string &surname)
		{
			std::cout << surname << "\t";
			auto answer = book.GetPhoneNumber(surname);
			if (std::get<0>(answer).empty())
				std::cout << std::get<1>(answer);
			else
				std::cout << std::get<0>(answer);
			std::cout << std::endl;
		};
		print_phone_number("Клим");
		print_phone_number("Котов");

		std::cout << std::left << std::setw(47) << std::setfill('@') << "4 ChangePhoneNumber  " << std::setfill(' ') << std::endl << std::endl;
		book.ChangePhoneNumber(Person{ "Зайцев", "Захар", "Артемович" },
		PhoneNumber{7, 123, "15344458", std::nullopt});
		book.ChangePhoneNumber(Person{ "Абра", "Кадабра", "Абракадабровна" },
		PhoneNumber{ 16, 465, "9155448", 13 });
		std::cout << book;

	}



	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	return 0;
}


