#include <iostream>
#include <numeric>

#include "HuffmanTree.h"

int main()
{
    HuffmanTree tree;
    tree.build("ehal greka cerez reku");
    tree.print();
    return 0;
}

BoolVector::BoolVector(int length)
    : m_length(length) {
    m_cellCount = m_length / CellSize;
    if (m_length % CellSize != 0) {
        m_cellCount++;
    }
    m_cells = new Cell[m_cellCount];
}