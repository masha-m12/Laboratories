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

        int height() const;
        void setHeight(int height);

    private:
        int m_key = 0;
        Node* m_leftChild = nullptr;
        Node* m_rightChild = nullptr;
        int m_height = 1;
    };

    BinaryTree() = default;
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept;
    virtual ~BinaryTree();

    Node* root() const;

    void clear();
    void deleteSubtree();
    bool isEmpty() const;

    int height() const;
    int countNodes() const;
    
    int min() const;
    int max() const;

    virtual Node* addNode(Node* root, int key);
    Node* addNode(int key);

    bool searchNodeWithParent(Node* node, Node* parent, int key, Node*& findNode, Node*& parentFindNode);

    bool deleteNodeByKey(int key);
    bool searchNodeByKey(int key) const;

    bool isBalanced();
    int getLevelByKey(int key);

    std::vector<int> allTreeKeys();

    void printHorizontal() const;
    void printLevels() const;

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree other);

protected:
    virtual int min(Node* node) const;
    virtual int max(Node* node) const;

    virtual int getLevelByKey(Node* node, int key, int level) const;
    virtual void lrnTraversal(Node* root, std::vector<int>& keys) const;

    virtual Node* nlrSearch(Node* node, int key) const;
    Node* remove(Node* node, Node* parent);
    virtual Node* findReplacement(Node* node);

    int height(Node* node) const;
    Node* copyTree(Node* root);

    Node* m_root = nullptr;

private:
    void clear(Node* node);
    void deleteSubtree(Node* node);
    int countNodes(Node* node) const;

    bool isBalanced(Node* node);
    void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
    void printLevels(Node* root, int level) const;
};