#pragma once
#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <sstream>

namespace MyNamespace
{
	class FullName
	{
	private:
		std::string surname, name;
		std::optional<std::string> patronymic;

	public:
		FullName(std::string surname, std::string name, std::string patronymic) : surname(surname), name(name), patronymic(patronymic)
		{}
		FullName(std::string surname, std::string name) : surname(surname), name(name), patronymic(std::nullopt)
		{}
		~FullName()
		{
			this->surname = "";
			this->surname.shrink_to_fit();
			this->name = "";
			this->name.shrink_to_fit();
			this->patronymic.reset();
		}
		bool operator==(const FullName& name)
		{
			return std::tie(this->surname, this->name, this->patronymic) == std::tie(name.surname, name.name, name.patronymic);
		}
		friend std::ostream &operator<<(std::ostream &os, const FullName fn);
	};
	std::ostream& operator<<(std::ostream& os,const FullName fn)
	{
		os << "Полное имя: \t" << fn.surname << ' ' << fn.name;
		if(fn.patronymic.has_value())
		{
			os << ' ' << fn.patronymic.value();
		}
		return os;
	}
	class Student
	{
	private:
		FullName fullName;
		std::vector<int> scores;
		double averangeScore = 0;

	public:
		Student(std::string surname, std::string name, std::string patronymic, std::vector<int> scores) : fullName(surname, name, patronymic), scores(scores)
		{
			for(auto iter = 0; iter < scores.size(); iter++)
			{
				this->averangeScore += scores.at(iter);
			}
			this->averangeScore /= scores.size();
		}
		Student(std::string surname, std::string name, std::vector<int> scores) : fullName(surname, name)
		{
			for(auto iter = 0; iter < scores.size(); iter++)
			{
				this->scores.push_back(scores[iter]);
			}
			for(auto iter = 0; iter < scores.size(); iter++)
			{
				this->averangeScore += scores.at(iter);
			}
			this->averangeScore /= scores.size();
		}
		~Student()
		{
			if(!scores.empty())
			{
				this->scores.clear();
				this->scores.shrink_to_fit();
			}
		}
		double GetAverageScore()
		{
			return this->averangeScore;
		}
		bool operator==(const FullName& name)
		{
			return this->fullName == name;
		}
		friend std::ostream &operator<<(std::ostream &os, const Student st);
	};
	std::ostream &operator<<(std::ostream &os, const Student st)
	{
		os << st.fullName << '\n'
		   << "Средний балл: \t" << st.averangeScore << '\n' << "Все баллы:\n";
		for (auto iter = 0; iter < st.scores.size(); iter++)
		{
			os << st.scores[iter] << '\t';
			if(iter%5 == 4)
			{
				os << '\n';
			}
		}
		os << '\n';
		return os;
	}

	class IRepository 
	{
		virtual void Open() = 0; // бинарная десериализация в файл
		virtual void Save() = 0; // бинарная сериализация в файл
	};

	class IMethods 
	{
		virtual double GetAverageScore(const FullName& name) = 0;
		virtual std::string GetAllInfo(const FullName& name) = 0;
		virtual std::string GetAllInfo() = 0;
	};

	class StudentsGroup : public IRepository , public IMethods
	{
	private:
		std::vector<Student> students;

	public:
		StudentsGroup(std::string surname, std::string name, std::string patronymic, std::vector<int> scores)
		{
			students.push_back(Student(surname, name, patronymic, scores));
		}
		StudentsGroup(std::string surname, std::string name, std::vector<int> scores)
		{
			students.push_back(Student(surname, name, scores));
		}
		StudentsGroup(){}
		void addStudent(std::string surname, std::string name, std::string patronymic, std::vector<int> scores)
		{
			students.push_back(Student(surname, name, patronymic, scores));
		}
		void addStudent(std::string surname, std::string name, std::vector<int> scores)
		{
			students.push_back(Student(surname, name, scores));
		}
		void Open() override
		{
			std::ifstream in("binary.bin", std::ios::binary); 
			in.read(reinterpret_cast<char*>(&this->students), sizeof(this->students));
		}
		void Save() override
		{
			std::ofstream out("binary.bin", std::ios::binary);
			if(out.good())
			{
				out.write(reinterpret_cast<char*>(&this->students), sizeof(this->students));
			}
		}
		double GetAverageScore(const FullName& name)
		{
			return (*std::find_if(this->students.begin(), this->students.end(), [&name](auto iter)
								{ return iter == name; })).GetAverageScore();
		}
		std::string GetAllInfo(const FullName& name)
		{
			std::stringstream ss;
			ss << (*std::find_if(this->students.begin(), this->students.end(), [&name](auto iter)
							  { return iter == name; }));
			return ss.str();
		}
		std::string GetAllInfo()
		{
			std::stringstream ss;
			for(auto iter : this->students)
			{
				ss << iter << '\n';
			}
			return ss.str();
		}
		
		~StudentsGroup()
		{
			if(!students.empty())
			{
				students.clear();
				students.shrink_to_fit();
			}
		}
	};
	
}