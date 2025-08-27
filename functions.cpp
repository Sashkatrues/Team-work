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
void CreateArray(std::ifstream& binin, std::string*& foolsarray, int32_t size) {
   
    
    binin.seekg(0, std::ios::end);
    int32_t length{ static_cast<int32_t>(binin.tellg())};
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

        foolsarray[index] = content.substr(pos, next - pos);
        ++index;
        pos = next + 1;
    }
}

int32_t CountFools(std::string*& foolsarray1, int32_t size) {
    int32_t counter{};
    size_t pos{};
    for (int32_t i{}; i < size; ++i) {
        pos = foolsarray1[i].find_last_of(';');
        if ( foolsarray1[i][pos+1] < 4+48) {
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
        if (foolsarray1[i][pos+1] < 4+48) {
            foolsarray[j] = foolsarray1[i];
            ++j;
        }
    }

    return foolsarray;
}
void CreateListWithFools(std::string*& foolsarray,int32_t size){ 
        std::ofstream binout("ListWithFools.bin", std::ios::binary);
        for (int32_t i{}; i < size; ++i) {
            binout.write(foolsarray[i].c_str(), foolsarray[i].size());
            binout.write("\n", 1);
        }
        binout.close();
}

