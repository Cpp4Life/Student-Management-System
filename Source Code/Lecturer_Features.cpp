#include "Project.h"
#include "Lecturer_Features.h"

static void show_Menu(Lecturer& lect);
static void Profile(Lecturer& lect);
static void Change_Pass(Lecturer& lect);

void Lecturer_Features(Lecturer& lect)
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
		show_Menu(lect);
		break;
	}

	case 2:
	{
		system("cls");
		Profile(lect);
		break;
	}

	case 3:
	{
		system("cls");
		Change_Pass(lect);
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
		cin.get();
		Lecturer_Features(lect);
	}
	}
}

static void Profile(Lecturer& lect)
{
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Fullname        :    " << lect.fullname;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Degree          :    " << lect.degree;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Gender          :    " << lect.gender;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Country         :    Viet Nam";
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Working at      :    Ho Chi Minh University of Science";
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Lecturer_Features(lect);
}

static void Change_Pass(Lecturer& lect)
{
	string current_Pass;
	string new_Pass;
	string retype;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Current Password     :    ";
	current_Pass = _Get_Pass();
	cin.ignore();
	while (current_Pass != lect.pass)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Your password was incorrect!";
		cin.get();
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
	while (new_Pass != retype)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Passwords do not match";
		cin.get();
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
	in_File.open(_path._Lecturer);
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
			if (pass_pos == current_Pass && user_Name == lect.user)
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
	std::ofstream out_File(_path._Lecturer, std::ios::in | std::ios::trunc);
	result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
	out_File << result;
	out_File.close();
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "     Password changed successfully";
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Lecturer_Features(lect);
}

static void show_Menu(Lecturer& lect)
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
		cout << "      1. View list of courses in the current semester\n\n";
		cout << "\t\t\t\t\t";
		cout << "      2. View list of students of a course\n\n";
		cout << "\t\t\t\t\t";
		cout << "      3. View attendance list of a course\n\n";
		cout << "\t\t\t\t\t";
		cout << "      4. Edit an attendance\n\n";
		cout << "\t\t\t\t\t";
		cout << "      5. Import scoreboard of a course\n\n";
		cout << "\t\t\t\t\t";
		cout << "      6. Edit grade of a student\n\n";
		cout << "\t\t\t\t\t";
		cout << "      7. View a scoreboard\n\n";
		cout << "\t\t\t\t\t";
		cout << "      Choose options:[0 -> 7]: ";
		cin >> choice;
	} while (cin.fail());
	switch (choice)
	{
	case 0:
	{
		system("cls");
		Lecturer_Features(lect);
		break;
	}

	case 1:
	{
		system("cls");
		View_Courses(lect);
		break;
	}

	case 2:
	{
		system("cls");
		View_Students_of_A_Course(lect);
		break;
	}

	case 3:
	{
		system("cls");
		View_Attendance_of_A_Course(lect);
		break;
	}

	case 4:
	{
		system("cls");
		Edit_Attendance(lect);
		break;
	}

	case 5:
	{
		system("cls");
		Import_Scoreboard(lect);
		break;
	}

	case 6:
	{
		system("cls");
		Edit_Grade(lect);
		break;
	}

	case 7:
	{
		system("cls");
		View_Scoreboard(lect);
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
		show_Menu(lect);
	}
	}
}

