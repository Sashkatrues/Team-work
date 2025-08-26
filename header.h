#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

struct fullStudent {

};

struct Student 
{
    int32_t id;
    std::string surname;
    std::string name;
    std::string fathername;
};


struct Grade
{
    int32_t group;
    int32_t id;
    int32_t math;
    int32_t geo;
    int32_t prog;
};

void CheckInputFile(std::ifstream&);
void CheckOutputFile(std::fstream&);

int32_t CountStudents(std::ifstream&);
void InputStudents(std::ifstream&, std::string*, int32_t);
void TaskA();

void CreateStudentBinary(std::fstream&, std::string*, int32_t);
void InputGrades(std::ifstream&, std::string*, int32_t);
void CreateGradeBinary(std::fstream&, std::string*, int32_t);

#endif