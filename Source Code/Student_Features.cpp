#define _CRT_SECURE_NO_WARNINGS
#include "Project.h"
#include "Student_Features.h"

static void show_Menu(Student& student);
static void Profile(Student& student);
static void Change_Pass(Student& student);

void Student_Features(Student& student)
{
	int choice;
	do
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		title();
		cout << "        1. Show menu\n\n";
		cout << "\t\t\t\t";
		cout << "        2. View profile info\n\n";
		cout << "\t\t\t\t";
		cout << "        3. Change password\n\n";
		cout << "\t\t\t\t";
		cout << "        4. Log out\n\n";
		cout << "\t\t\t\t";
		cout << "        Choose options:[1/2/3/4]: ";
		cin >> choice;
	} while (cin.fail());
	switch (choice)
	{
	case 1:
	{
		system("cls");
		show_Menu(student);
		break;
	}

	case 2:
	{
		system("cls");
		Profile(student);
		break;
	}

	case 3:
	{
		system("cls");
		Change_Pass(student);
		break;
	}

	case 4:
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t";
		cout << "Thank you for using our application";
		cout << "\n\n\n\n";
		break;
	}

	default:
	{
		cout << "\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "   Invalid input!";
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "   Press Enter to choose again...";
		std::cin.get();
		Student_Features(student);
	}
	}
}

static void Profile(Student& student)
{
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Fullname        :    " << student.fullname;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Date of Birth   :    " << student.DoB;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Country         :    Viet Nam";
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Studying at     :    Ho Chi Minh University of Science";
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Student ID      :    " << student.user;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Class           :    " << student.Class;
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Student_Features(student);
}

static void Change_Pass(Student& student)
{
	string current_Pass;
	string new_Pass;
	string retype;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Current Password     :    ";
	current_Pass = _Get_Pass();
	std::cin.ignore();
	while (current_Pass != student.pass)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Your password was incorrect!";
		std::cin.get();
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t";
		cout << "Current Password     :    ";
		current_Pass = _Get_Pass();
	}
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "New Password         :    ";
	new_Pass = _Get_Pass();
	while (new_Pass.size() < 8) //The length of Password less than 8
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Password at least 8 characters";
		std::cin.get();
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t";
		cout << "Current Password     :    ";
		for (int i = 0; i < current_Pass.size(); i++)
			cout << "*";
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "New Password         :    ";
		new_Pass = _Get_Pass();
	}
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Re-type new password :    ";
	retype = _Get_Pass();
	while (new_Pass != retype) //new password and retype are not matched
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Passwords do not match";
		std::cin.get();
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t";
		cout << "Current Password     :    ";
		for (int i = 0; i < current_Pass.size(); i++)
			cout << "*";
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "New Password         :    ";
		new_Pass = _Get_Pass();
		while (new_Pass.size() < 8) //The length of Password less than 8
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "Password at least 8 characters";
			std::cin.get();
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n";
			cout << "\t\t\t\t";
			cout << "Current Password     :    ";
			for (int i = 0; i < current_Pass.size(); i++)
				cout << "*";
			cout << "\n\n";
			cout << "\t\t\t\t";
			cout << "New Password         :    ";
			new_Pass = _Get_Pass();
		}
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "Re-type new password :    ";
		retype = _Get_Pass();
	}

	std::ifstream in_File;
	in_File.open(_path._Student);
	string result;
	if (!in_File.is_open())
		cout << "File not existed\n";
	else
	{
		while (!in_File.eof())
		{
			string text;
			std::getline(in_File, text);
			int fst = text.find(',', 0);
			int snd = text.find(',', fst + 1);
			string pass_pos = text.substr(fst + 1, snd - (fst + 1));
			string user_Name = text.substr(0, fst);
			if (pass_pos == current_Pass && user_Name == student.user)
			{
				text.replace(fst + 1, current_Pass.length(), new_Pass);
				result += text + "\n";
			}
			else
			{
				result += text + "\n";
			}
		}
	}
	in_File.close();
	std::ofstream out_File(_path._Student, std::ios::in | std::ios::trunc);
	result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
	out_File << result;
	out_File.close();
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "     Password changed successfully";
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Student_Features(student);
}

static void show_Menu(Student& student)
{
	int choice;
	do
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t";
		cout << "      0. Go back to main page\n\n";
		cout << "\t\t\t\t\t";
		cout << "      1. Check in course\n\n";
		cout << "\t\t\t\t\t";
		cout << "      2. View check in\n\n";
		cout << "\t\t\t\t\t";
		cout << "      3. View Schedules\n\n";
		cout << "\t\t\t\t\t";
		cout << "      4. View Score of a course\n\n";
		cout << "\t\t\t\t\t";
		cout << "      Choose options:[0 -> 4]: ";
		cin >> choice;
	} while (cin.fail());
	switch (choice)
	{
	case 0:
	{
		system("cls");
		Student_Features(student);
		break;
	}

	case 1:
	{
		system("cls");
		Check_in(student);
		break;
	}

	case 2:
	{
		system("cls");
		View_Check_in(student);
		break;
	}

	case 3:
	{
		system("cls");
		View_Schedules(student);
		break;
	}

	case 4:
	{
		system("cls");
		View_Score_of_A_Course(student);
		break;
	}

	default:
	{
		cout << "\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "      Invalid input!";
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Press Enter to choose again...";
		cin.get();
		show_Menu(student);
	}
	}
}

