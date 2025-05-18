#include <iostream>
#include "BinaryTree.h"

BinaryTree::Node::Node()
{}

BinaryTree::Node::Node(int key, Node* leftChild, Node* rightChild)
    : m_key(key), m_leftChild(leftChild), m_rightChild(rightChild)
{}

int BinaryTree::Node::key() const {
    return m_key;
}

void BinaryTree::Node::setKey(const int key) {
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::leftChild() const {
    return m_leftChild;
}

void BinaryTree::Node::setLeftChild(Node* leftChild) {
    m_leftChild = leftChild;
}

BinaryTree::Node* BinaryTree::Node::rightChild() const {
    return m_rightChild;
}

void BinaryTree::Node::setRightChild(Node* rightChild) {
    m_rightChild = rightChild;
}

BinaryTree::BinaryTree(const BinaryTree& other) {
    m_root = copyTree(other.m_root);
}

BinaryTree::~BinaryTree() {
    clear(m_root);
}

BinaryTree::Node* BinaryTree::root() const {
    return m_root;
}

void BinaryTree::clear() {
    clear(m_root);
    m_root = nullptr;
}

bool BinaryTree::isEmpty() const {
    return m_root == nullptr;
}

int BinaryTree::countNodes() const {
    return countNodes(m_root);
}

BinaryTree::Node* BinaryTree::addNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (rand() % 2) {
        root->setLeftChild(addNode(root->leftChild(), key));
    }
    else {
        root->setRightChild(addNode(root->rightChild(), key));
    }
    return root;
}

bool BinaryTree::searchNodeByKey(int key) const {
    return nlrSearch(m_root, key);
}

BinaryTree::Node* BinaryTree::copyTree(Node* root) {
    if (!root) {
        return nullptr;
    }

}

void BinaryTree::clear(Node* node) {
    if (!node) {
        return;
    }
    clear(node->leftChild());
    clear(node->rightChild());
    delete node;
    node = nullptr;
}

int BinaryTree::countNodes(Node* node) const {
    if (!node) {
        return 0;
    }
    return 1 + countNodes(node->leftChild()) + countNodes(node->rightChild());
}

void BinaryTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }
    printHorizontal(root->rightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
    printHorizontal(root->leftChild(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::printLevels(Node* root, int leftBorderPos, int rightBorderPos, int yPos) const //реализация с презентации - доработать!
{
    if (root == nullptr) {
        return;
    }
    int xPos = (leftBorderPos + rightBorderPos) / 2;
    //ToDo: перенос курсор в точку (xPos, yPos)
    //ToDo: вывод root->key() 
    printLevels(root->leftChild(), leftBorderPos, xPos, yPos + 15);
    printLevels(root->rightChild(), xPos, rightBorderPos, yPos + 15);
}

BinaryTree::Node* BinaryTree::nlrSearch(Node* root, int key) const
{
    if (!root || root->key() == key) {
        return root;
    }
    Node* subTreeSearchResult = nlrSearch(root->leftChild(), key);
    if (!subTreeSearchResult) {
        subTreeSearchResult = nlrSearch(root->rightChild(), key);
    }
    return subTreeSearchResult;
}