void View_Courses(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "          View Courses of Semester";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the Semester you want to view     : ";
	cin >> semes;
	cout << "\n\n";
	string filename = acad_year + "-" + semes + "-Schedule-";
	std::vector<string> courses;
	string text;
	bool check;
	for (int i = 1; i <= 10; i++)
	{
		check = 0;
		string temp = "19CLC" + std::to_string(i) + ".txt";
		filename += temp;
		std::ifstream K19CLC_infile(filename);
		while (std::getline(K19CLC_infile, text))
		{
			check = text.find(lect.user, 0) != string::npos;
			if (check)
			{
				courses.push_back(text);
				break;
			}
		}
		filename.erase(filename.end() - temp.size(), filename.end());
	}

	for (int i = 1; i <= 2; i++)
	{
		check = 0;
		string temp = "19APCS" + std::to_string(i) + ".txt";
		filename += temp;
		std::ifstream K19APCS_infile(filename);
		while (std::getline(K19APCS_infile, text))
		{
			check = text.find(lect.user, 0) != string::npos;
			if (check)
			{
				courses.push_back(text);
				break;
			}
		}
		filename.erase(filename.end() - temp.size(), filename.end());
	}

	for (int i = 1; i <= 6; i++)
	{
		check = 0;
		string temp = "18CLC" + std::to_string(i) + ".txt";
		filename += temp;
		std::ifstream K18CLC_infile(filename);
		while (std::getline(K18CLC_infile, text))
		{
			check = text.find(lect.user, 0) != string::npos;
			if (check)
			{
				courses.push_back(text);
				break;
			}
		}
		filename.erase(filename.end() - temp.size(), filename.end());
	}

	for (int i = 1; i <= 3; i++)
	{
		check = 0;
		string temp = "19APCS" + std::to_string(i) + ".txt";
		filename += temp;
		std::ifstream K18APCS_infile(filename);
		while (std::getline(K18APCS_infile, text))
		{
			check = text.find(lect.user, 0) != string::npos;
			if (check)
			{
				courses.push_back(text);
				break;
			}
		}
		filename.erase(filename.end() - temp.size(), filename.end());
	}

	for (int i = 0; i < courses.size(); i++)
	{
		std::replace(courses[i].begin(), courses[i].end(), ',', ' ');
		cout << "  " << courses[i] << "\n\n";
	}
	cout << "\n";
	cout << "\t\t\t\t\t     ";
	char input;
	cout << "Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Courses(lect);
	}
	else
		show_Menu(lect);
}

void View_Students_of_A_Course(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "          View Students of a Course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter Semester you want to view         : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID you want to view         : ";
	cin >> Class;
	string course_id;
	string sche = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(sche);
	string content;
	bool check = 0;
	while (std::getline(sche_infile, content))
	{
		int fst = content.find_first_of(',');
		int snd = content.find(',', fst + 1);
		check = content.find(lect.user, 0) != string::npos;
		if (check)
		{
			course_id = content.substr(fst + 1, snd - (fst + 1));
			break;
		}
	}
	sche_infile.close();
	if (check)
	{
		cout << "\n\n";
		cout << "\t\tNo" << "\t    ID      " << "\tFullname\t" << "\t\tDate of Birth\t" << "    Class";
		string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream infile(filename);
		string text;
		while (std::getline(infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
			if (text.substr(fth + 1) == Class)
			{
				cout << "\n\n";
				cout << "\t\t" << text.substr(0, fst)
					<< "\t    " << text.substr(fst + 1, snd - (fst + 1))
					<< "\t" << text.substr(snd + 1, trd - (snd + 1));
				string temp = text.substr(snd + 1, trd - (snd + 1));
				for (int i = 0; i < 32 - temp.size(); i++)
					cout << " ";
				cout << text.substr(trd + 1, fth - (trd + 1))
					<< "\t    " << text.substr(fth + 1);
			}
			else
				continue;
		}
		infile.close();
	}
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "You are no teaching class " << Class << " in this semester";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "     Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Students_of_A_Course(lect);
	}
	else
		show_Menu(lect);
}

void View_Attendance_of_A_Course(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "          View Attendance of A course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the semester of course            : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID you want to view         : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	string sche = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(sche);
	string content;
	bool check = 0;
	while (std::getline(sche_infile, content))
	{
		int fst = content.find_first_of(',');
		int snd = content.find(',', fst + 1);
		check = content.find(lect.user, 0) != string::npos;
		if (check)
		{
			course_id = content.substr(fst + 1, snd - (fst + 1));
			break;
		}
	}
	sche_infile.close();
	if (check)
	{
		cout << "\n\n";
		cout << "\t\tNo" << "\t    ID      " << "\tFullname\t" << "\t\tDate of Birth\t" << "    Class";
		string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream infile(filename);
		string text;
		while (std::getline(infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
			if (text.substr(fth + 1) == Class)
			{
				cout << "\n\n";
				cout << "\t\t" << text.substr(0, fst)
					<< "\t    " << text.substr(fst + 1, snd - (fst + 1))
					<< "\t" << text.substr(snd + 1, trd - (snd + 1));
				string temp = text.substr(snd + 1, trd - (snd + 1));
				for (int i = 0; i < 32 - temp.size(); i++)
					cout << " ";
				cout << text.substr(trd + 1, fth - (trd + 1))
					<< "\t    " << text.substr(fth + 1);
				std::getline(infile, text);
			}
			else
			{
				cout << "\n\n";
				cout << "\t\t\t\t\t";
				std::replace(text.begin(), text.end(), ',', ' ');
				cout << "        " << text;
			}
		}
		infile.close();
	}
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t     ";
		cout << "    No any classes matched in this semester";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "    Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Attendance_of_A_Course(lect);
	}
	else
		show_Menu(lect);
}

