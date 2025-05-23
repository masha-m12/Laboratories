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
    BinaryTree(BinaryTree&& other) noexcept;
    ~BinaryTree();

    Node* root() const;

    void clear();
    void deleteSubtree();
    bool isEmpty() const;

    int height() const;
    int countNodes() const;

    int min() const;
    int max() const;

    Node* addNode(Node* root, int key);
    Node* addNode(int key);

    bool deleteNodeByKey(int key);
    bool searchNodeByKey(int key) const;

    bool isBalanced();
    int getLevelByKey(int key);

    void lrnTraversal(Node* root, std::vector<int>& keys) const;
    std::vector<int> allTreeKeys();

    void printHorizontal() const;
    void printLevels() const;

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree other);

private:
    Node* m_root = nullptr;

    Node* copyTree(Node* root);

    void clear(Node* node);
    void deleteSubtree(Node* node);
    int height(Node* node) const;
    int countNodes(Node* node) const;
    int min(Node* node) const;
    int max(Node* node) const;
    bool isBalanced(Node* node);
    void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
    void printLevels(Node* root, int level) const;

    Node* nlrSearch(Node* node, int key) const;
    Node* remove(Node* node, int key);
};