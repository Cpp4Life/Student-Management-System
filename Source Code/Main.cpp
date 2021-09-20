#include "Project.h"
#include "Timer.h"

std::vector<Staff> staff_Info(std::ifstream& File)
{
	int size;
	File >> size;
	std::vector<Staff> staff;
	string text;
	File.ignore();
	while (std::getline(File, text, '\n'))
	{
		int fst = text.find(',', 0);
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);

		Staff info;
		info.user = text.substr(0, fst);
		info.pass = text.substr(fst + 1, snd - (fst + 1));
		info.fullname = text.substr(snd + 1, trd - (snd + 1));
		info.gender = text.substr(trd + 1);

		staff.push_back(info);
	}
	return staff;
}

std::vector<Lecturer> lect_Info(std::ifstream& File)
{
	std::vector<Lecturer> Lect;
	string text;
	while (std::getline(File, text))
	{
		int fst = text.find(',', 0);
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find(',', trd + 1);

		Lecturer info;
		info.user = text.substr(0, fst);
		info.pass = text.substr(fst + 1, snd - (fst + 1));
		info.fullname = text.substr(snd + 1, trd - (snd + 1));
		info.degree = text.substr(trd + 1, fth - (trd + 1));
		info.gender = text.substr(fth + 1);

		Lect.push_back(info);
	}
	return Lect;
}

std::vector<Student> student_Info(std::ifstream& File)
{
	int size;
	File >> size;
	std::vector<Student> student;
	string text;
	File.ignore();
	while (std::getline(File, text))
	{
		int fst = text.find(',', 0);
		int snd = text.find(',', fst + 1);
		int trd = text.find(',', snd + 1);
		int fth = text.find(',', trd + 1);

		Student info;
		info.user = text.substr(0, fst);
		info.pass = text.substr(fst + 1, snd - (fst + 1));
		info.fullname = text.substr(snd + 1, trd - (snd + 1));
		info.DoB = text.substr(trd + 1, fth - (trd + 1));
		info.Class = text.substr(fth + 1);

		student.push_back(info);
	}
	return student;
}

void Load_Alldata(std::vector<Staff>& staff, std::vector<Lecturer>& lecturer, std::vector<Student>& student)
{
	std::ifstream staffFile;
	staffFile.open(_path._Staff);
	if (!staffFile.is_open())
		cout << "File not existed\n";
	else
	{
		staff = staff_Info(staffFile);
		staffFile.close();
	}

	std::ifstream LectFile;
	LectFile.open(_path._Lecturer);
	if (!LectFile.is_open())
		cout << "File not existed\n";
	else
	{
		lecturer = lect_Info(LectFile);
		LectFile.close();
	}

	std::ifstream StdFile;
	StdFile.open(_path._Student);
	if (!StdFile.is_open())
		cout << "File not existed\n";
	else
	{
		student = student_Info(StdFile);
		StdFile.close();
	}
}

int main()
{
	mainpage();

	std::vector<Staff> staff;
	std::vector<Lecturer> lecturer;
	std::vector<Student> student;
	{
		Timer timer;
		Load_Alldata(staff, lecturer, student);
	}
	std::cin.get();
	logscreen(staff, lecturer, student);

	std::cin.get();
}