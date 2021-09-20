#include "Project.h"
#include "Staff_Features.h"

static void show_Menu(Staff& staff);
static void Profile(Staff& staff);
static void Change_Pass(Staff& staff);

void Staff_Features(Staff& staff)
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
		show_Menu(staff);
		break;
	}

	case 2:
	{
		system("cls");
		Profile(staff);
		break;
	}

	case 3:
	{
		system("cls");
		Change_Pass(staff);
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
		cout << "       Invalid input!";
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Press Enter to choose again...";
		cin.get();
		Staff_Features(staff);
	}
	}
}

static void Profile(Staff& staff)
{
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Fullname        :    " << staff.fullname;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Gender          :    " << staff.gender;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Country         :    Viet Nam";
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Working at      :    Ho Chi Minh University of Science";
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Staff_Features(staff);
}

static void Change_Pass(Staff& staff)
{
	string current_Pass;
	string new_Pass;
	string retype;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t";
	cout << "Current Password     :    ";
	current_Pass = _Get_Pass();
	cin.ignore();
	while (current_Pass != staff.pass)
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
	in_File.open(_path._Staff);
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
			if (pass_pos == current_Pass && user_Name == staff.user)
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
	std::ofstream out_File(_path._Staff, std::ios::in | std::ios::trunc);
	result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
	out_File << result;
	out_File.close();
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "     Password changed successfully";
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	Staff_Features(staff);
}

static void show_Menu(Staff& staff)
{
	int choice;
	do
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t";
		cout << "      0. Go back to main page\n\n";
		cout << "\t";
		cout << "      1. Import Students                        | \t2. Add a new student\n\n";
		cout << "\t";
		cout << "      3. Edit student                           | \t4. Remove student\n\n";
		cout << "\t";
		cout << "      5. Change student from class A to class B | \t6. View list of classes\n\n";
		cout << "\t";
		cout << "      7. View list of students in a Class       | \t8. Create a Semester in year\n\n";
		cout << "\t";
		cout << "      9. View academic years                    | \t10. Import Schedule\n\n";
		cout << "\t";
		cout << "      11. Add a new course                      | \t12. Edit course\n\n";
		cout << "\t";
		cout << "      13. Remove course                         | \t14. Remove a student from a course\n\n";
		cout << "\t";
		cout << "      15. Add student to a course               | \t16. View list of courses in the current semester\n\n";
		cout << "\t";
		cout << "      17. View list of students of a course     | \t18. View attendance list of a course\n\n";
		cout << "\t";
		cout << "      19. Export attendance list of a course    | \t20. View all lecturers\n\n";
		cout << "\t";
		cout << "      21. View scoreboard                       | \t22. Export Scoreboard\n\n";
		cout << "\t\t\t\t\t";
		cout << "     Choose options:[0 -> 22]: ";
		cin >> choice;
	} while (cin.fail());
	switch (choice)
	{
	case 0:
	{
		system("cls");
		Staff_Features(staff);
		break;
	}

	case 1:
	{
		system("cls");
		Import(staff);
		break;
	}

	case 2:
	{
		system("cls");
		Add_Student(staff);
		break;
	}

	case 3:
	{
		system("cls");
		Edit_Student(staff);
		break;
	}

	case 4:
	{
		system("cls");
		Remove_Student(staff);
		break;
	}

	case 5:
	{
		system("cls");
		Class_Changing(staff);
		break;
	}

	case 6:
	{
		system("cls");
		View_Classes(staff);
		break;
	}

	case 7:
	{
		system("cls");
		View_Student_of_A_Class(staff);
		break;
	}

	case 8:
	{
		system("cls");
		Create_Semester(staff);
		break;
	}

	case 9:
	{
		system("cls");
		View_Academic_Years(staff);
		break;
	}

	case 10:
	{
		system("cls");
		Import_Schedule(staff);
		break;
	}

	case 11:
	{
		system("cls");
		Add_Course(staff);
		break;
	}

	case 12:
	{
		system("cls");
		Edit_Course(staff);
		break;
	}

	case 13:
	{
		system("cls");
		Remove_Course(staff);
		break;
	}

	case 14:
	{
		system("cls");
		Remove_Student_From_A_Course(staff);
		break;
	}

	case 15:
	{
		system("cls");
		Add_Student_To_Course(staff);
		break;
	}

	case 16:
	{
		system("cls");
		View_Courses(staff);
		break;
	}

	case 17:
	{
		system("cls");
		View_Students_of_A_Course(staff);
		break;
	}

	case 18:
	{
		system("cls");
		View_Attendance_of_A_Course(staff);
		break;
	}

	case 19:
	{
		system("cls");
		Export_Attendance(staff);
		break;
	}

	case 20:
	{
		system("cls");
		View_Lecturers(staff);
		break;
	}

	case 21:
	{
		system("cls");
		View_Scoreboard(staff);
		break;
	}

	case 22:
	{
		system("cls");
		Export_Scoreboard(staff);
		break;
	}

	default:
	{
		cout << "\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "         Invalid input!";
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "   Press Enter to choose again...";
		cin.get();
		show_Menu(staff);
	}
	}
}

