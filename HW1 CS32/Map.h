//
//  Header.h
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/19/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED
#include <string>

typedef std::string KeyType;
typedef double ValueType;

const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
    
    Map();
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const KeyType& key, const ValueType& value);
    
    bool update(const KeyType& key, const ValueType& value);
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    
    bool erase(const KeyType& key);
    
    bool contains(const KeyType& key) const;
    
    bool get(const KeyType& key, ValueType& value) const;
    
    bool get(int i, KeyType& key, ValueType& value) const;
    
    void swap(Map& other);
    
private:
    
    int m_size;
    int keyExists(const KeyType& key) const;
    
    struct match
    {
        KeyType m_key;
        ValueType m_value;
    };
    match m_stuff[DEFAULT_MAX_ITEMS];
};
#endif /* defined(MAP_INCLUDED) */
