#include <iostream>
#include "HashTable.h"

HashTable::HashTable() : HashTable(10, new HashFunctionFirst()) {}

HashTable::HashTable(int capacity, HashFunction* function)
    : m_size(0), m_capacity(capacity), m_function(function) {
    m_table.resize(m_capacity);
}

HashTable::HashTable(const HashTable& other)
    :m_size(other.m_size), m_capacity(other.m_capacity), m_function(other.m_function->clone()), m_table(other.m_table)
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

void HashTable::print() const {
    std::cout << "HashTable: number of elements: " << m_size << ", capacity: " << m_capacity << "\n";
    for (int i = 0; i < m_capacity; ++i) {
        const auto& chain = m_table[i];
        if (!chain.empty()) {
            for (const auto& pair : chain) {
                std::cout << "Key: " << pair.first << ", value: " << pair.second << "\n";
            }
        }
    }
}

void HashTable::resize(int capacity) {
    if (capacity <= m_size) {
        return;
    }

    m_capacity = capacity;
    rehash();
}

void HashTable::setHashFunction(HashFunction* function) {
    if (!function) {
        return;
    }

    delete m_function;
    m_function = function;
    rehash();
}

HashFunction* HashTable::getHashFunction() {
    return m_function;
}

HashTable& HashTable::operator=(const HashTable& other) {
    if (this == &other) {
        return *this;
    }
    HashTable hash(other);
    swap(hash);
    return *this;
}

std::string& HashTable::operator[](int key) {
    int hash = m_function->computeHash(key, m_capacity);

    for (auto& pair : m_table[hash]) {
        if (pair.first == key) {
            return pair.second;
        }
    }

    m_table[hash].emplace_back(key, std::string{});
    m_size++;

    return m_table[index].back().second;
}

const std::string& HashTable::operator[](int key) const {
    int hash = m_function->computeHash(key, m_capacity);
    auto it = find(key, hash);

    if (it != m_table[hash].end()) {
        return it->second;
    }
    else {
        std::cerr << "Key wasn't found in HashTable";
    }
}

void HashTable::rehash() {
    std::vector<std::list<std::pair<int, std::string>>> newTable(m_capacity);
    int newSize = 0;

    for (const auto& chain : m_table) {
        for (const auto& pair : chain) {
            int newHash = m_function->computeHash(pair.first, m_capacity);
            newTable[newHash].push_back(pair);
            newSize++;
        }
    }
    m_table.swap(newTable);
    m_size = newSize;
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

std::list<std::pair<int, std::string>>::const_iterator HashTable::find(int key, int hash) const {
    const auto& chain = m_table[hash];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            return it;
        }
    }
    return chain.end();
}

int HashFunctionFirst::computeHash(int key, int capacity) const {
    if (capacity == 0) {
        return 0;
    }

    const int c = 18 % 5;
    const int d = 18 % 7;

    int h0 = key % capacity;
    return (h0 + c + d) % capacity;
}

HashFunction* HashFunctionFirst::clone() const {
    return new HashFunctionFirst(*this);
}

int HashFunctionThird::computeHash(int key, int capacity) const {
    if (capacity == 0) {
        return 0;
    }

    int h0 = key % capacity;
    return ((h0 + 1) * (1 + key % (capacity - 2))) % capacity;
}

HashFunction* HashFunctionThird::clone() const {
    return new HashFunctionThird(*this);
}