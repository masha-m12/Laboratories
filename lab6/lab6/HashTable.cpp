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