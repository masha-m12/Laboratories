#include <algorithm>
#include <vector>
#include <string>
#include "HuffmanTree.h"

HuffmanTree::Node::Node()
{}

HuffmanTree::Node::~Node()
{
    if (m_left)
    {
        delete m_left;
    }
    if (m_right)
    {
        delete m_right;
    }
}

std::string HuffmanTree::Node::stringifySymbols() const
{
    std::string str;
    for (int i = 0; i < m_symbols.length(); ++i)
    {
        if (m_symbols[i])
        {
            str += char(i);
        }
    }
    return str;
}

void HuffmanTree::Node::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }
    printHorizontal(root->m_right, marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ');
    std::cout << root->m_frequency << ' ' << root->stringifySymbols();
    std::cout << std::endl;
    printHorizontal(root->m_left, marginLeft + levelSpacing, levelSpacing);
}

int HuffmanTree::Node::frequency() const {
    return m_frequency;
}

void HuffmanTree::Node::setFrequency(int frequency) {
    m_frequency = frequency;
}

const BoolVector& HuffmanTree::Node::symbols() const {
    return m_symbols;
}

void HuffmanTree::Node::setSymbols(const BoolVector& symbols) {
    m_symbols = symbols;
}

HuffmanTree::Node* HuffmanTree::Node::left() const {
    return m_left;
}

void HuffmanTree::Node::setLeft(Node* left) {
    m_left = left;
}

HuffmanTree::Node* HuffmanTree::Node::right() const {
    return m_right;
}

HuffmanTree::~HuffmanTree()
{
    clear();
}

void HuffmanTree::clear()
{
    if (m_root)
    {
        delete m_root;
        m_root = nullptr;
    }
}

void HuffmanTree::print()
{
    m_root->printHorizontal(m_root);
}

void HuffmanTree::build(const std::string& text)
{
    if (m_root)
    {
        clear();
    }

    std::vector<Node*> nodes;
    for (const char& symbol : text)
    {
        std::vector<Node*>::iterator it = std::find_if(
            nodes.begin(),
            nodes.end(),
            [&symbol](Node* node) // Безымянная функция
            {
                return node->symbols().bitValue(symbol);
            }
        );

        if (it == nodes.end())
        {
            Node* newNode = new Node;
            newNode->setFrequency(1);
            BoolVector bv(256, 0);
            bv.setBitValue(symbol, 1);
            newNode->setSymbols(bv);
            nodes.push_back(newNode);
        }
        else
        {
            Node* node = *it;
            node->setFrequency(node->frequency() + 1);
        }
    }

    // Ещё одна безымянная функция, сложили в переменную
    auto sorter = [](Node* a, Node* b) -> bool
        {
            return a->frequency() < b->frequency();
        };
    std::sort(nodes.begin(), nodes.end(), sorter);

    while (nodes.size() > 1)
    {
        Node* root = new Node();
        root->setFrequency(nodes[0]->frequency() + nodes[1]->frequency());

        BoolVector bv = nodes[0]->symbols() | nodes[1]->symbols();
        root->setSymbols(bv);

        root->setLeft(nodes[0]);
        root->setRight(nodes[1]);

        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(root);
        std::sort(nodes.begin(), nodes.end(), sorter);
    }

    m_root = nodes.front();
}

double HuffmanTree::encode(const std::string& text, std::string& encodedText)
{

}

bool HuffmanTree::decode(const std::string& encodedText, std::string& decodedText)
{

}

std::string HuffmanTree::encode(const char symbol)
{

}

bool HuffmanTree::decode(std::istream& encodedStream, std::ostream& decodedStream)
{

}