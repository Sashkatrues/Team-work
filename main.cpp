#include "header.h"


int main()
{
	try
	{
		std::ifstream fin_s("list_of_students.txt");
		CheckInputFile(fin_s);
		std::ifstream fin_g("list_of_student_grades.txt");
		CheckInputFile(fin_g);
		std::fstream bin_s("students.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_s);
		std::fstream bin_g("grades.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_g);

		int32_t size{ CountStudents(fin_s) };
		std::string* students = new std::string[size];
		InputStudents(fin_s, students, size);
		CreateStudentBinary(bin_s, students, size);
		
		std::string* grades = new std::string[size];
		InputGrades(fin_g, grades, size);
		CreateGradeBinary(bin_g, grades, size);

		fin_s.close();
		fin_g.close();
		bin_s.close();
		bin_g.close();


	}
	catch (const char* msg) { std::cerr << msg; }
	return 0;
}