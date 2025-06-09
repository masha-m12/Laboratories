#include <iostream>
#include "BinaryTreeSearch.h"
#include "../../lab2/lab2/BinaryTree.h"

int main()
{
    BinaryTreeSearch tree;

    setlocale(LC_ALL, "russian");

    tree.addNode(10);
    tree.addNode(5);
    tree.addNode(15);
    tree.addNode(3);
    tree.addNode(7);
    tree.addNode(12);
    tree.addNode(20);

    std::cout << "Дерево:\n";
    tree.printHorizontal();

    std::cout << "Ключи по возрастанию: ";
    std::vector<int> keys = tree.allTreeKeys();
    for (int k : keys) {
        std::cout << k << " ";
    }
    std::cout << "\n";

    int min = tree.min();
    std::cout << "Минимальный ключ: " << min << "\n";

    int max = tree.max();
    std::cout << "Максимальный ключ: " << max << "\n";

    std::cout << "Дерево после удаления 10:\n";
    tree.deleteNodeByKey(10);
    tree.printHorizontal();

    return 0;
}