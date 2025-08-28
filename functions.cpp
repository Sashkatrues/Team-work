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
        bin.write(array[i].c_str(), array[i].length());
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


double calculateAverage(const std::string& line, std::string& name, std::string& group, std::string& id) {
    if (line.empty()) {
        throw std::runtime_error("string is empty");
    }

    size_t pos{};
    size_t prev{};

    pos = line.find(';', prev);
    if (pos == std::string::npos) {
        throw std::runtime_error("mistake with form: don't have name");
    }
    name = line.substr(prev, pos - prev);
    prev = pos + 1;

    pos = line.find(';', prev);
    if (pos == std::string::npos) {
        throw std::runtime_error("mistake with form: don't have group");
    }
    group = line.substr(prev, pos - prev);
    prev = pos + 1;

    pos = line.find(';', prev);
    if (pos == std::string::npos) {
        throw std::runtime_error("mistake with form: don't have ID");
    }
    id = line.substr(prev, pos - prev);
    prev = pos + 1;

    double sum{};
    int32_t count{};
    while (prev < line.size()) {

        pos = line.find(';', prev);
        if (pos == std::string::npos) break;
        // std::string subject = line.substr(prev, pos - prev);  // Пропускаем, если не нужен
        prev = pos + 1;

        // Оценка: до следующего ';' или конца
        pos = line.find(';', prev);
        std::string grade_str;
        if (pos == std::string::npos) {
            grade_str = line.substr(prev);
            prev = line.size();
        }
        else {
            grade_str = line.substr(prev, pos - prev);
            prev = pos + 1;
        }

        int grade = std::stoi(grade_str);
        sum += grade;
        ++count;

    }

    if (count == 0) {
        throw std::runtime_error(name + "don't have marks");
    }

    return sum / count;
}

// Функция для обработки файлов
void processFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile);
    if (!fin) {
        throw std::runtime_error("input file error\n");
    }

    std::fstream fout(outputFile, std::ios::out | std::ios::binary);
    if (!fout) {
        throw std::runtime_error("output file error\n");
    }

    std::string line;
    while (std::getline(fin, line)) {
        try {
            std::string name, group, id;
            double average = calculateAverage(line, name, group, id);

            std::stringstream ss;
            ss << name << ";" << group << ";" << id << ";" << std::fixed << std::setprecision(2) << average << "\n";
            std::string output = ss.str();

            fout.write(output.c_str(), output.size());
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what();
        }
    }

    fin.close();
    fout.close();
}
void CreateArray(std::ifstream& binin, std::string*& arr, int32_t size) {


    binin.seekg(0, std::ios::end);
    int32_t length{ static_cast<int32_t>(binin.tellg()) };
    binin.seekg(0);
    char* buffer = new char[length];
    binin.read(buffer, length);
    std::string content(buffer, length);
    delete[] buffer;
    size_t pos{};
    int32_t index{};
    while (index < size) {
        size_t next{ content.find('\n', pos) };
        if (next == std::string::npos) break;

        arr[index] = content.substr(pos, next - pos);
        ++index;
        pos = next + 1;
    }
}

int32_t CountFools(std::string*& foolsarray1, int32_t size) {
    int32_t counter{};
    size_t pos{};
    for (int32_t i{}; i < size; ++i) {
        pos = foolsarray1[i].find_last_of(';');
        if (std::stod(foolsarray1[i].substr(pos + 1, foolsarray1[i].size() - pos - 1)) < 4) {
            ++counter;
        }
    }
    return counter;
}

std::string* CreateFoolsArray(std::string*& foolsarray1, int32_t size, int32_t foolsize) {

    std::string* foolsarray = new std::string[foolsize];

    size_t pos{};
    int32_t j{  };
    for (int32_t i{}; i < size; ++i) {
        pos = foolsarray1[i].find_last_of(';');
        if (std::stod(foolsarray1[i].substr(pos + 1,foolsarray[i].size()-pos-1)) < 4) {
            foolsarray[j] = foolsarray1[i];
            ++j;
        }
    }

    return foolsarray;
}
void CreateListWithFools(std::string*& foolsarray, int32_t size) {
    std::ofstream binout("ListWithFools.bin", std::ios::binary);
    for (int32_t i{}; i < size; ++i) {
        binout.write(foolsarray[i].c_str(), foolsarray[i].size());
        binout.write("\n", 1);
    }
    binout.close();
}