void Load_Data_to_Students_txt(const string& File)
{
	std::ifstream class_File(File + ".txt");
	string text;
	int count = 0;
	std::ofstream out_File(_path._Student, std::ios::app);
	while (std::getline(class_File, text))
	{
		count++;
		int fst = text.find(',', 0);
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find(',', trd + 1);

		string user = text.substr(fst + 1, snd - (fst + 1));
		string fullname = text.substr(snd + 1, trd - (snd + 1));
		string temp = text.substr(trd + 1, fth - (trd + 1));
		int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		string begin_date = temp;
		temp.clear(); //temp is empty now
		fst = begin_date.find_first_of('/');
		int last = begin_date.find_last_of('/');
		int date;
		int month;
		int year;
		stringstream ss;
		ss << begin_date.substr(0, fst);
		ss >> date;
		ss.clear();
		ss << begin_date.substr(fst + 1, last - (fst + 1));
		ss >> month;
		ss.clear();
		ss << begin_date.substr(last + 1);
		ss >> year;
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			Month[2]++;
		if (date < 10 && month < 10)
			temp = "0" + std::to_string(date) + "/0" + std::to_string(month) + "/" + begin_date.substr(last + 1);
		else if (date >= 10 && month < 10)
			temp = std::to_string(date) + "/0" + std::to_string(month) + "/" + begin_date.substr(last + 1);
		else if (date < 10 && month >= 10)
			temp = "0" + std::to_string(date) + "/" + std::to_string(month) + "/" + begin_date.substr(last + 1);
		else
			temp = std::to_string(date) + "/" + std::to_string(month) + "/" + begin_date.substr(last + 1);
		string DoB = temp;
		temp.erase(std::remove(temp.begin(), temp.end(), '/'), temp.end()); //get rid of all "/"
		string pass = temp;
		string Class = text.substr(fth + 1);

		out_File << "\n";
		out_File << user << "," << pass << "," << fullname << "," << DoB << "," << Class;
	}
	class_File.close();
	out_File.close();

	std::ifstream in_tmpFile(_path._Student);
	int size = 0;
	in_tmpFile >> size;
	std::ofstream out_tmpFile(_path._Student, std::ios::in);
	out_tmpFile << size + count;
	in_tmpFile.close();
	out_tmpFile.close();
}

//Import from csv
void Import(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t";
	string class_ID;
	cout << "      Enter class ID for importing: ";
	cin >> class_ID;

	std::ifstream classes_File;
	classes_File.open("Classes.txt");
	if (classes_File.peek() == std::ifstream::traits_type::eof()) //check does the "classes.txt" exist any class or empty?
	{
		std::ofstream temp("temp.txt");
		temp << class_ID;
		std::ofstream one_Class; //create a new txt file for a specific class
		one_Class.open(class_ID + ".txt");
		cout << "\n";
		cout << "\t\t\t\t";
		string csv_File;   //input the name of csv file
		cout << "      Input directory _path of .csv file: ";
		cin >> csv_File;
		std::ifstream csv(csv_File);  //open csv file and start writing 
		string text;
		std::getline(csv, text);
		string result;
		while (!csv.eof())
		{
			std::getline(csv, text);
			result += text + "\n";
		}
		result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
		one_Class << result;
		cout << "\n";
		cout << "\t\t\t\t\t\t";
		cout << "Imported successfully";
		csv.close();
		one_Class.close();
		temp.close();
		classes_File.close();
		remove("Classes.txt");
		rename("temp.txt", "Classes.txt");
	}
	else // "classes.txt" is not empty
	{
		std::vector<string> Exist_Class;
		string text;
		while (!classes_File.eof())
		{
			std::getline(classes_File, text);
			Exist_Class.push_back(text);
		}
		// check to avoid duplication
		bool check = 0;
		std::for_each(Exist_Class.begin(), Exist_Class.end(), [&check, class_ID](const string& value)
			{
				if (value == class_ID)
					check = 1;
			});
		while (check == 1)
		{
			cout << "\n";
			cout << "\t\t\t\t\t";
			cout << "   Can not import to this class";
			cin.ignore();
			cin.get();
			system("cls");
			cout << "\n\n";
			cout << "\t\t\t\t";
			cout << "      Enter class ID for importing: ";
			cin >> class_ID;
			check = 0;
			std::for_each(Exist_Class.begin(), Exist_Class.end(), [&check, class_ID](const string& value)
				{
					if (value == class_ID)
						check = 1;
				});
		}
		// has prevented duplication
		std::ofstream out_File("Classes.txt", std::ios::app);
		out_File << "\n" << class_ID;
		std::ofstream one_Class; //create a new txt file for a specific class
		one_Class.open(class_ID + ".txt");
		cout << "\n";
		cout << "\t\t\t\t";
		string csv_File;   //input the name of csv file
		cout << "      Input directory _path of .csv file: ";
		cin >> csv_File;
		std::ifstream csv(csv_File);  //open csv file and start writing 
		string line;
		std::getline(csv, line);
		string temp;
		while (!csv.eof())
		{
			std::getline(csv, line);
			temp += line + "\n";
		}
		temp.erase(std::remove(temp.end() - 2, temp.end(), '\n'), temp.end());
		one_Class << temp;
		cout << "\n";
		cout << "\t\t\t\t\t\t";
		cout << "Imported successfully";
		classes_File.close();
		one_Class.close();
		out_File.close();
		csv.close();
	}
	Load_Data_to_Students_txt(class_ID);
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "   Do you want to import more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Import(staff);
	}
	else
		show_Menu(staff);
}