void Edit_Attendance(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "       Edit An Attendance";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)              : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester                   : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Student Class ID                       : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string student_id;
	cout << "    Enter Student ID you want to edit attendance : ";
	cin >> student_id;
	string course_id;
	string sche = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(sche);
	string content;
	bool check = 0;
	while (std::getline(sche_infile, content))
	{
		int fst = content.find_first_of(',');
		int snd = content.find(',', fst + 1);
		check = content.find(lect.user, 0) != string::npos;
		if (check)
		{
			course_id = content.substr(fst + 1, snd - (fst + 1));
			break;
		}
	}
	sche_infile.close();
	if (check)
	{
		string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream course_infile(filename);
		std::ofstream course_outfile(filename, std::ios::in);
		string text;
		bool _Valid_Date = 0;
		bool _ID_Check = 0;
		while (getline(course_infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			if (text.substr(fst + 1, snd - (fst + 1)) == student_id)
			{
				_ID_Check = 1;
				course_outfile << text << "\n";
				string date;
				cout << "\n";
				cout << "\t\t\t\t";
				cout << "    Enter date you want to edit (dd/mm/yyyy)     : ";
				cin >> date;
				while (getline(course_infile, text))
				{
					fst = text.find_first_of(',');
					snd = text.find(',', fst + 1);
					trd = text.find(',', snd + 1);
					if (text == "")
					{
						course_outfile << "\n";
						break;
					}
					if (text.substr(0, fst) == date)
					{
						_Valid_Date = 1;
						string _Current_Status = text.substr(trd + 1);
						string _New_Status;
						cout << "\n";
						cout << "\t\t\t\t";
						cout << "    Enter new status (-1 or +1)                  : ";
						cin >> _New_Status;
						while (_New_Status.size() != 2)
						{
							cout << "\n\n";
							cout << "\t\t\t\t\t\t";
							cout << "        Wrong Format";
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							cin.get();
							system("cls");
							cout << "\n\n";
							cout << "\t\t\t\t\t\t";
							cout << "    Edit An Attendance";
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter Academic Year (yyyy-yyyy)              : " << acad_year;
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter the present Semester                   : " << semes;
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter Student Class ID                       : " << Class;
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter Student ID you want to edit attendance : " << student_id;
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter date you want to edit (dd/mm/yyyy)     : " << date;
							cout << "\n\n";
							cout << "\t\t\t\t";
							cout << "    Enter new status (-1 or +1)                  : ";
							cin >> _New_Status;
						}
						text.replace(trd + 1, _Current_Status.length(), _New_Status);
						course_outfile << text << "\n";
					}
					else
						course_outfile << text << "\n";
				}
			}
			else
			{
				course_outfile << text << "\n";
				for (int i = 0; i < 12; i++)
				{
					getline(course_infile, text);
					course_outfile << text << "\n";
				}
			}
		}
		course_infile.close();
		course_outfile.close();
		if (_ID_Check)
		{
			if (_Valid_Date)
			{
				cout << "\n\n";
				cout << "\t\t\t\t\t\t";
				cout << "       Edited Successfully      ";
			}
			else
			{
				cout << "\n\n";
				cout << "\t\t\t\t\t\t";
				cout << "   Invalid date to check in";
			}
		}
		else
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "      No Student ID matched in this class";
		}
	}
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "    No any classes matched in this semester";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	char input;
	cout << "Do you want to edit more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Edit_Attendance(lect);
	}
	else
		show_Menu(lect);
}

