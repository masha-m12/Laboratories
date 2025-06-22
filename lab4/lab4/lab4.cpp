#include <iostream>
#include "BalancedTreeSearch.h"
#include "../../lab2/lab2/BinaryTree.h"

void foo(int size) {
    BalancedTreeSearch tree;
    std::vector<int> keys;
    for (int i = 0; i < size; ++i)
    {
        keys.push_back(i);
    }

    std::vector<int> tmp = keys;
    for (int i = 0; i < size; ++i)
    {
        int index = rand() % tmp.size();
        tree.addNode(tmp[index]);
        tmp.erase(tmp.begin() + index);
    }

    tree.printHorizontal();

    tmp = keys;
    for (int i = 0; i < size; ++i)
    {
        int index = rand() % tmp.size();
        tree.deleteNodeByKey(tmp[index]);
        tmp.erase(tmp.begin() + index);
    }

    tree.printHorizontal();
}

int main()
{
    setlocale(LC_ALL, "russian");

    foo(73);
    return 0;

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

    std::cout << "Удаляем 30:\n";
    tree.deleteNodeByKey(30);
    tree.printHorizontal();
    std::cout << "\n";

    std::cout << "Удаляем 4:\n";
    tree.deleteNodeByKey(4);
    tree.printHorizontal();
    std::cout << "\n";

    return 0;
}