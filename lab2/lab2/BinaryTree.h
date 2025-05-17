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
    void printHorizontal(Node* node, int space) const;
    void printLevels(Node* node) const;

    Node* addNode(Node* node, int key);
    Node* search(Node* node, int key);
    Node* remove(Node* node, int key);
};