#pragma once
#include <iostream>
#include "../../lab3/lab3/BinaryTreeSearch.h"

class BalancedTreeSearch : public BinaryTreeSearch
{
public:
    BalancedTreeSearch() = default;
    BalancedTreeSearch(const BalancedTreeSearch& other);
    BalancedTreeSearch(BalancedTreeSearch&& other) noexcept;
    ~BalancedTreeSearch() override = default;

    Node* addNode(int key) override;
    bool deleteNodeByKey(int key) override;

protected:
    Node* addNode(Node* root, int key, bool& isFixed);
    Node* remove(Node* node, int key, bool& isDeleted, bool& isFixed);

private:
    void newHeight(BalancedTreeSearch::Node* node);
    int heightDifference(const Node* node) const;
    Node* balancing(Node* node, bool& isFixed, bool isOperationAdd);
    Node* rotateRight(Node* middle);
    Node* rotateLeft(Node* middle);
};