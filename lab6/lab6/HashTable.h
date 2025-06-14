#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>

class HashTable {
public:
    HashTable();
    HashTable(const HashTable& other);
    ~HashTable();

    void add(int key, std::string& value);
    bool remove(int key);

    bool contains(int key) const;
    void swap(HashTable& other);
    void print();
    void resize(int capacity);
    void setHashFunction(HashFunction* function);

    HashTable& operator=(const HashTable& other);

    std::string& operator[](int key);
    const std::string& operator[](int key) const;

private:
    int m_size;
    int m_capacity;
    HashFunction* m_function;
    std::vector<std::list<std::pair<int, std::string>>> m_table;
};

class HashFunction {
public:
    virtual int computeHash(int key, int capacity) = 0;
    virtual ~HashFunction() = default;
};

class HashFunctionFirst : public HashFunction {
public:
    int computeHash(int key, int capacity) override;
    int c = 18 % 5;
    int d = 18 % 7;
};