#pragma once
#include <iostream>
#include <vector>

class BinaryTree
{
public:
    class Node
    {
    public:
        Node();
        Node(int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr);
        ~Node() = default;

        int key() const;
        void setKey(const int key);

        Node* leftChild() const;
        void setLeftChild(Node* leftChild);

        Node* rightChild() const;
        void setRightChild(Node* rightChild);

    private:
        int m_key = 0;
        Node* m_leftChild = nullptr;
        Node* m_rightChild = nullptr;
    };
    
    BinaryTree() = default;
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();

    Node* root() const;

    void clear();
    void deleteSubtree();
    bool isEmpty() const;

    int countNodes() const;

    Node* addNode(Node* root, int key);

    bool deleteNodeByKey(int key);
    bool searchNodeByKey(int key) const;

    void printHorizontal() const;
    void printLevels() const;

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree other);

private:
    Node* m_root = nullptr;

    Node* copyTree(Node* root);

    void clear(Node* node);
    int countNodes(Node* node) const;
    void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
    void printLevels(Node* root, int leftBorderPos, int rightBorderPos, int yPos) const;

    Node* nlrSearch(Node* node, int key) const;
    Node* remove(Node* node, int key);
};

/*
-конструкторы(по умолчанию и с параметрами);

-конструкторы(по умолчанию, копирования, перемещения);
-деструктор;
-получение корня дерева;
-очистка дерева(удаление всех узлов);
-удаление поддеревьев узла;
-isEmpty(возвращает true, если дерево пусто);
-получение количества узлов дерева;
-добавление узла в дерево(методом случайного выбора поддерева);
-удаление узла из дерева по ключу(возвращает true, если узел был удалён);
-поиск узла дерева по ключу;
-проверка дерева на сбалансированность(возвращает true, если дерево является сбалансированным : высоты правого и левого поддеревьев отличаются не более, чем на единицу, и сами поддеревья также являются сбалансированными);
-получение уровня вершины по ключу(возвращает индекс уровня или - 1, если вершина не найдена);
-вывод в консоль дерева в горизонтальном виде(самый правый потомок находится на первой строке, самый левый - на нижней);
-вывод в консоль дерева по уровням в консоль;
-оператор присваивания;
-оператор перемещения.
*/