#include <iostream>
#include "HashTable.h"

HashTable::HashTable()
{}

HashTable::HashTable(const HashTable& other)
    :m_size(other.m_size), m_capacity(other.m_capacity), m_table(other.m_table)
{}

HashTable::~HashTable() {
	delete m_function;
}

void HashTable::add(int key, const std::string& value) {
    if (m_function == nullptr) {
        return;
    }

    int hash = m_function->computeHash(key, m_capacity);
    auto it = find(key, hash);

    if (it != m_table[hash].end()) {
        it->second = value;
    }
    else {
        m_table[hash].emplace_back(key, value);
        m_size++;
    }
}

bool HashTable::remove(int key) {
    int hash = m_function->computeHash(key, m_capacity);
    auto& chain = m_table[hash];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            chain.erase(it);
            m_size--;
            return true;
        }
    }
    return false;
}

bool HashTable::contains(int key) {
    int hash = m_function->computeHash(key, m_capacity);
    auto it = find(key, hash);

    if (it != m_table[hash].end()) {
        return true;
    }
    else {
        return false;
    }
}

void HashTable::swap(HashTable& other) {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_function, other.m_function);
    std::swap(m_table, other.m_table);
}

HashTable& HashTable::operator=(const HashTable& other) {
    if (this == &other) {
        return *this;
    }
    HashTable hash(other);
    swap(hash);
    return *this;
}

std::list<std::pair<int, std::string>>::iterator HashTable::find(int key, int hash) {
    auto& chain = m_table[hash];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            return it;
        }
    }
    return chain.end();
}