void ExtractNamesAndGroups(const std::string* foolsarray, int32_t size, std::string*& names, int32_t*& groups) {
    names = new std::string[size];
    groups = new int32_t[size];
    for (int32_t i{}; i < size; ++i) {
        size_t pos = foolsarray[i].find(';');
        if (pos == std::string::npos) continue;
        names[i] = foolsarray[i].substr(0, pos);

        size_t groupStart = pos + 1;
        size_t groupEnd = foolsarray[i].find(';', groupStart);
        std::string groupStr = foolsarray[i].substr(groupStart, groupEnd - groupStart);
        groups[i] = std::stoi(groupStr);
    }
}

bool compareIndices(int32_t a, int32_t b, const int32_t* groups, const std::string* names) {
    if (groups[a] != groups[b]) {
        return groups[a] < groups[b];
    }
    return names[a] < names[b];
}

void myQuickSort(int32_t* indices, int32_t low, int32_t high, const int32_t* groups, const std::string* names) {
    if (low >= high) {
        return;
    }

    int32_t pivotIndex = low + (high - low) / 2;
    int32_t pivot = indices[pivotIndex];

    int32_t i = low;
    int32_t j = high;
    while (i <= j)
    {
        while (compareIndices(indices[i], pivot, groups, names)) {
            ++i;
        }

        while (compareIndices(pivot, indices[j], groups, names)) {
            --j;
        }

        if (i <= j) {
            std::swap(indices[i], indices[j]);
            ++i;
            --j;
        }
    }

    if (low < j) myQuickSort(indices, low, j, groups, names);
    if (i < high) myQuickSort(indices, i, high, groups, names);
}


void SortIndices(int32_t size, int32_t*& indices, const int32_t* groups, const std::string* names) {
    indices = new int32_t[size];
    for (int32_t i{}; i < size; ++i) {
        indices[i] = i;
    }
    myQuickSort(indices, 0, size - 1, groups, names);
}

void CreateSortedFoolsBin(const std::string* arr, const int32_t* indices, int32_t size) {
    std::ofstream binout("SortedFools.bin", std::ios::binary);
    for (int32_t i{}; i < size; ++i) {
        int32_t idx = indices[i];
        binout.write(arr[idx].c_str(), arr[idx].size());
        binout.write("\n", 1);
    }
    binout.close();
}


int32_t CountGroupStudents(std::string*& students, int32_t size, int32_t group_num) {
    int32_t counter{};
    size_t pos{};
    for (int32_t i{}; i < size; ++i) {
        pos = students[i].find_first_of(';');
        if (std::stoi(students[i].substr(pos + 1,1)) == group_num ) {
            ++counter;
        }
    }
    return counter;
}

std::string* CreateGroupArray(std::string*& Students, int32_t size, int32_t group_number, int32_t groupSize) {
    std::string* groupString = new std::string[groupSize];
    size_t pos{};
    int32_t j{};
    for (int32_t i{}; i < size; ++i) {
        pos = Students[i].find_first_of(';');
        if (std::stoi(Students[i].substr(pos + 1, 1)) == group_number) {
            groupString[j] = Students[i];
            ++j;
        }
    }
    return groupString;
}

void SortGroupBySurnames(std::string*& groupStrings, int32_t groupSize) {
    std::sort(groupStrings, groupStrings + groupSize, СompareBySurname);
}

bool СompareBySurname(const std::string& a, const std::string& b) {
    size_t posA = a.find(';');
    size_t posB = b.find(';');
    std::string surnameA = a.substr(0, posA);
    std::string surnameB = b.substr(0, posB);
    return surnameA < surnameB;
}

void CreateSortedGroupList(std::string*& groupStrings, int32_t groupSize) {
    std::ofstream binout("SortedGroupList.bin", std::ios::binary);
    for (int32_t i{}; i < groupSize; ++i) {
        binout.write(groupStrings[i].c_str(), groupStrings[i].size());
        binout.write("\n", 1);
    }
    binout.close();
}

bool CompareByAverageDescending(const std::string& a, const std::string& b) {
    size_t posA = a.rfind(';');
    double avgA = std::stod(a.substr(posA + 1));

    size_t posB = b.rfind(';');
    double avgB = std::stod(b.substr(posB + 1));

    if (avgA != avgB) {
        return avgA > avgB;
    }

    size_t nameEndA = a.find(';');
    std::string nameA = a.substr(0, nameEndA);

    size_t nameEndB = b.find(';');
    std::string nameB = b.substr(0, nameEndB);

    return nameA < nameB;
}

