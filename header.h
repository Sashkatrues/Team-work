

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
void CreateBinary(std::fstream&, std::string*, int32_t);
void InputGrades(std::ifstream&, std::string*, int32_t);
void MergeStudentDataWithGrades(std::string*, std::string*, int32_t);
double calculateAverage(const std::string&, std::string&, std::string&, std::string&);
void processFile(const std::string&, const std::string&);
void CreateArray(std::ifstream&, std::string*&, int32_t);
std::string* CreateFoolsArray(std::string*&, int32_t, int32_t);
int32_t CountFools(std::string*&, int32_t);
int32_t CountGroupStudents(std::string*&, int32_t, int32_t);
void ExtractNamesAndGroups(const std::string*, int32_t, std::string*&, int32_t*&);
bool compareIndices(int32_t, int32_t, const int32_t*, const std::string*);
void myQuickSort(int32_t*, int32_t, int32_t, const int32_t*, const std::string*);
void SortIndices(int32_t, int32_t*&, const int32_t*, const std::string*);
void CreateSortedFoolsBin(const std::string*, const int32_t*, int32_t);
std::string* CreateGroupArray(std::string*&, int32_t, int32_t, int32_t);
bool CompareBySurname(const std::string&, const std::string&);
void SortGroup(std::string*&, int32_t);
void CreateSortedGroupList(std::string*&, int32_t);
bool CompareByAverageDescending(const std::string&, const std::string&);
void CreateSortedGroupAverageList(std::string*&, int32_t);
std::string* CreateGeniusArray(std::string*&, int32_t, int32_t);
int32_t CountGenius(std::string*&, int32_t);
void CreateListWithGenius(std::string*&, int32_t);
void CreateSortedList(const std::string*, const int32_t*, int32_t, const std::string&);
int32_t CountRecordsInBinaryFile(std::ifstream& fin);
void SortList(const char*, const char*);
#endif