void Add_Student(Staff& staff)
{
	std::ifstream in_File(_path._Student);
	std::ofstream out_File(_path._Student, std::ios::in);
	int size;
	in_File >> size;
	out_File << size + 1;
	in_File.close();
	out_File.close();

	cout << "\n\n\n\n";
	cout << "\t\t\t\t\t";
	cout << "Enter the Information below:";
	string class_ID;
	cout << "\n\n";
	cout << "\t\t\t\t";
	cout << "Class ID                   : ";
	cin >> class_ID;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string fullname;
	cout << "Full name                  : ";
	std::getline(cin, fullname);
	cout << "\n";
	cout << "\t\t\t\t";
	string student_ID;
	cout << "Student ID                 : ";
	cin >> student_ID;
	cout << "\n";
	cout << "\t\t\t\t";
	string DoB;
	cout << "Date of Birth (dd/mm/yyyy) : ";
	cin >> DoB;
	int count = 0;
	for (int i = 0; i < DoB.size(); i++)
		if (DoB[i] == '/')
			count++;

	while (DoB.size() != 10 || count != 2)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "         Wrong Format";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.get();
		system("cls");
		cout << "\n\n\n\n";
		cout << "\t\t\t\t\t";
		cout << "Enter the Information below:";
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "Class ID                   : " << class_ID;
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "Full name                  : " << fullname;
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "Student ID                 : " << student_ID;
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "Date of Birth (dd/mm/yyyy) : ";
		cin >> DoB;
		count = 0;
		for (int i = 0; i < DoB.size(); i++)
			if (DoB[i] == '/')
				count++;
	}

	std::ifstream class_inFile(class_ID + ".txt");
	if (!class_inFile.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t      ";
		cout << "No any classes mathched this class";
	}
	else
	{
		string text;
		int count = 0;
		while (std::getline(class_inFile, text))
		{
			int fst = text.find_first_of(',');
			stringstream ss(text.substr(0, fst));
			ss >> count;
		}
		class_inFile.close();

		std::ofstream class_outFile(class_ID + ".txt", std::ios::app);
		class_outFile << "\n";
		class_outFile << count + 1 << "," << student_ID << "," << fullname << "," << DoB << "," << class_ID;
		class_outFile.close();

		string temp = DoB;
		temp.erase(std::remove(temp.begin(), temp.end(), '/'), temp.end());
		string pass = temp;
		std::ofstream student_File(_path._Student, std::ios::app);
		student_File << "\n";
		student_File << student_ID << "," << pass << "," << fullname << "," << DoB << "," << class_ID;
		student_File.close();

		cout << "\n";
		cout << "\t\t\t\t\t";
		cout << "   Added student successfully";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "Do you want to add more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Add_Student(staff);
	}
	else
		show_Menu(staff);
}

void Edit_Student(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	string student_class;
	cout << "Which class does the student belong to : ";
	cin >> student_class;
	cout << "\n";
	cout << "\t\t\t\t\t";
	string student_ID;
	cout << "What is the Student ID                 : ";
	cin >> student_ID;
	cout << "\n";
	cout << "\t\t\t\t\t";
	cin.ignore();
	string new_Name;
	cout << "Student new name                       : ";
	std::getline(cin, new_Name);
	cout << "\n";
	cout << "\t\t\t\t\t";
	string new_DoB;
	cout << "Student new Date of Birth (dd/mm/yyyy) : ";
	std::getline(cin, new_DoB);
	int count = 0;
	for (int i = 0; i < new_DoB.size(); i++)
		if (new_DoB[i] == '/')
			count++;
	while (new_DoB.size() != 10 || count != 2)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t\t";
		cout << "         Wrong Format";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.get();
		system("cls");
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Which class does the student belong to : " << student_class;
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "What is the Student ID                 : " << student_ID;
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Student new name                       : " << new_Name;
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Student new Date of Birth (dd/mm/yyyy) : ";
		std::getline(cin, new_DoB);
		count = 0;
		for (int i = 0; i < new_DoB.size(); i++)
			if (new_DoB[i] == '/')
				count++;
	}
	std::ifstream class_File(student_class + ".txt");
	if (!class_File.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "     No any classes matched this class";
	}
	else
	{
		string text;
		bool exist = 0;
		string result;
		int _No = 0;
		while (std::getline(class_File, text))
		{
			_No++;
			int fst = text.find(',', 0);
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find(',', trd + 1);

			if (text.substr(fst + 1, snd - (fst + 1)) == student_ID)
			{
				exist = 1;
				result += std::to_string(_No) + "," + student_ID + "," + new_Name + "," + new_DoB + "," + student_class + "\n";
			}
			else
			{
				result += text + "\n";
			}
		}
		class_File.close();
		result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
		std::ofstream out_File(student_class + ".txt", std::ios::out | std::ios::trunc); //19CLC.txt
		out_File << result;
		out_File.close();
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		if (exist == 0)
			cout << "      No Student matched in this class";
		else
		{
			cout << "        Edited student successfully";
			std::ifstream student_inFile(_path._Student);
			string _Result;
			student_inFile >> _Result;
			string line;
			string temp = new_DoB; // 01/01/2001
			temp.erase(std::remove(temp.begin(), temp.end(), '/'), temp.end());
			string pass = temp; // 01012001
			while (std::getline(student_inFile, line))
			{
				int fst = line.find(',', 0);
				int snd = line.find(',', fst + 1);
				int trd = line.find(',', snd + 1);
				int fth = line.find(',', trd + 1);

				if (line.substr(0, fst) == student_ID)
				{
					_Result += student_ID + "," + pass + "," + new_Name + "," + new_DoB + "," + student_class + "\n";
				}
				else
				{
					_Result += line + "\n";
				}
			}
			student_inFile.close();
			_Result.erase(std::remove(_Result.end() - 2, _Result.end(), '\n'), _Result.end());
			std::ofstream student_outFile(_path._Student, std::ios::in | std::ios::trunc); //Students.txt
			student_outFile << _Result;
			student_outFile.close();
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "      Do you want to edit more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Edit_Student(staff);
	}
	else
		show_Menu(staff);
}

void Remove_Student(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t";
	string student_ID;
	cout << "What is the Stundent ID you want to remove : ";
	cin >> student_ID;
	std::ifstream student_file(_path._Student);
	int size;
	student_file >> size;
	student_file.ignore();
	string Class;
	string text;
	bool exist = 0;
	size = 0; //start over
	string content;
	while (std::getline(student_file, text))
	{
		size++;
		int first = text.find_first_of(',');
		int last = text.find_last_of(',');
		if (text.substr(0, first) == student_ID)
		{
			Class = text.substr(last + 1);
			exist = 1;
			continue;
		}
		else
		{
			content += text + "\n";
		}
	}
	student_file.close();

	if (exist)
	{
		content.erase(std::remove(content.end() - 2, content.end(), '\n'), content.end());
		string _Result = std::to_string(size - 1) + "\n" + content;
		std::ofstream tempFile("temp.txt");
		tempFile << _Result;
		tempFile.close();
		remove(_path._Student.string().c_str());
		rename("temp.txt", _path._Student.string().c_str());
		string file = Class + ".txt";
		std::ifstream class_file(file);
		if (!class_file.is_open())
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "   No any classes matched this class";
		}
		else
		{

			std::ofstream out_File("temp.txt");
			string line;
			string result;
			while (std::getline(class_file, line))
			{
				int first = line.find_first_of(',');
				int snd = line.find(',', first + 1);
				if (line.substr(first + 1, snd - (first + 1)) == student_ID)
					continue;
				else
				{
					result += line + "\n";
				}
			}
			result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
			out_File << result;
			class_file.close();
			out_File.close();
			remove(file.c_str());
			rename("temp.txt", file.c_str());
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "      Removed student successfully";
		}
	}
	else
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "      There are no any ID matched    ";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "   Do you want to remove more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Remove_Student(staff);
	}
	else
		show_Menu(staff);
}