void SortGroupByAverageDescending(std::string*& groupArray, int32_t groupSize) {
    std::sort(groupArray, groupArray + groupSize, CompareByAverageDescending);
}

void CreateSortedGroupAverageList(std::string*& groupArray, int32_t groupSize) {
    std::ofstream binout("SortedGroupAverage.bin", std::ios::binary);
    for (int32_t i{}; i < groupSize; ++i) {
        binout.write(groupArray[i].c_str(), groupArray[i].size());
        binout.write("\n", 1);
    }
    binout.close();
}

int32_t CountGenius(std::string*& geniusarray1, int32_t size) {
    int32_t counter{};
    size_t pos{};
    for (int32_t i{}; i < size; ++i) {
        pos = geniusarray1[i].find_last_of(';');
        if (std::stod(geniusarray1[i].substr(pos + 1, geniusarray1[i].size() - pos - 1)) >= 8) {
            ++counter;
        }
    }
    return counter;
}

std::string* CreateGeniusArray(std::string*& geniusarray1, int32_t size, int32_t geniussize)
{

    std::string* geniusarray = new std::string[geniussize];

    size_t pos{};
    int32_t j{  };
    for (int32_t i{}; i < size; ++i)
    {
        pos = geniusarray1[i].find_last_of(';');
        if (std::stod(geniusarray1[i].substr(pos + 1, geniusarray1[i].size() - pos - 1)) >= 8)
        {
            geniusarray[j] = geniusarray1[i];
            ++j;
        }
        if (j == geniussize)
        {
            break;
        }
    }

    return geniusarray;
}
void CreateListWithGenius(std::string*& geniusarray, int32_t size)
{
    std::ofstream binout("ListWithGenius.bin", std::ios::binary);
    for (int32_t i{}; i < size; ++i)
    {
        binout.write(geniusarray[i].c_str(), geniusarray[i].size());
        binout.write("\n", 1);
    }
    binout.close();
}


void CreateSortedList(const std::string* arr, const int32_t* indices, int32_t size, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) {
        throw "output file error\n";
    }
    for (int32_t i{}; i < size; ++i) {
        int32_t idx = indices[i];
        fout << arr[idx] << '\n';
    }
    fout.close();
}


int32_t CountRecordsInBinaryFile(std::ifstream& fin) {
    fin.clear();
    fin.seekg(0, std::ios::beg);
    int32_t count = 0;
    char c;
    while (fin.get(c)) {
        if (c == '\n') {
            count++;
        }
    }
    fin.clear();
    fin.seekg(0, std::ios::beg);
    return count;
}

void SortFools() {

    std::ifstream fools_bin("ListWithFools.bin", std::ios::binary);
    CheckInputFile(fools_bin);


    int32_t foolsize = CountRecordsInBinaryFile(fools_bin);

    std::string* foolsArray = new std::string[foolsize];
    CreateArray(fools_bin, foolsArray, foolsize);
    fools_bin.close();


    std::string* fool_names = nullptr;
    int32_t* fool_groups = nullptr;
    ExtractNamesAndGroups(foolsArray, foolsize, fool_names, fool_groups);


    int32_t* fool_indices = nullptr;
    SortIndices(foolsize, fool_indices, fool_groups, fool_names);

    CreateSortedList(foolsArray, fool_indices, foolsize, "SortedFoolsByGroupAndName.txt");

    delete[] foolsArray;
    delete[] fool_names;
    delete[] fool_groups;
    delete[] fool_indices;
}

void SortGenius() {
    std::ifstream genius_bin("ListWithGenius.bin", std::ios::binary);
    CheckInputFile(genius_bin);


    int32_t geniussize = CountRecordsInBinaryFile(genius_bin);

    std::string* geniusArray = new std::string[geniussize];
    CreateArray(genius_bin, geniusArray, geniussize);
    genius_bin.close();

    std::string* genius_names = nullptr;
    int32_t* genius_groups = nullptr;
    ExtractNamesAndGroups(geniusArray, geniussize, genius_names, genius_groups);


    int32_t* genius_indices = nullptr;
    SortIndices(geniussize, genius_indices, genius_groups, genius_names);


    CreateSortedList(geniusArray, genius_indices, geniussize, "SortedGeniusByGroupAndName.txt");

    delete[] geniusArray;
    delete[] genius_names;
    delete[] genius_groups;
    delete[] genius_indices;
}
