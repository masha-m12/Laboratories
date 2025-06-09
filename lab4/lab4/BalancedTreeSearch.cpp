#include <iostream>
#include "BalancedTreeSearch.h"

BalancedTreeSearch::BalancedTreeSearch(const BalancedTreeSearch& other) {
    m_root = copyTree(other.m_root);
}

BalancedTreeSearch::BalancedTreeSearch(BalancedTreeSearch&& other) noexcept {
    m_root = other.m_root;
    other.m_root = nullptr;
}

int BalancedTreeSearch::heightDifference(const Node* node) const {
    if (!node) {
        return 0;
    }

    int leftHeight = height(node->leftChild());
    int rightHeight = height(node->rightChild());

    return rightHeight - leftHeight;
}

BalancedTreeSearch::Node* BalancedTreeSearch::balancing(Node* node, bool& isFixed) {
    if (!node) {
        return nullptr;
    }

    int leftHeight = height(node->leftChild());
    int rightHeight = height(node->rightChild());

    node->setHeight(std::max(leftHeight, rightHeight) + 1);
    int balance = heightDifference(node);

    if (balance == 0) {
        isFixed = true;
    }
    else if (balance == -2) {
        if (heightDifference(node->leftChild()) <= 0) {
            node = rotateRight(node);
        }
        else {
            Node* rotatedSubtree = rotateLeft(node->leftChild());
            node->setLeftChild(rotatedSubtree);
            node = rotateRight(node);
        }
        isFixed = true;
    }
    else if (balance == 2) {
        if (heightDifference(node->rightChild()) >= 0) {
            node = rotateLeft(node);
        }
        else {
            Node* rotatedSubtree = rotateRight(node->rightChild());
            node->setRightChild(rotatedSubtree);
            node = rotateLeft(node);
        }
        isFixed = true;
    }

    return node;
}

BalancedTreeSearch::Node* BalancedTreeSearch::rotateRight(Node* middle) {
    Node* bottom = middle->leftChild();
    middle->setLeftChild(bottom->rightChild());
    bottom->setRightChild(middle);

    int middleLeftHeight = height(middle->leftChild());
    int middleRightHeight = height(middle->rightChild());
    middle->setHeight(std::max(middleLeftHeight, middleRightHeight) + 1);

    int bottomLeftHeight = height(bottom->leftChild());
    int bottomRightHeight = height(bottom->rightChild());
    bottom->setHeight(std::max(bottomLeftHeight, bottomRightHeight) + 1);

    return bottom;
}

BalancedTreeSearch::Node* BalancedTreeSearch::rotateLeft(Node* middle) {
    Node* bottom = middle->rightChild();
    middle->setRightChild(bottom->leftChild());
    bottom->setLeftChild(middle);

    int middleLeftHeight = height(middle->leftChild());
    int middleRightHeight = height(middle->rightChild());
    middle->setHeight(std::max(middleLeftHeight, middleRightHeight) + 1);

    int bottomLeftHeight = height(bottom->leftChild());
    int bottomRightHeight = height(bottom->rightChild());
    bottom->setHeight(std::max(bottomLeftHeight, bottomRightHeight) + 1);

    return bottom;
}

//к добавлению
if (!root) {
    root = new Node(key);
}
else if (root->key() < key) {
    root->setLeftChild(addNode(root->leftChild(), key));
    //Вернулись из левого поддерева, балансируем
}
else {
    root->setRightChild(addNode(root->rightChild(), key));
    //Вернулись из правого поддерева, балансируем
}