void Class_Changing(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	string student_class;
	cout << "What is the current class_ID of Student       : ";
	cin >> student_class;
	cout << "\n";
	cout << "\t\t\t\t\t";
	string student_id;
	cout << "What is the Student ID                        : ";
	cin >> student_id;
	string file = student_class + ".txt";
	std::ifstream current_Class(file); //19CLC.txt
	if (!current_Class.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "    There are no any classes matched";
	}
	else
	{

		std::ofstream tempFile("temp.txt");
		string text;
		string new_info;
		string temp;
		while (std::getline(current_Class, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			if (student_id == text.substr(fst + 1, snd - (fst + 1)))
				new_info = text;
			else
			{
				temp += text + "\n";
			}
		}
		temp.erase(std::remove(temp.end() - 2, temp.end(), '\n'), temp.end());
		tempFile << temp;
		current_Class.close();
		tempFile.close();
		remove(file.c_str());
		rename("temp.txt", file.c_str());
		cout << "\n";
		cout << "\t\t\t\t\t";
		string new_class;
		cout << "Which class do you want to move the Studen to : ";
		cin >> new_class;

		std::ifstream inFile(new_class + ".txt");
		if (!inFile.is_open())
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "    There are no any classes matched";
		}
		else
		{
			string line;
			string No;
			while (std::getline(inFile, line))
			{
				int fst = line.find_first_of(',');
				No = line.substr(0, fst);
			}
			inFile.close();

			stringstream ss(No);
			int count;
			ss >> count;
			int fst = new_info.find_first_of(',');
			int last = new_info.find_last_of(',');
			std::ofstream outFile(new_class + ".txt", std::ios::app);
			outFile << "\n";
			outFile << count + 1 << "," << new_info.substr(fst + 1, last - (fst + 1)) << "," << new_class;
			outFile.close();

			std::ifstream student_infile(_path._Student); //Students.txt
			string result;
			string content;
			while (std::getline(student_infile, content))
			{
				int fst = content.find_first_of(',');
				int last = content.find_last_of(',');
				string temp = content.substr(last + 1);
				if (content.substr(0, fst) == student_id)
				{
					content.replace(last + 1, temp.length(), new_class);
					result += content + "\n";
				}
				else
				{
					result += content + "\n";
				}
			}
			student_infile.close();
			std::ofstream student_outfile(_path._Student, std::ios::in | std::ios::trunc);
			result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
			student_outfile << result;
			student_outfile.close();
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "      Changed student successfully    ";
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "    Do you want to remove more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Class_Changing(staff);
	}
	else
		show_Menu(staff);
}

void View_Classes(Staff& staff)
{
	std::vector<string> classes;
	std::ifstream in_File("Classes.txt");
	string text;
	while (std::getline(in_File, text))
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t\t";
		cout << text;
	}
	in_File.close();
	cout << "\n\n";
	cout << "\t\t\t\t";
	wait();
	show_Menu(staff);
}

void View_Student_of_A_Class(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	string class_id;
	cout << "Which class do you want to view : ";
	cin >> class_id;
	std::ifstream class_file(class_id + ".txt");
	if (!class_file.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "       There are no any classes matched";
	}
	else
	{
		string text;
		cout << "\n";
		cout << "\t\tNo" << "\t    ID      " << "\tFullname\t" << "\t\tDate of Birth\t" << "    Class";
		while (std::getline(class_file, text))
		{
			if (text == "")
				continue;
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			int trd = text.find(',', snd + 1);
			int fth = text.find_last_of(',');
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
		class_file.close();
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "      Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Student_of_A_Class(staff);
	}
	else
		show_Menu(staff);
}

void Create_Semester(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Years (yyyy-yyyy) : ";
	cin >> acad_year;
	while (acad_year.size() != 9)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "Academic years can not be created";
		std::cin.ignore();
		std::cin.get();
		system("cls");
		cout << "\n\n";
		cout << "\t\t\t\t";
		cout << "    Enter Academic Years (yyyy-yyyy) : ";
		cin >> acad_year;
	}
	cout << "\n";
	cout << "\t\t\t\t";
	string semes;
	cout << "    Create a new Semester            : ";
	cin >> semes;
	string _Result = acad_year + "," + semes;
	std::ifstream infile("Semesters.txt");
	string text;
	bool check = 0; // No exist in file
	while (std::getline(infile, text))
	{
		if (text.compare(_Result) == 0)
		{
			check = 1;
			break;
		}
	}
	if (check)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "       Semester has already existed";
	}
	else
	{
		std::ofstream semester_File("Semesters.txt", std::ios::app);
		semester_File << _Result << "\n";
		semester_File.close();
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "      Semester created successfully";
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "    Do you want to create more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Create_Semester(staff);
	}
	else
		show_Menu(staff);
}

void View_Academic_Years(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Which academic years you want to view : ";
	cin >> acad_year;
	std::ifstream semester_File("Semesters.txt");
	std::vector<string> semes;
	int count = 0;
	string text;
	while (std::getline(semester_File, text))
	{
		int fst = text.find_first_of(',');
		if (text.substr(0, fst) == acad_year)
		{
			count++;
			semes.push_back(text.substr(fst + 1));
		}
		else
			continue;
	}
	semester_File.close();
	cout << "\n";
	cout << "\t\t\t\t\t";
	cout << "    There are " << count << " semesters in " << acad_year;
	for (auto item : semes)
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t\t\t   ";
		cout << item;
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t   ";
	wait();
	show_Menu(staff);
}

