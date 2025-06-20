#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>

class HashFunction {
public:
    virtual int computeHash(int key, int capacity) const = 0;
    virtual HashFunction* clone() const = 0;
    virtual ~HashFunction() = default;
};

class HashFunctionFirst : public HashFunction {
public:
    int computeHash(int key, int capacity) const override;
    HashFunction* clone() const override;
};

class HashFunctionThird : public HashFunction {
public:
    int computeHash(int key, int capacity) const override;
    HashFunction* clone() const override;
};

class HashTable {
public:
    HashTable();
    HashTable(int capacity, HashFunction* function);
    HashTable(const HashTable& other);
    ~HashTable();

    void add(int key, const std::string& value);
    bool remove(int key);

    bool contains(int key);
    void swap(HashTable& other);
    void print() const;
    void resize(int capacity);
    void setHashFunction(HashFunction* function);
    HashFunction* getHashFunction();

    HashTable& operator=(const HashTable& other);

    std::string& operator[](int key);
    const std::string& operator[](int key) const;

private:
    void rehash();
    std::list<std::pair<int, std::string>>::iterator find(int key, int hash);
    std::list<std::pair<int, std::string>>::const_iterator find(int key, int hash) const;

    int m_size;
    int m_capacity;
    HashFunction* m_function;
    std::vector<std::list<std::pair<int, std::string>>> m_table;
};