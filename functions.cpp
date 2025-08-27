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
void processFile(const std::string& fullgrades.bin, const std::string& average_grades.bin) {
    std::ifstream fin(fullgrades.bin);
    if (!fin) {
        throw std::runtime_error("input file error\n");
    }

    std::fstream fout(average_grades.bin, std::ios::out | std::ios::binary);
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