void Create_Course_txt(const string& acad_year, const string& semes, const string& Class, const std::vector<Course>& course_info)
{
	string filename = acad_year + "-" + semes + "-" + Class + "-";
	for (int i = 0; i < course_info.size(); i++)
	{
		std::ofstream each_course_txt(filename + course_info[i].course_id + ".txt");
		std::ifstream class_file(Class + ".txt");
		string text;
		while (std::getline(class_file, text))
		{
			each_course_txt << text << "\n";
			each_course_txt << "-1,-1,-1,-1" << "\n";
			int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			string begin_date = course_info[i].start_date;
			int fst = begin_date.find_first_of('/');
			int last = begin_date.find_last_of('/');
			int date;
			int month;
			int year;
			stringstream ss;
			ss << begin_date.substr(0, fst);
			ss >> date;
			ss.clear();
			ss << begin_date.substr(fst + 1, last - (fst + 1));
			ss >> month;
			ss.clear();
			ss << begin_date.substr(last + 1);
			ss >> year;
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
				Month[2]++;
			for (int j = 0; j < 10; j++)
			{
				if (date < Month[month])
				{
					if (date < 10 && month < 10)
						each_course_txt << "0" << std::to_string(date) << "/0" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else if (date >= 10 && month < 10)
						each_course_txt << std::to_string(date) << "/0" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else if (date < 10 && month >= 10)
						each_course_txt << "0" << std::to_string(date) << "/" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else
						each_course_txt << std::to_string(date) << "/" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					each_course_txt << "," << course_info[i].start_time << "," << course_info[i].end_time << ",-1\n";
					date += 7;
				}
				else
				{
					date -= Month[month];
					month++;
					if (date < 10 && month < 10)
						each_course_txt << "0" << std::to_string(date) << "/0" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else if (date >= 10 && month < 10)
						each_course_txt << std::to_string(date) << "/0" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else if (date < 10 && month >= 10)
						each_course_txt << "0" << std::to_string(date) << "/" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					else
						each_course_txt << std::to_string(date) << "/" << std::to_string(month) << "/" << begin_date.substr(last + 1);
					each_course_txt << "," << course_info[i].start_time << "," << course_info[i].end_time << ",-1\n";
					date += 7;
				}
			}
			each_course_txt << "\n";
		}
		each_course_txt.close();
		class_file.close();
	}
}

//Import from csv
void Import_Schedule(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "Import New Schedule For A Class";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)    : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester         : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Which Class for this schedule      : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string csv_File; //get csv file from user
	cout << "    Input directory _path of .csv file : ";
	cin >> csv_File;
	string filename = acad_year + "-" + semes + "-Schedule-" + Class;
	std::ifstream csv(csv_File); //open csv to read
	string text;
	std::getline(csv, text);
	string result;
	std::vector<string> temp;
	while (std::getline(csv, text))
	{
		temp.push_back(text);
		result += text + "\n";
	}
	csv.close();
	result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
	std::ofstream out_File(filename + ".txt");
	out_File << result;
	out_File.close();
	std::vector<Course> course_info;
	std::vector<string> lect_info;
	for (int i = 0; i < temp.size(); i++)
	{
		std::vector<int> pos_of_comma;
		for (int j = 0; j < temp[i].size(); j++)
			if (temp[i][j] == ',')
				pos_of_comma.push_back(j);
		lect_info.push_back(temp[i].substr(pos_of_comma[3] + 1, pos_of_comma[7] - (pos_of_comma[3] + 1))); //user,fullname,degree,gender
		Course info;
		info.course_id = temp[i].substr(pos_of_comma[0] + 1, pos_of_comma[1] - (pos_of_comma[0] + 1));     //get course id
		info.start_date = temp[i].substr(pos_of_comma[7] + 1, pos_of_comma[8] - (pos_of_comma[7] + 1));    //get start date
		info.end_date = temp[i].substr(pos_of_comma[8] + 1, pos_of_comma[9] - (pos_of_comma[8] + 1));      //get end date
		info.start_time = temp[i].substr(pos_of_comma[10] + 1, pos_of_comma[11] - (pos_of_comma[10] + 1)); //get start time
		info.end_time = temp[i].substr(pos_of_comma[11] + 1, pos_of_comma[12] - (pos_of_comma[11] + 1));   //get end time
		course_info.push_back(info);
	}
	Create_Course_txt(acad_year, semes, Class, course_info);
	for (int i = 0; i < lect_info.size(); i++) //open Lecturer.txt
	{
		bool check = 0;
		int fst = lect_info[i].find_first_of(',');
		std::ifstream lect_file(_path._Lecturer);
		string content;
		while (std::getline(lect_file, content))
		{
			int first = content.find_first_of(',');
			if (content.substr(0, first) == lect_info[i].substr(0, fst)) //Check if exited or not
			{
				check = 1;
				break;
			}
			else
				continue;
		}
		lect_file.close();
		if (check == 0) //Can insert to file
		{
			std::ofstream lect_outfile(_path._Lecturer, std::ios::app);
			lect_outfile << "\n" << lect_info[i].substr(0, fst) << "," << lect_info[i];
			lect_outfile.close();
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "Imported successfully";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "   Do you want to import more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Import_Schedule(staff);
	}
	else
		show_Menu(staff);
}