void Check_in(Student& student)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "    Check in to course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter your present Academic Year (yyyy-yyyy)    : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter your present semester                     : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter course id you want to check in            : ";
	cin >> course_id;
	string filename = acad_year + "-" + semes + "-" + student.Class + "-" + course_id + ".txt";
	std::ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
	{
		cout << "\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "  You are no " << course_id << " matched in this semester";
	}
	else
	{
		string text;
		bool _Valid_Date = 0; //0 = Invalid date 
		bool _ID_Check = 0;
		std::ofstream outfile(filename, std::ios::in);
		while (std::getline(infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
			if (text.substr(fst + 1, snd - (fst + 1)) == student.user) //Go to correct student
			{
				_ID_Check = 1;
				outfile << text << endl;
				std::time_t T = std::time(NULL);
				struct tm localTime = *std::localtime(&T);

				string _SystemDate; //Create System Date
				if (localTime.tm_mday < 10 && localTime.tm_mon + 1 < 10)
					_SystemDate = "0" + std::to_string(localTime.tm_mday) + "/0" + std::to_string(localTime.tm_mon + 1) + "/" + std::to_string(localTime.tm_year + 1900);
				else if (localTime.tm_mday >= 10 && localTime.tm_mon + 1 < 10)
					_SystemDate = std::to_string(localTime.tm_mday) + "/0" + std::to_string(localTime.tm_mon + 1) + "/" + std::to_string(localTime.tm_year + 1900);
				else if (localTime.tm_mday < 10 && localTime.tm_mon + 1 >= 10)
					_SystemDate = "0" + std::to_string(localTime.tm_mday) + "/" + std::to_string(localTime.tm_mon + 1) + "/" + std::to_string(localTime.tm_year + 1900);
				else
					_SystemDate = std::to_string(localTime.tm_mday) + "/" + std::to_string(localTime.tm_mon + 1) + "/" + std::to_string(localTime.tm_year + 1900);

				int _SystemHour = localTime.tm_hour;
				int _SystemMinute = localTime.tm_min;

				while (std::getline(infile, text))
				{
					if (text == "")
					{
						outfile << "\n";
						break;
					}
					fst = text.find_first_of(',');
					snd = text.find(',', fst + 1);
					trd = text.find(',', snd + 1);
					if (text.substr(0, fst) == _SystemDate) //Valid date
					{
						string status = text.substr(trd + 1); //Current status: -1
						string _StartTime = text.substr(fst + 1, snd - (fst + 1)); //7:30, grab info from txt file
						string _EndTime = text.substr(snd + 1, trd - (snd + 1));   //11:30, grab info from txt file
						int _StartTime_Colon = _StartTime.find_first_of(':');	   //7:30 -> 1, analyze to find ":"
						int _EndTime_Colon = _EndTime.find_first_of(':');          //11:30 -> 2, analyze to find ":"
						string _Start_Hour = _StartTime.substr(0, _StartTime_Colon); // 7
						string _Start_Min = _StartTime.substr(_StartTime_Colon + 1); // 30
						string _End_Hour = _EndTime.substr(0, _EndTime_Colon);       // 11
						string _End_Min = _EndTime.substr(_EndTime_Colon + 1);       // 30
						if (_SystemHour == std::stoi(_Start_Hour) && _SystemMinute >= std::stoi(_Start_Min)) //Ex: System >= 7:30; Course = 7:30
						{
							_Valid_Date = 1;
							text.replace(trd + 1, status.length(), "+1");
						}
						else if (_SystemHour == std::stoi(_Start_Hour) && _SystemMinute < std::stoi(_Start_Min)) //Ex: System < 7:30; Course = 7:30
						{
							outfile << text << "\n";
							continue;
						}
						else if (_SystemHour == std::stoi(_End_Hour) && _SystemMinute <= std::stoi(_End_Min)) //Ex: System <= 11:30; Course = 11:30
						{
							_Valid_Date = 1;
							text.replace(trd + 1, status.length(), "+1");
						}
						else if (_SystemHour == std::stoi(_End_Hour) && _SystemMinute > std::stoi(_End_Min)) //Ex: System > 11:30; Course = 11:30
						{
							outfile << text << "\n";
							continue;
						}
						else if (_SystemHour >= std::stoi(_Start_Hour) && _SystemHour <= std::stoi(_End_Hour)) //Ex: Start <= System <= End
						{
							_Valid_Date = 1;
							text.replace(trd + 1, status.length(), "+1");
						}
						outfile << text << "\n";
					}
					else
						outfile << text << "\n";
				}
			}
			else
			{
				outfile << text << endl;
				for (int i = 0; i < 12; i++)
				{
					std::getline(infile, text);
					outfile << text << endl;
				}
			}
		}
		infile.close();
		outfile.close();
		if (_ID_Check)
		{
			if (_Valid_Date)
			{
				cout << "\n\n";
				cout << "\t\t\t\t\t\t";
				cout << "    Checked in Done";
			}
			else
			{
				cout << "\n\n";
				cout << "\t\t\t\t\t\t";
				cout << " Invalid date to check in";
			}
		}
		else
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "   You've not registered this course yet ";
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t    ";
	char input;
	cout << "Do you want to check in more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Check_in(student);
	}
	else
		show_Menu(student);
}

