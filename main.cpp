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
        CreateBinary(bin_s, students, size);
        std::string* grades = new std::string[size];
        InputGrades(fin_g, grades, size);
        CreateBinary(bin_g, grades, size);
        MergeStudentDataWithGrades(students, grades, size);

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
        std::fstream bin_fools("ListWithFools.bin", std::ios::out | std::ios::binary);
        CreateBinary(bin_fools, foolsarray, foolsize);

        bin_fools.close();

        std::ifstream fin("ListWithFools.bin", std::ios::binary);
        CheckInputFile(fin);

        std::string* names = nullptr;
        int32_t* groups = nullptr;
        ExtractNamesAndGroups(foolsarray, foolsize, names, groups);

        int32_t* indices = nullptr;
        SortIndices(foolsize, indices, groups, names);

        CreateSortedFoolsBin(foolsarray, indices, foolsize);

        delete[] foolsarray;
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
        SortGroup(groupArray, groupSize);
        std::fstream binout("SortedGroupList.bin", std::ios::out | std::ios::binary);
        CreateBinary(binout, groupArray, groupSize);
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

        SortGroup(groupAvgArray, groupSizeAvg);
        std::fstream bin_fout("SortedGroupAverage.bin", std::ios::out | std::ios::binary);
        CreateBinary(bin_fout, groupAvgArray, groupSizeAvg);
        bin_fout.close();

        delete[] groupAvgArray;

        std::string* geniusarray1 = new std::string[size];
        std::ifstream bining("average_grades.bin", std::ios::binary | std::ios::ate);
        CreateArray(bining, geniusarray1, size);
        int32_t geniussize{ CountGenius(geniusarray1, size) };

        std::string* geniusarray = CreateGeniusArray(geniusarray1, size, geniussize);
        delete[] geniusarray1;
        std::fstream bin_out("ListWithGenius.bin", std::ios::out | std::ios::binary);
        CreateBinary(bin_out, geniusarray, geniussize);
        delete[] geniusarray;
        bin_out.close();
        bining.close();

        SortList("ListWithFools.bin", "SortedFoolsByGroupAndName.txt");
        SortList("ListWithGenius.bin", "SortedGeniusByGroupAndName.txt");

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

