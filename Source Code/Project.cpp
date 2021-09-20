#define _CRT_SECURE_NO_WARNINGS
#include "Project.h"

void date()
{
	std::time_t T = std::time(NULL);
	struct tm localTime = *std::localtime(&T);
	cout << "\n\n\n";
	cout << "\t\t\t\t\t Date : ";
	if (localTime.tm_mday < 10 && localTime.tm_mon + 1 < 10)
		cout << "0" << localTime.tm_mday << "/0" << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
	else if (localTime.tm_mday >= 10 && localTime.tm_mon + 1 < 10)
		cout << localTime.tm_mday << "/0" << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
	else if (localTime.tm_mday < 10 && localTime.tm_mon + 1 >= 10)
		cout << "0" << localTime.tm_mday << "/" << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
	else
		cout << localTime.tm_mday << "/" << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
}

void mainpage()
{
	date();
	cout << "\n";
	cout << "\t\t\t\t    ---------------------------\n";
	cout << "\t\t\t\t    |STUDENT MANAGEMENT SYSTEM|\n";
	cout << "\t\t\t\t    ---------------------------\n";
	cout << "\n\n\n";
	cout << "\t\t\t\t";
	cout << "Written By    :    Truong Gia Dat\n";
	cout << "\t\t\t\t\t\t   Nguyen Van Binh\n";
	cout << "\t\t\t\t\t\t   Nguyen Thanh Hieu\n";
	cout << "\t\t\t\t\t\t   Le Xuan Dinh\n";
	cout << "\n";
	cout << "\t\t\t\t";
	cout << "Project       :    Student Management System";
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Guided By     :    MSc. Thanh Ho Tuan\n";
	cout << "\t\t\t\t\t\t   MSc. Phuong Loc Truong";
	cout << "\n\n";
	cout << "\t\t\t\t    Press Enter to continue......";
	cin.get();
}

void call_Exit()
{
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t";
	cout << "You are no longer to use the System.";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "   Press Enter to Exit Program...";
	cin.get();
	exit(0);
}

void Staff_Features(Staff& staff);
void Lecturer_Features(Lecturer& lect);
void Student_Features(Student& student);

string _GetPassword()
{
	string _Getpass;
	char ast = ' ';
	int aste = 0;
	do
	{
		ast = _getch(); //Enter password

		if (ast == 13 || ast == ' ')
			break;
		if ((ast == 8 || ast == 127) && !_Getpass.empty())
		{
			cout << "\b \b";
			_Getpass.erase(_Getpass.size() - 1);
			aste--;
		}
		else
		{
			_Getpass += ast;
			cout << "*";
			aste++;
		}
	} while (1);
	return _Getpass;
}

void logscreen(std::vector<Staff>& staff, std::vector<Lecturer>& lect, std::vector<Student>& student)
{
	string username;
	string password;
	int attempt = 0;
	int check = 1;
	do
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "    Username: ";
		cin >> username;
		cout << "\n";
		cout << "\t\t\t\t\t";
		cout << "    Password: ";
		password = _GetPassword();
		for (int i = 0; i < staff.size(); i++) //Staff Login
		{
			if (username.compare(staff[i].user) == 0 && password.compare(staff[i].pass) == 0)
			{
				cout << "\n\n";
				cout << "\t\t\t\t";
				cout << "You are successfully accessed to the system!\n\n";
				cout << "\t\t\t\t      Press Enter to continue...";
				cin.get();
				Staff account = staff[i];
				Staff_Features(account);
				check = 0;
				break;
			}
			else
				continue;
		}

		if (check == 0)
			break;

		for (int i = 0; i < lect.size(); i++) //Lecturer Login
		{
			if (username.compare(lect[i].user) == 0 && password.compare(lect[i].pass) == 0)
			{
				cout << "\n\n";
				cout << "\t\t\t\t";
				cout << "You are successfully accessed to the system!\n\n";
				cout << "\t\t\t\t      Press Enter to continue...";
				cin.get();
				Lecturer account = lect[i];
				Lecturer_Features(account);
				check = 0;
				break;
			}
			else
				continue;
		}

		if (check == 0)
			break;

		for (int i = 0; i < student.size(); i++) //Student Login
		{
			if (username.compare(student[i].user) == 0 && password.compare(student[i].pass) == 0)
			{
				cout << "\n\n";
				cout << "\t\t\t\t";
				cout << "You are successfully accessed to this system!\n\n";
				cout << "\t\t\t\t      Press Enter to continue...";
				cin.get();
				Student account = student[i];
				Student_Features(account);
				check = 0;
				break;
			}
			else
				continue;
		}

		if (check == 0)
			break;

		if (check == 1)
		{
			system("cls");
			attempt += 1;
			cout << "\n\n\n\n\n\n\n\n\n\n";
			cout << "\t\t\t\t\t";
			cout << "Login Failed";
			cout << "\n\n";
			cout << "\t\t\t\t";
			cout << "      Attempts remain: " << 3 - attempt;
			cin.ignore();
			cin.get();
		}
		if (attempt >= 3)
		{
			cout << "\n";
			cout << "\t\t\t";
			cout << "      No permission to access the system!";
			cin.get();
			call_Exit();
			cin.get();
		}
	} while (check == 1);
}