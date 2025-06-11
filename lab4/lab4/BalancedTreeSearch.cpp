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

BalancedTreeSearch::Node* BalancedTreeSearch::balancing(Node* node, bool& isFixed) {
    if (!node) {
        return nullptr;
    }

    newHeight(node);
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
        isFixed = true;
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
            newHeight(root);
            int balance = heightDifference(root);
            if (balance < -1 || balance > 1) {
                root = balancing(root, isFixed);
            }
        }
    }
    else {
        root->setRightChild(addNode(root->rightChild(), key, isFixed));
        if (!isFixed) {
            newHeight(root);
            int balance = heightDifference(root);
            if (balance < -1 || balance > 1) {
                root = balancing(root, isFixed);
            }
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
        if (!isFixed && isDeleted) {
            newHeight(node);
            int balance = heightDifference(node);
            if (balance < -1 || balance > 1) {
                node = balancing(node, isFixed);
            }
        }
    }
    else if (key > node->key()) {
        node->setRightChild(remove(node->rightChild(), key, isDeleted, isFixed));
        if (!isFixed && isDeleted) {
            newHeight(node);
            int balance = heightDifference(node);
            if (balance < -1 || balance > 1) {
                node = balancing(node, isFixed);
            }
        }
    }
    else {
        isDeleted = true;
        isFixed = false;
        Node* left = node->leftChild();
        Node* right = node->rightChild();
        delete node;

        if (!right) {
            if (!left) {
                isFixed = true;
            }
            node = left;
            if (node) {
                newHeight(node);
                node = balancing(node, isFixed);
            }
            return node;
        }

        Node* min = BinaryTreeSearch::searchMin(right);
        Node* minRight = min->rightChild();

        if (min == right) {
            min->setLeftChild(left);
            node = min;
            newHeight(node);
            node = balancing(node, isFixed);
        }
        else {
            Node* minParent = right;

            while (minParent->leftChild() != min) {
                minParent = minParent->leftChild();
            }

            minParent->setLeftChild(minRight);
            min->setLeftChild(left);
            min->setRightChild(right);
            node = min;
            newHeight(right);
            node = balancing(node, isFixed);

            if (!isFixed) {
                bool flagIsDeleted = false;
                bool flagIsFixed = false;
                newHeight(right);

                right = remove(right, min->key(), flagIsDeleted, flagIsFixed);
                node->setRightChild(right);

                newHeight(right);
                newHeight(node);
                node = balancing(node, isFixed);
            }
        }
    }
    return node;
}