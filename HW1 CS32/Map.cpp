//
//  main.cpp
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/19/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//


#include "Map.h"
#include <algorithm>


Map::Map()
{
    m_size=0;
}

int Map::keyExists(const KeyType& key) const
{
    
    for(int i=0; i<m_size; i++)
    {
        if(key==m_stuff[i].m_key)
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
    if(m_size>=DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    
    int stuff=keyExists(key);
    
    if(stuff!=-1)
    {
        return false;
    }
    
    m_stuff[m_size].m_key = key;
    m_stuff[m_size].m_value = value;
    m_size++;
    
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    int stuff=keyExists(key);
    
    if (stuff==-1)
    {
        return false;
    }
    
    m_stuff[stuff].m_key = key;
    m_stuff[stuff].m_value = value;
    
    return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    int stuff=keyExists(key);
    
    if (stuff==-1)
    {
        if(insert(key, value))
        {
            return true;
        }
        
        else
        {
            return false;
        }
    }
    
    else
    {
        update(key, value);
    }
    
    return true;
}

bool Map::erase(const KeyType& key)
{
    int stuff=keyExists(key);
    
    if (stuff>-1)
    {
        if(stuff==m_size - 1)
        {
            m_size--;
            return true;
        }
        
        for (; stuff < m_size-1; stuff++)
        {
            m_stuff[stuff] = m_stuff[stuff+1];
        }
        
        m_size--;
        
        return true;
    }
    return false;
}

bool Map::contains(const KeyType& key) const
{
    return (keyExists(key)>-1);
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
    std::swap(*this, other);
}
