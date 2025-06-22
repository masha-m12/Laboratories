#pragma once
#include <iostream>
#include <vector>
#include "../../lab2/lab2/BinaryTree.h"

class BinaryTreeSearch : public BinaryTree
{
public:
    BinaryTreeSearch() = default;
    BinaryTreeSearch(const BinaryTreeSearch& other);
    BinaryTreeSearch(BinaryTreeSearch&& other) noexcept;
    ~BinaryTreeSearch() override = default;

    using BinaryTree::min;
    using BinaryTree::max;
    using BinaryTree::addNode;
    using BinaryTree::deleteNodeByKey;
    using BinaryTree::searchNodeByKey;
    using BinaryTree::getLevelByKey;
    using BinaryTree::allTreeKeys;

    BinaryTreeSearch& operator=(const BinaryTreeSearch& other);
    BinaryTreeSearch& operator=(BinaryTreeSearch&& other) noexcept;

protected:
    int min(Node* node) const override;
    int max(Node* node) const override;

    Node* addNode(Node* root, int key) override;
    Node* searchMin(Node* node);
    Node* findReplacement(Node* node) override;
    Node* nlrSearch(Node* node, int key) const override;

    int getLevelByKey(Node* node, int key, int level) const override;
    void lrnTraversal(Node* root, std::vector<int>& keys) const override;
};