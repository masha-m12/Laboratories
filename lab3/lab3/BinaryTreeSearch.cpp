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