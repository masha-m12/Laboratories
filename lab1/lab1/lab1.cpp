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
    std::ifstream* file;
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
    srand(time(0));

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

void splitFiles(const std::string& file, std::string& fileA, std::string& fileB) {
    std::ifstream f(file);
    std::ofstream fA(fileA);
    std::ofstream fB(fileB);

    if (!f.is_open() || !fA.is_open() || !fB.is_open()) {
        std::cerr << "Ошибка при открытии файлов." << "\n";
        return;
    }

    int number1, number2;
    bool inFile1 = true;

    if (!(f >> number1)) {
        std::cerr << "Файл пустой." << "\n";
        return;
    }

    while (f >> number2) {
        if (inFile1) {
            fA << number1 << " ";
        }
        else {
            fB << number1 << " ";
        }

        if (number1 <= number2) {
            number1 = number2;
        }
        else {
            number1 = number2;
            inFile1 = !inFile1;
        }
    }

    if (inFile1) {
        fA << number1 << " ";
    }
    else {
        fB << number1 << " ";
    }

    f.close();
    fA.close();
    fB.close();
}

void mergeFiles(std::string& fileA, std::string& fileB, std::string& fileC, std::string& fileD) {
    std::ifstream fA(fileA);
    std::ifstream fB(fileB);
    std::ofstream fC(fileC);
    std::ofstream fD(fileD);

    if (!fA.is_open() || !fB.is_open() || !fC.is_open() || !fD.is_open()) {
        std::cerr << "Ошибка при открытии файлов." << "\n";
        return;
    }

    Sequence seq1, seq2;
    seq1.file = &fA;
    seq2.file = &fB;

    seq1.readNext();
    seq2.readNext();

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
        fC.swap(fD);
    }

    fA.close();
    fB.close();
    fC.close();
    fD.close();
}

std::string sortFiles(const std::string& file, std::string& fileA, std::string& fileB, std::string& fileC, std::string& fileD) {
    splitFiles(file, fileA, fileB);
    mergeFiles(fileA, fileB, fileC, fileD);
    return fileA;
}

int main() {
    setlocale(LC_ALL, "Russian");

    createFileWithRandomNumbers("file.txt", 10, 100);

    std::string fileA = "fileA.txt";
    std::string fileB = "fileB.txt";
    std::string fileC = "fileC.txt";
    std::string fileD = "fileD.txt";

    std::string sortFile = sortFiles("file.txt", fileA, fileB, fileC, fileD);
    std::cout << isFileContainsSortedArray(sortFile);
    if (isFileContainsSortedArray(sortFile) == 1) {
        std::cout << "Файл" << sortFile << "отсортирован." << "\n";
    }

    return 0;
}