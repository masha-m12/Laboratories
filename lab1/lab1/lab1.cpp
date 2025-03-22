#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    //реализовано слияние из А, В в С - чтобы понять
    //нужно реализовать разбиение из А, В в С, D по отрезкам
    int valueA, valueB;
    bool readA = (fA >> valueA).good();
    bool readB = (fB >> valueB).good();

    while (readA && readB) {
        if (valueA < valueB) {
            fC << valueA << " ";
            readA = (fA >> valueA).good();
        }
        else {
            fC << valueB << " ";
            readB = (fB >> valueB).good();
        }
    }

    while (readA) {
        fC << valueA << " ";
        readA=(fA >> valueA).good();
    }

    while (readB) {
        fC << valueB << " ";
        readA = (fB >> valueB).good();
    }

    fA.close();
    fB.close();
    fC.close();
    fD.close();
}

//написать общую функцию сортировки файла

//нужно для того, чтоб видеть содержимое файлов в консоли
void printFile(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла: " << fileName << "\n";
        return;
    }

    std::cout << "Содержимое файла " << fileName << ": ";

    int number;
    while (file >> number) {
        std::cout << number << " ";
    }

    std::cout << "\n";
    file.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    createFileWithRandomNumbers("file.txt", 10, 100);
    printFile("file.txt");

    std::string fileA = "fileA.txt";
    std::string fileB = "fileB.txt";
    std::string fileC = "fileC.txt";
    std::string fileD = "fileD.txt";

    //закинуть в (общую) функцию сортировки и вызывать только ее
    splitFiles("file.txt", fileA, fileB);
    printFile(fileA);
    printFile(fileB);

    mergeFiles(fileA, fileB, fileC, fileD);
    printFile(fileC);

    return 0;
}