void View_Check_in(Student& student)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "    View Check In";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter your present Academic Year (yyyy-yyyy)    : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter your present semester                     : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter course id you want to view                : ";
	cin >> course_id;
	cout << "\n\n";
	cout << "\t\tNo" << "\t    ID      " << "\tFullname\t" << "\t\tDate of Birth\t" << "    Class";
	string filename = acad_year + "-" + semes + "-" + student.Class + "-" + course_id + ".txt";
	std::ifstream infile(filename);
	string text;
	while (std::getline(infile, text))
	{
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find_last_of(',');
		if (text.substr(fst + 1, snd - (fst + 1)) == student.user)
		{
			cout << "\n\n";
			cout << "\t\t" << text.substr(0, fst) //No
				<< "\t    " << text.substr(fst + 1, snd - (fst + 1)) //ID
				<< "\t" << text.substr(snd + 1, trd - (snd + 1)); //Full name
			string temp = text.substr(snd + 1, trd - (snd + 1));
			for (int i = 0; i < 32 - temp.size(); i++)
				cout << " ";
			cout << text.substr(trd + 1, fth - (trd + 1)) //DoB
				<< "\t    " << text.substr(fth + 1); //Class
			std::getline(infile, text); //Skip line of score
			while (std::getline(infile, text))
			{
				if (text == "")
					break;
				cout << "\n\n";
				cout << "\t\t\t\t\t";
				std::replace(text.begin(), text.end(), ',', ' ');
				cout << "        " << text;
			}
		}
		else
		{
			for (int i = 0; i < 12; i++)
				std::getline(infile, text);
		}
	}
	infile.close();
	cout << "\n\n";
	cout << "\t\t\t\t\t    ";
	char input;
	cout << "Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Check_in(student);
	}
	else
		show_Menu(student);
}

void View_Schedules(Student& student)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "    View Schedules";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter your present Academic Year (yyyy-yyyy) : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter your present semester                  : ";
	cin >> semes;
	cout << "\n\n";
	string filename = acad_year + "-" + semes + "-Schedule-" + student.Class + ".txt";
	std::ifstream infile(filename);
	string text;
	while (std::getline(infile, text))
	{
		std::replace(text.begin(), text.end(), ',', ' ');
		cout << "  " << text;
		cout << "\n\n";
	}
	infile.close();
	cout << "\n";
	cout << "\t\t\t\t\t ";
	wait();
	show_Menu(student);
}

void View_Score_of_A_Course(Student& student)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "    View Score of a course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter your present Academic Year (yyyy-yyyy)    : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter your present semester                     : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Which scoreboard of the course you want to view : ";
	cin >> course_id;
	cout << "\n\n";
	cout << "\t\tNo" << "\t    ID      " << "\tFullname\t\t" << "\tMid-term" << "     Final" << "     Bonus" << "     Total";
	string filename = acad_year + "-" + semes + "-" + student.Class + "-" + course_id + ".txt";
	std::ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
	{
		cout << "\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "    You are no " << course_id << " matched in this semester";
	}
	else
	{
		std::string text;
		while (std::getline(infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
			if (text.substr(fth + 1) == student.Class && text.substr(fst + 1, snd - (fst + 1)) == student.user)
			{
				cout << "\n\n";
				cout << "\t\t" << text.substr(0, fst)
					<< "\t    " << text.substr(fst + 1, snd - (fst + 1))
					<< "\t" << text.substr(snd + 1, trd - (snd + 1));
				string temp = text.substr(snd + 1, trd - (snd + 1));
				for (int i = 0; i < 32 - temp.size(); i++)
					cout << " ";
				std::getline(infile, text);
				string score = text;
				std::replace(score.begin(), score.end(), ',', ' ');
				fst = score.find_first_of(' ');
				snd = score.find(' ', fst + 1);
				trd = score.find(' ', snd + 1);
				cout << score.substr(0, fst) //Mid-term
					<< "\t     " << score.substr(fst + 1, snd - (fst + 1)); //Final
				for (int i = 0; i < 10 - score.substr(fst + 1, snd - (fst + 1)).size(); i++)
					cout << " ";
				cout << score.substr(snd + 1, trd - (snd + 1)) //Bonus
					<< "\t " << score.substr(trd + 1); //Total
			}
			else
				continue;
		}
		infile.close();
	}
	cout << "\n\n\n";
	cout << "\t\t\t\t\t\t";
	char input;
	cout << "Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Score_of_A_Course(student);
	}
	else
		show_Menu(student);
}