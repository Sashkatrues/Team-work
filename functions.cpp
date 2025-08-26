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
        bin.write(" ", 1);
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
        bin.write(" ", 1);
    }
    bin.close();
}


