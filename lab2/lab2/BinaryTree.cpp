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