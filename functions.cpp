#include "header.h"


void CheckInputFile(std::ifstream& fin)
{
    if (!fin.good())
    {
        throw "file doesn't exist\n";
    }
    if (!fin)
    {
        throw "input file error\n";
    }
    if (fin.peek() == EOF)
    {
        throw "file is empty\n";
    }
}

void CheckOutputFile(std::fstream& fout)
{
    if (!fout.good())
    {
        throw "file doesn't exist\n";
    }
    if (!fout)
    {
        throw "output file error\n";
    }
}


int32_t CountStudents(std::ifstream& fin)
{
    fin.clear();
    fin.seekg(0, std::ios::beg);
    std::string temp;
    int32_t count{};
    while (getline(fin, temp))
    {
        ++count;
    }
    return count;
}


void InputStudents(std::ifstream& fin, std::string* array, int32_t size)
{
    fin.clear();
    fin.seekg(0, std::ios::beg);
    for (int32_t i{}; i < size; ++i)
    {
        getline(fin, array[i]);
    }
    fin.close();
}


void CreateStudentBinary(std::fstream& bin, std::string* array, int32_t size)
{
    for (int32_t i{}; i < size; ++i)
    {
        bin.write(array[i].c_str(),  array[i].length());
    }
}


void InputGrades(std::ifstream& fin, std::string* array, int32_t size)
{
    fin.clear();
    fin.seekg(0, std::ios::beg);
    for (int32_t i{}; i < size; ++i)
    {
        getline(fin, array[i]);
    }
    fin.close();
}


void CreateGradeBinary(std::fstream& bin, std::string* array, int32_t size)
{
    for (int32_t i{}; i < size; ++i)
    {
        bin.write(array[i].c_str(), array[i].length());
    }
    bin.close();
}

void TaskA (){
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
    catch (const char* msg) {
        std::cerr << msg;
    }
}