#include <iostream>
#include "HashTable.h"

int main() {
    setlocale(LC_ALL, "russian");

    HashTable ht(5);
    ht.print();
    std::cout << "\n";

    ht.add(10, "Ten");
    ht.add(20, "Twenty");
    ht.add(6, "Six");
    ht.add(11, "Eleven");
    ht.print();
    std::cout << "\n";

    std::cout << "Удаление 20: \n";
    ht.remove(20);
    ht.print();
    std::cout << "\n";

    return 0;
}