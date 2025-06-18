#include <iostream>
#include <vector>
#include <algorithm>
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

int BinaryTree::Node::height() const {
    return m_height;
}

void BinaryTree::Node::setHeight(int height) {
    m_height = height;
}

int BinaryTree::Node::balance() const {
    return m_balance;
}

void BinaryTree::Node::setBalance(int balance) {
    m_balance = balance;
}

BinaryTree::BinaryTree(const BinaryTree& other) {
    m_root = copyTree(other.m_root);
}

BinaryTree::BinaryTree(BinaryTree&& other) noexcept
    : m_root(other.m_root) {
    other.m_root = nullptr;
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

void BinaryTree::deleteSubtree() {
    deleteSubtree(m_root);
}

bool BinaryTree::isEmpty() const {
    return m_root == nullptr;
}

int BinaryTree::height() const {
    return height(m_root);
}

int BinaryTree::countNodes() const {
    return countNodes(m_root);
}

int BinaryTree::min() const {
    return min(m_root);
}

int BinaryTree::max() const {
    return max(m_root);
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

BinaryTree::Node* BinaryTree::addNode(int key)
{
    if (m_root) {
        return addNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

bool BinaryTree::searchNodeWithParent(Node* node, Node* parent, int key, Node*& findNode, Node*& parentFindNode) {
    if (!node) {
        return false;
    }

    if (node->key() == key) {
        findNode = node;
        parentFindNode = parent;
        return true;
    }
    if (searchNodeWithParent(node->leftChild(), node, key, findNode, parentFindNode)) {
        return true;
    }
    if (searchNodeWithParent(node->rightChild(), node, key, findNode, parentFindNode)) {
        return true;
    }

    return false;
}

bool BinaryTree::deleteNodeByKey(int key) {
    Node* parent = nullptr;
    Node* node = nullptr;

    bool search = searchNodeWithParent(m_root, nullptr, key, node, parent);
    if (!search) {
        return false;
    }

    remove(node, parent);

    return true;
}

bool BinaryTree::searchNodeByKey(int key) const {
    return nlrSearch(m_root, key);
}

bool BinaryTree::isBalanced() {
    return isBalanced(m_root);
}

int BinaryTree::getLevelByKey(int key) {
    return getLevelByKey(m_root, key, 1);
}

void BinaryTree::lrnTraversal(Node* root, std::vector<int>& keys) const
{
    if (root == nullptr) {
        return;
    }

    lrnTraversal(root->leftChild(), keys);
    keys.push_back(root->key());
    lrnTraversal(root->rightChild(), keys);
}

std::vector<int> BinaryTree::allTreeKeys() {
    std::vector<int>keys;
    lrnTraversal(m_root, keys);
    std::sort(keys.begin(), keys.end());
    return keys;
}

void BinaryTree::printHorizontal() const {
    printHorizontal(m_root, 0, 5);
}

void BinaryTree::printLevels() const {
    if (!m_root) {
        return;
    }

    int h = height(m_root);
    for (int level = 0; level < h; ++level) {
        printLevels(m_root, level);
        std::cout << std::endl;
    }
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        clear();
        m_root = copyTree(other.m_root);
    }
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree other) {
    std::swap(m_root, other.m_root);
    return *this;
}

BinaryTree::Node* BinaryTree::copyTree(Node* root) {
    if (!root) {
        return nullptr;
    }
    Node* copyNode = new Node(root->key());
    copyNode->setLeftChild(copyTree(root->leftChild()));
    copyNode->setRightChild(copyTree(root->rightChild()));
    return copyNode;
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

void BinaryTree::deleteSubtree(Node* node) {
    if (!node) {
        return;
    }
    deleteSubtree(node->leftChild());
    deleteSubtree(node->rightChild());
    delete node;
    node = nullptr;
}

int BinaryTree::height(Node* node) const {
    if (!node) {
        return 0;
    }
    return 1 + std::max(height(node->leftChild()), height(node->rightChild()));
}

int BinaryTree::countNodes(Node* node) const {
    if (!node) {
        return 0;
    }
    return 1 + countNodes(node->leftChild()) + countNodes(node->rightChild());
}

int BinaryTree::min(Node* node) const {
    if (!node) {
        return INT_MAX;
    }
    int left = min(node->leftChild());
    int right = min(node->rightChild());

    return std::min(node->key(), std::min(left, right));
}

int BinaryTree::max(Node* node) const {
    if (!node) {
        return INT_MIN;
    }
    int left = max(node->leftChild());
    int right = max(node->rightChild());

    return std::max(node->key(), std::max(left, right));
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

bool BinaryTree::isBalanced(Node* node) {
    if (!node) {
        return true;
    }
    int left = height(node->leftChild());
    int right = height(node->rightChild());
    if (abs(left - right) > 1) {
        return false;
    }
    return isBalanced(node->leftChild()) && isBalanced(node->rightChild());
}

int BinaryTree::getLevelByKey(Node* node, int key, int level) const {
    if (!node) {
        return -1;
    }
    if (node->key() == key) {
        return level;
    }
    if (key < node->key()) {
        return getLevelByKey(node->leftChild(), key, level + 1);
    }
    else {
        return getLevelByKey(node->rightChild(), key, level + 1);
    }
}

void BinaryTree::printLevels(Node* node, int level) const
{
    if (node == nullptr) {
        return;
    }

    if (level == 0) {
        std::cout << node->key() << " ";
        return;
    }

    printLevels(node->leftChild(), level - 1);
    printLevels(node->rightChild(), level - 1);
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

BinaryTree::Node* BinaryTree::remove(Node* node, Node* parent) {
    if (!node) {
        return nullptr;
    }

    Node* replacement = findReplacement(node);

    if (node == m_root) {
        m_root = replacement;
    }
    if (parent != nullptr) {
        if (parent->leftChild() == node) {
            parent->setLeftChild(replacement);
        }
        else {
            parent->setRightChild(replacement);
        }
    }

    delete node;
    return replacement;
}

BinaryTree::Node* BinaryTree::findReplacement(Node* node) {
    Node* replacement = nullptr;

    if (!node->leftChild() && !node->rightChild()) {
        replacement = nullptr;
    }

    else if (!node->leftChild()) {
        replacement = node->rightChild();
    }
    else if (!node->rightChild()) {
        replacement = node->leftChild();
    }
    else {
        replacement = node->rightChild();
        Node* replacementParent = node;

        while (replacement->leftChild() || replacement->rightChild()) {
            replacementParent = replacement;
            if (replacement->leftChild()) {
                replacement = replacement->leftChild();
            }
            else {
                replacement = replacement->rightChild();
            }
        }

        if (replacementParent != nullptr) {
            if (replacementParent->leftChild() == replacement) {
                replacementParent->setLeftChild(nullptr);
            }
            else {
                replacementParent->setRightChild(nullptr);
            }
            replacement->setLeftChild(node->leftChild());
            replacement->setRightChild(node->rightChild());
        }
    }
    return replacement;
}