void Add_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Import A New Course For Class";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)   : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester        : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Which Class for this course       : ";
	cin >> Class;
	string filename = acad_year + "-" + semes + "-Schedule-" + Class;
	std::ifstream schedule_infile(filename + ".txt");
	string text;
	int count = 0;
	while (std::getline(schedule_infile, text))
	{
		int fst = text.find_first_of(',');
		stringstream ss(text.substr(0, fst));
		ss >> count;
	}
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter course ID                   : ";
	cin >> course_id;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string course_name;
	cout << "    What is the name of course        : ";
	std::getline(cin, course_name);
	cout << "\n";
	cout << "\t\t\t\t";
	string user;
	cout << "    What is Lecturer's user name      : ";
	cin >> user;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string lect;
	cout << "    What is Lecturer's full name      : ";
	std::getline(cin, lect);
	cout << "\n";
	cout << "\t\t\t\t";
	string degree;
	cout << "    Enter Lecturer's degree           : ";
	cin >> degree;
	cout << "\n";
	cout << "\t\t\t\t";
	string gender;
	cout << "    Enter gender                      : ";
	cin >> gender;
	cout << "\n";
	cout << "\t\t\t\t";
	string start_date;
	cout << "    When is the beginning date        : ";
	cin >> start_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string end_date;
	cout << "    When is the finished date         : ";
	cin >> end_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string work_date;
	cout << "    Enter the working date            : ";
	cin >> work_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string start_time;
	cout << "    What time the lesson start        : ";
	cin >> start_time;
	cout << "\n";
	cout << "\t\t\t\t";
	string end_time;
	cout << "    What time the lesson end          : ";
	cin >> end_time;
	cout << "\n";
	cout << "\t\t\t\t";
	string room;
	cout << "    Enter the Room ID of course       : ";
	cin >> room;
	string result = std::to_string(count + 1) + ","
		+ course_id + "," + course_name + ","
		+ Class + "," + user + "," + lect + ","
		+ degree + "," + gender + ","
		+ start_date + "," + end_date + ","
		+ work_date + "," + start_time + ","
		+ end_time + "," + room;
	std::ofstream sche_outfile(filename + ".txt", std::ios::app);
	sche_outfile << "\n" << result;
	string lect_info = user + "," + user + "," + lect + "," + degree + "," + gender;
	for (int i = 0; i < 1; i++)
	{
		bool check = 0;
		std::ifstream lect_file(_path._Lecturer);
		string content;
		while (std::getline(lect_file, content))
		{
			int first = content.find_first_of(',');
			if (content.substr(0, first) == user)
			{
				check = 1;
				break;
			}
			else
				continue;
		}
		lect_file.close();
		if (check == 0)
		{
			std::ofstream lect_outfile(_path._Lecturer, std::ios::app);
			lect_outfile << "\n" << lect_info;
			lect_outfile.close();
		}
	}
	Course info;
	info.course_id = course_id;
	info.start_date = start_date;
	info.end_date = end_date;
	info.start_time = start_time;
	info.end_time = end_time;
	std::vector<Course> course_info;
	course_info.push_back(info);
	Create_Course_txt(acad_year, semes, Class, course_info);
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Course Added Successfully";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << " Do you want to add more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Add_Course(staff);
	}
	else
		show_Menu(staff);
}

void Edit_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Edit an existing course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)   : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester        : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Which Class for this course       : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter course ID you want to edit  : ";
	cin >> course_id;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string course_name;
	cout << "    What is the name of course        : ";
	std::getline(cin, course_name);
	cout << "\n";
	cout << "\t\t\t\t";
	string user;
	cout << "    Enter Lecturer's new user name    : ";
	cin >> user;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string lect;
	cout << "    What is Lecturer's full name      : ";
	std::getline(cin, lect);
	cout << "\n";
	cout << "\t\t\t\t";
	string degree;
	cout << "    Enter Lecturer's degree           : ";
	cin >> degree;
	cout << "\n";
	cout << "\t\t\t\t";
	string gender;
	cout << "    Enter gender                      : ";
	cin >> gender;
	cout << "\n";
	cout << "\t\t\t\t";
	string start_date;
	cout << "    Enter new beginning date          : ";
	cin >> start_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string end_date;
	cout << "    Enter new finished date           : ";
	cin >> end_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string work_date;
	cout << "    Enter new working date            : ";
	cin >> work_date;
	cout << "\n";
	cout << "\t\t\t\t";
	string start_time;
	cout << "    Enter new start time of lesson    : ";
	cin >> start_time;
	cout << "\n";
	cout << "\t\t\t\t";
	string end_time;
	cout << "    Enter new end time of lesson      : ";
	cin >> end_time;
	cout << "\n";
	cout << "\t\t\t\t";
	string room;
	cout << "    Enter new Room ID of course       : ";
	cin >> room;
	string result = course_id + "," + course_name + ","
		+ Class + "," + user + "," + lect + ","
		+ degree + "," + gender + ","
		+ start_date + "," + end_date + ","
		+ work_date + "," + start_time + ","
		+ end_time + "," + room;
	string filename = acad_year + "-" + semes + "-Schedule-" + Class + ".txt"; //Schedule file.txt
	int count = 0;
	std::ifstream schedule_infile(filename);
	string text;
	string temp;
	while (std::getline(schedule_infile, text))
	{
		count++;
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		if (text.substr(fst + 1, snd - (fst + 1)) == course_id)
			temp += std::to_string(count) + "," + result + "\n";
		else
			temp += text + "\n";
	}
	schedule_infile.close();
	temp.erase(std::remove(temp.end() - 2, temp.end(), '\n'), temp.end());
	std::ofstream outFile("temp.txt");
	outFile << temp;
	outFile.close();
	remove(filename.c_str());
	rename("temp.txt", filename.c_str());
	string course_file = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	remove(course_file.c_str());
	Course info;
	info.course_id = course_id;
	info.start_date = start_date;
	info.end_date = end_date;
	info.start_time = start_time;
	info.end_time = end_time;
	std::vector<Course> course_info;
	course_info.push_back(info);
	Create_Course_txt(acad_year, semes, Class, course_info);
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Course Edited Successfully";
	cout << "\n\n";
	cout << "\t\t\t\t";
	char input;
	cout << "        Do you want to edit more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Edit_Course(staff);
	}
	else
		show_Menu(staff);
}

