#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree tree;

    setlocale(LC_ALL, "russian");

    tree.addNode(10);
    tree.addNode(5);
    tree.addNode(15);
    tree.addNode(3);
    tree.addNode(7);

    std::cout << "Дерево по уровням:\n";
    tree.printLevels();

    int key = 7;
    int level = tree.getLevelByKey(key);
    std::cout << "Уровень узла с ключом " << key << ": " << level << "\n";

    return 0;
}