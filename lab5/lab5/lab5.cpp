#include <iostream>
#include <numeric>

#include "HuffmanTree.h"

int main()
{
    setlocale(LC_ALL, "russian");

    HuffmanTree tree;

    std::string fileName = "file.txt";
    std::string encodedFileName = "encoded.txt";
    std::string decodedFileName = "decoded.txt";

    tree.build(fileName);
    std::cout << "Дерево из списка частот:" << "\n";
    tree.print();

    double coefficient = tree.encode(fileName, encodedFileName);
    std::cout << "Коэффициент сжатия: " << coefficient << "\n";

    bool decoding = tree.decode(encodedFileName, decodedFileName);

    return 0;
}