void Remove_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Remove A Course For Class";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)       : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester            : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Which Class you want to remove course : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter a course_id you want to remove  : ";
	cin >> course_id;
	string filename = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream schedule_infile(filename); //Schedule file.txt
	string text;
	string result;
	while (std::getline(schedule_infile, text))
	{
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		if (text.substr(fst + 1, snd - (fst + 1)) == course_id)
			continue;
		else
			result += text + "\n";
	}
	schedule_infile.close();
	result.erase(std::remove(result.end() - 2, result.end(), '\n'), result.end());
	std::ofstream outfile("temp.txt");
	outfile << result;
	outfile.close();
	remove(filename.c_str());
	rename("temp.txt", filename.c_str());
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Course Removed Successfully";
	cout << "\n\n";
	cout << "\t\t\t\t";
	char input;
	cout << "        Do you want to remove more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Remove_Course(staff);
	}
	else
		show_Menu(staff);
}

void Remove_Student_From_A_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Remove A Student From A Course";
	cout << "\n\n";
	cout << "\t\t\t\t";
	string acad_year;
	cout << "    Enter Academic Year (yyyy-yyyy)        : ";
	cin >> acad_year;
	cout << "\n";
	cout << "\t\t\t\t";
	string	semes;
	cout << "    Enter the present Semester             : ";
	cin >> semes;
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID of the course           : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter a course_id you want to remove   : ";
	cin >> course_id;
	cout << "\n";
	cout << "\t\t\t\t";
	string student_id;
	cout << "    What is Student id you want to remove  : ";
	cin >> student_id;
	string course_txt = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	string text;
	std::ifstream course_file(course_txt);
	if (!course_file.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "        No any courses matched";
	}
	else
	{
		std::ofstream outfile("temp.txt");
		bool check = 0; //No exist
		while (std::getline(course_file, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			if (text.substr(fst + 1, snd - (fst + 1)) == student_id) //Have this student in course
			{
				check = 1;
				for (int i = 0; i < 12; i++)
					std::getline(course_file, text);
			}
			else
				outfile << text << "\n";
		}
		course_file.close();
		outfile.close();
		remove(course_txt.c_str());
		rename("temp.txt", course_txt.c_str());
		if (check)
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "      Student Removed Successfully";
		}
		else
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "        No student in this course";
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "    Do you want to remove more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Remove_Student_From_A_Course(staff);
	}
	else
		show_Menu(staff);
}

void Add_Student_To_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    Add Student To A Course";
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
	cout << "    Enter Class ID you want to add          : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter a course_id you want to add       : ";
	cin >> course_id;
	cout << "\n";
	cout << "\t\t\t\t";
	string student_id;
	cout << "    What is Student id you want to add      : ";
	cin >> student_id;
	cout << "\n";
	cout << "\t\t\t\t";
	cin.ignore();
	string fullname;
	cout << "    Enter Student full name                 : ";
	std::getline(cin, fullname);
	cout << "\n";
	cout << "\t\t\t\t";
	string DoB;
	cout << "    Enter Student Date of Birth(dd/mm/yyyy) : ";
	cin >> DoB;
	string filename = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream sche_infile(filename); //Schedule of a course file.txt
	if (!sche_infile.is_open())
	{
		cout << "\n\n";
		cout << "\t\t\t\t\t";
		cout << "    No any suitable course";
	}
	else
	{
		string course;
		string text;
		while (std::getline(sche_infile, text))
		{
			int fst = text.find_first_of(',');
			int snd = text.find(',', fst + 1);
			if (text.substr(fst + 1, snd - (fst + 1)) == course_id)
				course = text;
		}
		std::vector<int> pos_of_comma;
		for (int i = 0; i < course.size(); i++)
			if (course[i] == ',')
				pos_of_comma.push_back(i);
		int count = 0;
		string course_file = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
		std::ifstream infile(course_file);
		if (!infile.is_open())
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "    No any suitable course";
		}
		else
		{
			string content;
			while (std::getline(infile, content))
			{
				int fst = content.find_first_of(',');
				int last = content.find_last_of(',');
				if (content.substr(last + 1) == Class)
				{
					stringstream ss(content.substr(0, fst));
					ss >> count;
				}
			}
			infile.close();
			std::ofstream outfile(course_file, std::ios::app);
			outfile << std::to_string(count + 1) << "," << student_id << "," << fullname << "," << DoB << "," << Class << "\n";
			outfile << "-1,-1,-1,-1\n";
			int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			string start_time = course.substr(pos_of_comma[10] + 1, pos_of_comma[11] - (pos_of_comma[10] + 1));
			string end_time = course.substr(pos_of_comma[11] + 1, pos_of_comma[12] - (pos_of_comma[11] + 1));
			string start_date = course.substr(pos_of_comma[7] + 1, pos_of_comma[8] - (pos_of_comma[7] + 1));
			int fst = start_date.find_first_of('/');
			int last = start_date.find_last_of('/');
			int date;
			int month;
			int year;
			stringstream ss;
			ss << start_date.substr(0, fst);
			ss >> date;
			ss.clear();
			ss << start_date.substr(fst + 1, last - (fst + 1));
			ss >> month;
			ss.clear();
			ss << start_date.substr(last + 1);
			ss >> year;
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
				Month[2]++;
			for (int j = 0; j < 10; j++)
			{
				if (date < Month[month])
				{
					if (date < 10 && month < 10)
						outfile << "0" << std::to_string(date) << "/0" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else if (date >= 10 && month < 10)
						outfile << std::to_string(date) << "/0" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else if (date < 10 && month >= 10)
						outfile << "0" << std::to_string(date) << "/" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else
						outfile << std::to_string(date) << "/" << std::to_string(month) << "/" << start_date.substr(last + 1);
					outfile << "," << start_time << "," << end_time << ",-1\n";
					date += 7;
				}
				else
				{
					date -= Month[month];
					month++;
					if (date < 10 && month < 10)
						outfile << "0" << std::to_string(date) << "/0" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else if (date >= 10 && month < 10)
						outfile << std::to_string(date) << "/0" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else if (date < 10 && month >= 10)
						outfile << "0" << std::to_string(date) << "/" << std::to_string(month) << "/" << start_date.substr(last + 1);
					else
						outfile << std::to_string(date) << "/" << std::to_string(month) << "/" << start_date.substr(last + 1);
					outfile << "," << start_time << "," << end_time << ",-1\n";
					date += 7;
				}
			}
			outfile << "\n";
			outfile.close();
			cout << "\n\n";
			cout << "\t\t\t\t\t";
			cout << "   Student Added Successfully";
		}
	}
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << " Do you want to add more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Add_Student_To_Course(staff);
	}
	else
		show_Menu(staff);
}

