//
//  newMap.cpp
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/22/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include "newMap.h"
// #include <algorithm>
Map::Map(int number)
{
    m_capacity=number;
    m_size=0;
    m_stuff=new match[number];
}

Map::~Map()
{
    delete [] m_stuff;
}

Map::Map(const Map& jon)
{
    m_capacity=jon.m_capacity;
    m_size=jon.m_size;
    m_stuff=new match[m_capacity];
    
    for (int i=0; i<m_size; i++)
    {
        m_stuff[i]=jon.m_stuff[i];
    }
}

Map& Map::operator=(const Map& jon)
{
    if (this!=&jon)
    {
        delete [] m_stuff;
        
        m_capacity=jon.m_capacity;
        m_size=jon.m_size;
        m_stuff=new match[m_capacity];
        
        for (int i=0; i<m_size; i++)
        {
            m_stuff[i]=jon.m_stuff[i];
        }
    }
    
    return *this;
}

int Map::keyExists(const KeyType& key) const
{
    for (int i=0; i<m_size; i++)
    {
        if (key==m_stuff[i].m_key)
        {
            return i;
        }
    }
    
    return -1;
}

bool Map::empty() const
{
    return (m_size==0);
}

int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (m_size>=m_capacity)
    {
        return false;
    }
    
    int i=keyExists(key);
    
    if (i!=-1)
    {
        return false;
    }
    
    m_stuff[m_size].m_value = value;
    m_stuff[m_size].m_key = key;
    m_size++;
    
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    int i = keyExists(key);
    
    if (i == -1)
    {
        return false;
    }
    
    m_stuff[i].m_value = value;
    m_stuff[i].m_key = key;
    
    return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    int i=keyExists(key);
    
    if (i==-1)
    {
        if(insert(key, value))
        {
            return true;
        }
        return false;
    }
    
    update(key, value);
    
    return true;
}

bool Map::erase(const KeyType& key)
{
    int i=keyExists(key);
    
    if (i >= 0)
    {
        if(i == m_size - 1)
        {
            m_size=m_size-1;
            return true;
        }
        for (; i < m_size-1; i++)
        {
            m_stuff[i] = m_stuff[i+1];
        }
        m_size=m_size-1;
        return true;
    }
    
    return false;
}

bool Map::contains(const KeyType& key) const
{
    return (keyExists(key) != -1);
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    int i=keyExists(key);
    
    if (i==-1)
    {
        return false;
    }
    
    value=m_stuff[i].m_value;
    
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i<0 || i>=size())
    {
        return false;
    }
    
    key=m_stuff[i].m_key;
    value=m_stuff[i].m_value;
    
    return true;
}

void Map::swap(Map& other)
{
    
    int sizeTemp=m_size;
    int capacityTemp=m_capacity;
    match* ptrTemp=m_stuff;
    
    m_size=other.m_size;
    m_capacity=other.m_capacity;
    m_stuff=other.m_stuff;
    
    other.m_size=sizeTemp;
    other.m_capacity=capacityTemp;
    other.m_stuff=ptrTemp;
}

