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
        std::cout << size;
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
        std::string* foolsarray1 = new std::string[size];
        std::ifstream binin("average_grades.bin", std::ios::binary | std::ios::ate);

        CreateArray(binin, foolsarray1, size);
        int32_t foolsize{ CountFools(foolsarray1,size) };

        std::string* foolsarray = CreateFoolsArray(foolsarray1, size, foolsize);
        delete[] foolsarray1;
        CreateListWithFools(foolsarray, foolsize);
        delete[] foolsarray;

        std::ifstream fin("ListWithFools.bin", std::ios::binary);
        CheckInputFile(fin);

        std::string* arrayOfFools = new std::string[foolsize];
        CreateArray(fin, arrayOfFools, foolsize);

        std::string* names = nullptr;
        int32_t* groups = nullptr;
        ExtractNamesAndGroups(arrayOfFools, foolsize, names, groups);

        int32_t* indices = nullptr;
        SortIndices(foolsize, indices, groups, names);

        CreateSortedFoolsBin(arrayOfFools, indices, foolsize);


        delete[] arrayOfFools;
        delete[] names;
        delete[] groups;
        delete[] indices;
        fin.close();

        std::string* Students = new std::string[size];
        std::ifstream binn("fullgrades.bin", std::ios::binary);
        CreateArray(binn, Students, size);
        int32_t group_number_to_sort{};
        std::cout << "Input group number to sort by surnames\n";
        std::cin >> group_number_to_sort;
        int32_t groupSize{ CountGroupStudents(Students,size,group_number_to_sort) };
        std::string* groupArray = CreateGroupArray(Students, size, group_number_to_sort, groupSize);
        delete[] Students;
        SortGroupBySurnames(groupArray, groupSize);
        CreateSortedGroupList(groupArray, groupSize);
        delete[] groupArray;

        std::string* AvgStudents = new std::string[size];
        std::ifstream avgbin("average_grades.bin", std::ios::binary);
        CheckInputFile(avgbin);
        CreateArray(avgbin, AvgStudents, size);
        avgbin.close();

        int32_t group_number_avg{};
        std::cout << "Input group number to sort by descending average score\n";
        std::cin >> group_number_avg;

        int32_t groupSizeAvg{ CountGroupStudents(AvgStudents, size, group_number_avg) };
        std::string* groupAvgArray = CreateGroupArray(AvgStudents, size, group_number_avg, groupSizeAvg);
        delete[] AvgStudents;

        SortGroupByAverageDescending(groupAvgArray, groupSizeAvg);
        CreateSortedGroupAverageList(groupAvgArray, groupSizeAvg);
        delete[] groupAvgArray;

        std::string* geniusarray1 = new std::string[size];
        std::ifstream bining("average_grades.bin", std::ios::binary | std::ios::ate);
        CreateArray(bining, geniusarray1, size);
        int32_t geniussize{ CountGenius(geniusarray1, size) };

        std::string* geniusarray = CreateGeniusArray(geniusarray1, size, geniussize);
        delete[] geniusarray1;
        CreateListWithGenius(geniusarray, geniussize);
        delete[] geniusarray;
        bining.close();



        SortFools();
        SortGenius();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }





    return 0;
}
