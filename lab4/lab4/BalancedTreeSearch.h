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

    BalancedTreeSearch& operator=(const BalancedTreeSearch& other);
    BalancedTreeSearch& operator=(BalancedTreeSearch&& other) noexcept;

    Node* copyNodeSubtree(Node* root);

protected:

private:
    int heightDifference(const Node* node) const;
    Node* balancing(Node* node, bool& isFixed);
    Node* rotateRight(Node* middle);
    Node* rotateLeft(Node* middle);
};