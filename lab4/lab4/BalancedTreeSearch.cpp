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

void BalancedTreeSearch::newHeight(BalancedTreeSearch::Node* node) {
    if (node) {
        int leftHeight = height(node->leftChild());
        int rightHeight = height(node->rightChild());
        node->setHeight(std::max(leftHeight, rightHeight) + 1);
    }
}

BalancedTreeSearch::Node* BalancedTreeSearch::balancing(Node* node, bool& isFixed, bool isOperationAdd) {
    if (!node) {
        return nullptr;
    }

    int balance = heightDifference(node);

    if (balance == 0) {
        isFixed = true;
    }
    else if (balance == -2) {
        if (heightDifference(node->leftChild()) > 0) {
            Node* rotatedSubtree = rotateLeft(node->leftChild());
            node->setLeftChild(rotatedSubtree);
        }
        node = rotateRight(node);
        if (isOperationAdd) {
            isFixed = true;
        }
    }
    else if (balance == 2) {
        if (heightDifference(node->rightChild()) < 0) {
            Node* rotatedSubtree = rotateRight(node->rightChild());
            node->setRightChild(rotatedSubtree);
        }
        node = rotateLeft(node);
        if (isOperationAdd) {
            isFixed = true;
        }
    }
    return node;
}

BalancedTreeSearch::Node* BalancedTreeSearch::rotateRight(Node* middle) {
    Node* bottom = middle->leftChild();
    middle->setLeftChild(bottom->rightChild());
    bottom->setRightChild(middle);

    newHeight(middle);
    newHeight(bottom);

    return bottom;
}

BalancedTreeSearch::Node* BalancedTreeSearch::rotateLeft(Node* middle) {
    Node* bottom = middle->rightChild();
    middle->setRightChild(bottom->leftChild());
    bottom->setLeftChild(middle);

    newHeight(middle);
    newHeight(bottom);

    return bottom;
}

BalancedTreeSearch::Node* BalancedTreeSearch::addNode(Node* root, int key, bool& isFixed) {
    if (!root) {
        isFixed = false;
        root = new Node(key);
        return root;
    }

    if (key == root->key()) {
        isFixed = true;
        return root;
    }

    isFixed = false;
    if (root->key() > key) {
        root->setLeftChild(addNode(root->leftChild(), key, isFixed));
        if (!isFixed) {
            root->setBalance(root->balance() - 1);
            root = balancing(root, isFixed, false);
        }
    }
    else {
        root->setRightChild(addNode(root->rightChild(), key, isFixed));
        if (!isFixed) {
            root->setBalance(root->balance() + 1);
            root = balancing(root, isFixed, false);
        }
    }
    return root;
}

BalancedTreeSearch::Node* BalancedTreeSearch::remove(Node* node, int key, bool& isDeleted, bool& isFixed) {
    if (!node) {
        isDeleted = false;
        isFixed = true;
        return nullptr;
    }

    if (key < node->key()) {
        node->setLeftChild(remove(node->leftChild(), key, isDeleted, isFixed));
    }
    else if (key > node->key()) {
        node->setRightChild(remove(node->rightChild(), key, isDeleted, isFixed));
    }
    else {
        isDeleted = true;
        Node* left = node->leftChild();
        Node* right = node->rightChild();

        if (!right || !left) {
            delete node;
            isFixed = false;
            if (left) {
                return left;
            }
            else {
                return right;
            }
        }

        Node* min = BinaryTreeSearch::searchMin(right);
        node->setKey(min->key());

        bool flagIsDeleted;
        node->setRightChild(remove(node->rightChild(), min->key(), flagIsDeleted, isFixed));
    }

    newHeight(node);
    node = balancing(node, isFixed, false);

    return node;
}

void BalancedTreeSearch::add(int key) {
    bool isFixed = false;
    m_root = addNode(m_root, key, isFixed);
}

void BalancedTreeSearch::remove(int key) {
    bool isDeleted = false;
    bool isFixed = false;
    m_root = remove(m_root, key, isDeleted, isFixed);
}