//Import from csv
void Import_Scoreboard(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "          Import Scoreboard";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the semester of course            : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID to import scoreboard     : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter Course ID of scoreboard           : ";
	cin >> course_id;
	cout << "\n";
	cout << "\t\t\t\t";
	string score_csv; //csv file
	cout << "    Enter _path of score file with .csv     : ";
	cin >> score_csv;
	std::ifstream csv(score_csv);
	std::vector<string> score;
	string text;
	std::getline(csv, text);
	while (std::getline(csv, text))
	{
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		score.push_back(text.substr(trd + 1));
	}
	csv.close();
	string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	string result;
	std::ifstream course_infile(filename);
	if (!course_infile.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "     No suitable course or class";
	}
	else
	{
		string content;
		int index = 0;
		while (std::getline(course_infile, content))
		{
			if (index == score.size())
				break;
			int last = content.find_last_of(',');
			if (content.substr(last + 1) == Class)
			{
				result += content + "\n";
				result += score[index] + "\n";
				index++;
				std::getline(course_infile, content);
			}
			else
				result += content + "\n";
		}
		while (!course_infile.eof())
		{
			while (getline(course_infile, content))
				result += content + "\n";
		}
		course_infile.close();
		std::ofstream course_outfile(filename, std::ios::in | std::ios::trunc);
		course_outfile << result;
		course_outfile.close();
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "        Imported Successfully";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "  Do you want to import more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Import_Scoreboard(lect);
	}
	else
		show_Menu(lect);
}

void Edit_Grade(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "    Edit Grade of A Student";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester              : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Student Class ID                  : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string student_id;
	cout << "    Enter Student ID you want to edit grade : ";
	cin >> student_id;
	string course_id;
	string sche = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(sche);
	string content;
	bool check = 0;
	while (std::getline(sche_infile, content))
	{
		int fst = content.find_first_of(',');
		int snd = content.find(',', fst + 1);
		check = content.find(lect.user, 0) != string::npos;
		if (check)
		{
			course_id = content.substr(fst + 1, snd - (fst + 1));
			break;
		}
	}
	sche_infile.close();
	if (check)
	{
		string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream course_infile(filename);
		string result;
		string text;
		while (std::getline(course_infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			if (text.substr(fst + 1, snd - (fst + 1)) == student_id)
			{
				result += text + "\n";
				string midterm, final, bonus, total;
				cout << "\n";
				cout << "\t\t\t\t";
				cout << "    Enter new mid-term score    : ";
				cin >> midterm;
				cout << "\n";
				cout << "\t\t\t\t";
				cout << "    Enter new final score       : ";
				cin >> final;
				cout << "\n";
				cout << "\t\t\t\t";
				cout << "    Enter new bonus score       : ";
				cin >> bonus;
				cout << "\n";
				cout << "\t\t\t\t";
				cout << "    Re-write new total score    : ";
				cin >> total;
				result += midterm + "," + final + "," + bonus + "," + total + "\n";
				std::getline(course_infile, text);
			}
			else
				result += text + "\n";
		}
		course_infile.close();
		std::ofstream course_outfile(filename, std::ios::in | std::ios::trunc);
		course_outfile << std::fixed << result;
		course_outfile.close();
		cout << "\n\n";
		cout << "\t\t\t\t\t\t";
		cout << "       Edited Successfully      ";
	}
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "    No any classes matched in this semester";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	char input;
	cout << "Do you want to edit more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Edit_Grade(lect);
	}
	else
		show_Menu(lect);
}

void View_Scoreboard(Lecturer& lect)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "          View Scoreboard";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)         : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the semester of course            : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID you want to view         : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	string sche = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(sche);
	string content;
	bool check = 0;
	while (std::getline(sche_infile, content))
	{
		int fst = content.find_first_of(',');
		int snd = content.find(',', fst + 1);
		check = content.find(lect.user, 0) != string::npos;
		if (check)
		{
			course_id = content.substr(fst + 1, snd - (fst + 1));
			break;
		}
	}
	sche_infile.close();
	if (check)
	{
		cout << "\n\n";
		cout << "\t\tNo" << "\t    ID      " << "\tFullname\t\t" << "\tMid-term" << "     Final" << "     Bonus" << "     Total";
		string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream infile(filename);
		string text;
		while (std::getline(infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
			if (text.substr(fth + 1) == Class)
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
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "  No any classes matched in this semester";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "    Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Scoreboard(lect);
	}
	else
		show_Menu(lect);
}