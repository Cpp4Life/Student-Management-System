#ifndef _STUDENT_MANAGEMENT_SYSTEM_H
#define _STUDENT_MANAGEMENT_SYSTEM_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <filesystem>
#include <limits>
namespace fs = std::filesystem;
using namespace std;

struct Staff
{
	string user;
	string pass;
	string fullname;
	string gender;
};

struct Lecturer
{
	string user;
	string pass;
	string fullname;
	string degree;
	string gender;
};

struct Student
{
	string user;
	string pass;
	string fullname;
	string DoB;
	string Class;
};

struct Course
{
	string course_id;
	string start_date;
	string end_date;
	string start_time;
	string end_time;
};

void mainpage();
void logscreen(std::vector<Staff>& staff, std::vector<Lecturer>& lect, std::vector<Student>& student);

static void title()
{
	cout << "\n\n\n\n";
	cout << "\t\t\t\t    ---------------------------\n";
	cout << "\t\t\t\t    |STUDENT MANAGEMENT SYSTEM|\n";
	cout << "\t\t\t\t    ---------------------------\n";
	cout << "\n\n";
	cout << "\t\t\t\t";
}

static void wait()
{
	//cout << "      Press Enter to continue...";
	//cin.ignore();
	//cin.get();

	cout << "      Press Enter to continue...";
	char get;
	get = _getch();
	try
	{
		if (get != 13 || get != ' ')
			throw 13;
	}
	catch(...){}
}

static string _Get_Pass()
{
	string _Current;
	char ast = ' ';
	int aste = 0;
	do
	{
		ast = _getch(); //Enter password

		if (ast == 13 || ast == ' ')
			break;
		if ((ast == 8 || ast == 127) && !_Current.empty())
		{
			cout << "\b \b";
			_Current.erase(_Current.size() - 1);
			aste--;
		}
		else
		{
			_Current += ast;
			cout << "*";
			aste++;
		}
	} while (1);
	return _Current;
}

static class Path
{
public:
	//string _Staff = "C:\\Users\\asus\\Desktop\\Student-Management-System\\Student-Management-System\\Staff.txt";
	//string _Lecturer = "C:\\Users\\asus\\Desktop\\Student-Management-System\\Student-Management-System\\Lecturer.txt";
	//string _Student = "C:\\Users\\asus\\Desktop\\Student-Management-System\\Student-Management-System\\Students.txt";
	std::filesystem::path _Staff = std::filesystem::current_path() / "Staff.txt";
	std::filesystem::path _Lecturer = std::filesystem::current_path() / "Lecturer.txt";
	std::filesystem::path _Student = std::filesystem::current_path() / "Students.txt";
};

static Path _path;

#endif 