#pragma once

#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include "C:/Users/Mariya/Desktop/Gittyup/OOP/BoolVector/BoolVector/BoolVector.h"

class HuffmanTree
{
    class Node
    {
    public:
        Node();
        ~Node();

        std::string stringifySymbols() const;

        void printHorizontal(Node* root, int marginLeft = 0, int levelSpacing = 4) const;

        int frequency() const;
        void setFrequency(int frequency);

        const BoolVector& symbols() const;
        void setSymbols(const BoolVector& symbols);

        Node* left() const;
        void setLeft(Node* left);

        Node* right() const;
        void setRight(Node* right);

    private:
        int m_frequency;
        BoolVector m_symbols = BoolVector(256, 0);

        Node* m_left = nullptr;
        Node* m_right = nullptr;
    };

public:
    HuffmanTree() = default;
    ~HuffmanTree();

    void clear();

    void print();

    void build(const std::string& fileName);
    double encode(const std::string& fileName, const std::string& encodedFileName);
    bool decode(const std::string& encodedText, std::string& decodedText);

private:
    std::string encode(const char symbol, Node* node);
    bool decode(std::istream& encodedStream, std::ostream& decodedStream);

private:
    Node* m_root = nullptr;
};