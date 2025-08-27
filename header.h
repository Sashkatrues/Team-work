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
double calculateAverage(const std::string&, std::string&, std::string&, std::string&);
void processFile(const std::string&, const std::string&);
void CreateListWithFools(std::string*&, int32_t);
void CreateArray(std::ifstream&, std::string*&, int32_t);
std::string* CreateFoolsArray(std::string*&, int32_t, int32_t);
int32_t CountFools(std::string*&, int32_t);
int32_t CountGroupStudents(std::string*&, int32_t, int32_t);
int32_t CountFoolsInBin(std::ifstream& fin);
void ExtractNamesAndGroups(const std::string*, int32_t, std::string*&, int32_t*&);
bool compareIndices(int32_t, int32_t, const int32_t*, const std::string*);
void myQuickSort(int32_t*, int32_t, int32_t, const int32_t*, const std::string*);
void SortIndices(int32_t, int32_t*&, const int32_t*, const std::string*);
void CreateSortedFoolsBin(const std::string*, const int32_t*, int32_t);
std::string* CreateGroupArray(std::string*&, int32_t, int32_t, int32_t);
bool СompareBySurname(const std::string&, const std::string&);
void SortGroupBySurnames(std::string*&, int32_t);
void CreateSortedGroupList(std::string*&, int32_t);
bool CompareByAverageDescending(const std::string&, const std::string&);
void SortGroupByAverageDescending(std::string*&, int32_t);
void CreateSortedGroupAverageList(std::string*&, int32_t);
std::string* CreateGeniusArray(std::string*&, int32_t, int32_t);
int32_t CountGenius(std::string*&, int32_t);
void CreateListWithGenius(std::string*&, int32_t);
#endif
