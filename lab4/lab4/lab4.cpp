#include <iostream>
#include "BalancedTreeSearch.h"
#include "../../lab2/lab2/BinaryTree.h"

int main()
{
    setlocale(LC_ALL, "russian");

    BalancedTreeSearch tree;

    std::cout << "Добавляем 10, 20, 30 в дерево:\n";
    tree.add(10);
    tree.add(20);
    tree.add(30);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Добавляем 4, 7 в дерево:\n";
    tree.add(7);
    tree.add(4);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Удаляем 30:\n";
    tree.remove(30);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Удаляем 4:\n";
    tree.remove(4);
    tree.printHorizontal();
    std::cout << "\n";

    return 0;
}