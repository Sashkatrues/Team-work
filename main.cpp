#include "header.h"

int main()
{
    try
    {
        std::ifstream fin_s("list_of_students.txt");
        CheckInputFile(fin_s);
        std::ifstream fin_g("list_of_student_grades.txt");
        CheckInputFile(fin_g);
        std::fstream bin_s("students.bin", std::ios::out | std::ios::binary);
        CheckOutputFile(bin_s);
        std::fstream bin_g("grades.bin", std::ios::out | std::ios::binary);
        CheckOutputFile(bin_g);
        int32_t size{ CountStudents(fin_s) };
        std::string* students = new std::string[size];
        InputStudents(fin_s, students, size);
        CreateStudentBinary(bin_s, students, size);
        std::string* grades = new std::string[size];
        InputGrades(fin_g, grades, size);
        CreateGradeBinary(bin_g, grades, size);


        for (int32_t i{}; i < size; ++i) {
            size_t p1 = students[i].find(';');
            size_t p2 = students[i].find(';', p1 + 1);
            for (int32_t j{}; j < size; ++j) {
                size_t gp1 = grades[j].find(';');
                size_t gp2 = grades[j].find(';', gp1 + 1);

                if ((students[i].substr(0, p1) == grades[j].substr(gp1 + 1, gp2 - gp1 - 1))) {
                    std::cout << i << " " << j << " " << students[i].substr(0, p1);
                    std::cout << '\n';

                    grades[j] = students[i].substr(p1 + 1, p2 - p1 - 1) + ";" + grades[j] + "\n";
                    break;
                }
            }
        }
        std::fstream bin_gg("fullgrades.bin", std::ios::out | std::ios::binary);
        CheckOutputFile(bin_gg);
        for (int32_t i{}; i < size; ++i) {
            bin_gg.write(grades[i].c_str(), grades[i].size());
        }

        delete[] students;
        delete[] grades;
        bin_s.close();
        bin_g.close();
        bin_gg.close();

       
        processFile("fullgrades.bin", "average_grades.bin");
        std::cout << "Complite.\n";

    }
    catch (const char* msg) {
        std::cerr << msg;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

	return 0;
}
		