void View_Courses(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    View Courses of Semester";
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
	cout << "\n";
	cout << "\t\t\t\t";
	string Class;
	cout << "    Enter Class ID you want to view         : ";
	cin >> Class;
	cout << "\n\n";
	string filename = acad_year + "-" + semes + "-Schedule-" + Class + ".txt";
	std::ifstream infile(filename);
	std::string text;
	while (std::getline(infile, text))
	{
		std::replace(text.begin(), text.end(), ',', ' ');
		cout << "  " << text;
		cout << "\n\n";
	}
	infile.close();
	cout << "\n";
	cout << "\t\t\t\t";
	char input;
	cout << "        Do you want to view more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Courses(staff);
	}
	else
		show_Menu(staff);
}

void View_Students_of_A_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    View Students of a Course";
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
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter a course_id you want to view      : ";
	cin >> course_id;
	cout << "\n\n";
	cout << "\t\tNo" << "\t    ID      " << "\tFullname\t" << "\t\tDate of Birth\t" << "    Class";
	std::string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	std::ifstream infile(filename);
	std::string text;
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
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Students_of_A_Course(staff);
	}
	else
		show_Menu(staff);
}

void View_Attendance_of_A_Course(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "    View Attendance of a Course";
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
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter a course_id you want to view      : ";
	cin >> course_id;
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
	cout << "\n\n";
	cout << "\t\t\t\t\t    ";
	char input;
	cout << "Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Attendance_of_A_Course(staff);
	}
	else
		show_Menu(staff);
}

void Export_Attendance(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "       Export Attendance List";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "   You must enter the source file";
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
	cout << "    Enter Class ID you want to export       : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter Course ID you want to export      : ";
	cin >> course_id;
	std::string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	string result;
	std::ifstream infile(filename);
	std::string text;
	while (std::getline(infile, text))
	{
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find_last_of(',');
		if (text.substr(fth + 1) == Class)
		{
			result += text + "\n";
			std::getline(infile, text);
		}
		else
			result += text + "\n";
	}
	infile.close();
	string csv_file = filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + "-Attendance.csv";
	std::ofstream outfile(csv_file);
	outfile << "No,ID,Fullname,Date of Birth,Class\n";
	outfile << result;
	outfile.close();
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "       Exported Successfully";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "   Do you want to export more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Export_Attendance(staff);
	}
	else
		show_Menu(staff);
}

void View_Lecturers(Staff& staff)
{
	std::ifstream lect_file(_path._Lecturer);
	string text;
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "List of Lecturers";
	cout << "\n\n";
	cout << "\t\t\t\tFullname\t" << "\tDegree\t\t" << "    Gender";
	while (std::getline(lect_file, text))
	{
		if (text == "")
			continue;
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find_last_of(',');
		cout << "\n\n";
		cout << "\t\t\t\t" << text.substr(snd + 1, trd - (snd + 1));
		string temp_name = text.substr(snd + 1, trd - (snd + 1));
		for (int i = 0; i < 24 - temp_name.size(); i++)
			cout << " ";
		cout << text.substr(trd + 1, fth - (trd + 1));
		string temp_dob = text.substr(trd + 1, fth - (trd + 1));
		for (int i = 0; i < 20 - temp_dob.size(); i++)
			cout << " ";
		cout << text.substr(fth + 1);
	}
	lect_file.close();
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	wait();
	show_Menu(staff);
}

void View_Scoreboard(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "               View Scoreboard";
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
	cout << "    Enter Course ID you want to view        : ";
	cin >> course_id;
	std::string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	cout << "\n\n";
	cout << "\t\tNo" << "\t    ID      " << "\tFullname\t\t" << "\tMid-term" << "     Final" << "     Bonus" << "     Total";
	std::ifstream infile(filename);
	std::string text;
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
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "      Do you want to keep viewing?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		View_Scoreboard(staff);
	}
	else
		show_Menu(staff);
}

void Export_Scoreboard(Staff& staff)
{
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "       Export Scoreboard";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "You must enter the source file";
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
	cout << "    Enter Class ID you want to export       : ";
	cin >> Class;
	cout << "\n";
	cout << "\t\t\t\t";
	string course_id;
	cout << "    Enter Course ID you want to export      : ";
	cin >> course_id;
	std::string filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + ".txt";
	string result;
	std::ifstream infile(filename);
	std::string text;
	while (std::getline(infile, text))
	{
		int fst = text.find_first_of(',');
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find_last_of(',');
		if (text.substr(fth + 1) == Class)
		{
			result += text.substr(0, fst) + ","
				+ text.substr(fst + 1, snd - (fst + 1)) + ","
				+ text.substr(snd + 1, trd - (snd + 1)) + ",";
			std::getline(infile, text);
			result += text + "\n";
		}
		else
			continue;
	}
	infile.close();
	string csv_file = filename = acad_year + "-" + semes + "-" + Class + "-" + course_id + "-Scoreboard.csv";
	std::ofstream outfile(csv_file);
	outfile << "No,ID,Fullname,Mid-term,Final,Bonus,Total\n";
	outfile << result;
	outfile.close();
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	cout << "     Exported Successfully";
	cout << "\n\n";
	cout << "\t\t\t\t\t";
	char input;
	cout << "Do you want to export more?(Y/N): ";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		system("cls");
		Export_Scoreboard(staff);
	}
	else
		show_Menu(staff);
}