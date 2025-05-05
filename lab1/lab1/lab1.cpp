#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <locale>  

struct Sequence {
    int value = INT_MIN;
    std::ifstream* file = nullptr;
    bool ended = true;
    bool isValueValid = false;
    void readNext() {
        int prevValue = value;
        isValueValid = (file->is_open() && (*file >> value));
        if (isValueValid) {
            ended = (value < prevValue);
        }
        else {
            ended = true;
        }
    }
};

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << fileName << "\n";
        return false;
    }

    for (int i = 0; i < numbersCount; ++i) {
        int randomNumber = std::rand() % (maxNumberValue + 1);
        file << randomNumber << " ";
    }

    file.close();
    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла: " << fileName << "\n";
        return false;
    }

    int previous, current;
    file >> previous;
    while (file >> current) {
        if (previous > current) {
            return false;
        }
        previous = current;
    }

    file.close();
    return true;
}

bool splitFiles(const std::string& file, const std::string& fileA, const std::string& fileB) {
    std::ifstream f(file);
    std::ofstream fA(fileA);
    std::ofstream fB(fileB);

    if (!f.is_open() || !fA.is_open() || !fB.is_open()) {
        std::cerr << "Ошибка при открытии файлов." << "\n";
        return false;
    }

    int number1, number2;

    if (!(f >> number1)) {
        std::cerr << "Файл пустой." << "\n";
        return false;
    }

    while (f >> number2) {
        fA << number1 << " ";
        if (number1 > number2) {
            std::swap(fA, fB);
        }
        number1 = number2;
    }

    fA << number1 << " ";

    f.close();
    fA.close();
    fB.close();

    return true;
}

bool mergeFiles(const std::string& fileA, const std::string& fileB, const std::string& fileC, const std::string& fileD) {
    std::ifstream fA(fileA);
    std::ifstream fB(fileB);
    std::ofstream fC(fileC);
    std::ofstream fD(fileD);

    if (!fA.is_open() || !fB.is_open() || !fC.is_open() || !fD.is_open()) {
        std::cerr << "Ошибка при открытии файлов." << "\n";
        return false;
    }

    Sequence seq1, seq2;
    seq1.file = &fA;
    seq2.file = &fB;

    seq1.readNext();
    seq2.readNext();

    bool flag = false;

    while (seq1.isValueValid || seq2.isValueValid) {
        while (!seq1.ended || !seq2.ended) {
            if (!seq1.ended && (seq2.ended || seq1.value <= seq2.value)) {
                fC << seq1.value << " ";
                seq1.readNext();
            }
            else if (!seq2.ended) {
                fC << seq2.value << " ";
                seq2.readNext();
            }
        }

        seq1.ended = !seq1.isValueValid;
        seq2.ended = !seq2.isValueValid;

        flag = flag || (seq1.isValueValid || seq2.isValueValid);

        fC.swap(fD);
    }

    fA.close();
    fB.close();
    fC.close();
    fD.close();

    return flag;
}

std::string sortFile(const std::string& file,
    const std::string fileA = "fileA.txt",
    const std::string fileB = "fileB.txt",
    const std::string fileC = "fileC.txt",
    const std::string fileD = "fileD.txt") {

    splitFiles(file, fileA, fileB);

    std::string input1 = fileA;
    std::string input2 = fileB;
    std::string output1 = fileC;
    std::string output2 = fileD;

    while (mergeFiles(input1, input2, output1, output2)) {
        std::swap(input1, output1);
        std::swap(input2, output2);
    }

    std::remove(file.c_str());
    std::rename(output1.c_str(), file.c_str());

    return file;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");

    createFileWithRandomNumbers("file.txt", 10, 100);

    std::string sortedFile = sortFile("file.txt");
    if (isFileContainsSortedArray(sortedFile) == 1) {
        std::cout << "Файл " << sortedFile << " отсортирован." << "\n";
    }

    return 0;
}