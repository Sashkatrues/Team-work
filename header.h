#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

void CheckInputFile(std::ifstream&);
void CheckOutputFile(std::fstream&);
int32_t CountStudents(std::ifstream&);
void InputStudents(std::ifstream&, std::string*, int32_t);
void CreateStudentBinary(std::fstream&, std::string*, int32_t);
void InputGrades(std::ifstream&, std::string*, int32_t);
void CreateGradeBinary(std::fstream&, std::string*, int32_t);
double calculateAverage(const std::string& line, std::string& name, std::string& group, std::string& id);
void processFile(const std::string&, const std::string&);

#endif

