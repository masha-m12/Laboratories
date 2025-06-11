#include <iostream>
#include "BalancedTreeSearch.h"
#include "../../lab2/lab2/BinaryTree.h"

int main()
{
    setlocale(LC_ALL, "russian");

    BalancedTreeSearch tree;

    std::cout << "Добавляем 10, 20, 30 в дерево:\n";
    tree.addNode(10);
    tree.addNode(20);
    tree.addNode(30);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Добавляем 4, 7 в дерево:\n";
    tree.addNode(7);
    tree.addNode(4);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Удаляем 4:\n";
    tree.deleteNodeByKey(4);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Удаляем 20:\n";
    tree.deleteNodeByKey(20);
    tree.printHorizontal();
    std::cout << "\n";

    return 0;
}