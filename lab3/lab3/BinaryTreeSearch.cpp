#include <iostream>
#include "BinaryTreeSearch.h"

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other)
    : BinaryTree(other)
{}

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) noexcept
    : BinaryTree(std::move(other))
{}

int BinaryTreeSearch::min(Node* node) const {
    if (!node) {
        return INT_MAX;
    }

    Node* current = node;
    while (current->leftChild()) {
        current = current->leftChild();
    }
    return current->key();
}

int BinaryTreeSearch::max(Node* node) const {
    if (!node) {
        return INT_MIN;
    }

    Node* current = node;
    while (current->rightChild()) {
        current = current->rightChild();
    }
    return current->key();
}

BinaryTreeSearch::Node* BinaryTreeSearch::addNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (key < root->key()) {
        root->setLeftChild(addNode(root->leftChild(), key));
    }
    else {
        root->setRightChild(addNode(root->rightChild(), key));
    }

    return root;
}

BinaryTreeSearch::Node* BinaryTreeSearch::remove(Node* node, int key) {
    if (!node) {
        return nullptr;
    }

    Node* replacement = nullptr;

    if (node->key() > key) {
        Node* newLeftChild = remove(node->leftChild(), key);
        node->setLeftChild(newLeftChild);
    }
    else if (node->key() < key) {
        Node* newRightChild = remove(node->rightChild(), key);
        node->setRightChild(newRightChild);
    }
    else {
        if (!node->leftChild() && !node->rightChild()) {
            replacement = nullptr;
        }
        else if (!node->leftChild()) {
            replacement = node->rightChild();
        }
        else {
            replacement = node->leftChild();
        }

        Node* replacement = node->rightChild();
        while (replacement->leftChild()) {
            replacement = replacement->leftChild();
        }

        node->setKey(replacement->key());
        Node* newRightChild = remove(node->rightChild(), replacement->key());
        node->setRightChild(newRightChild);
    }
    return node;
}

BinaryTreeSearch::Node* BinaryTreeSearch::nlrSearch(Node* node, int key) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->key() == key) {
        return node;
    }
    else if (node->key() > key) {
        return nlrSearch(node->leftChild(), key);
    }
    else {
        return nlrSearch(node->rightChild(), key);
    }
}

int BinaryTreeSearch::getLevelByKey(Node* node, int key, int level) const {
    if (!node) {
        return -1;
    }

    if (node->key() == key) {
        return level;
    }
    else if (key < node->key()) {
        return getLevelByKey(node->leftChild(), key, level + 1);
    }
    else {
        return getLevelByKey(node->rightChild(), key, level + 1);
    }
}

void BinaryTreeSearch::lrnTraversal(Node* root, std::vector<int>& keys) const
{
    if (root == nullptr) {
        return;
    }

    lrnTraversal(root->leftChild(), keys);
    keys.push_back(root->key());
    lrnTraversal(root->rightChild(), keys);
}