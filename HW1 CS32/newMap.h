//
//  testMap.h
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/22/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef testMap_h
#define testMap_h
#include <string>

typedef std::string KeyType;
typedef double ValueType;

const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
    Map(int num = DEFAULT_MAX_ITEMS);
    
    ~Map();
    
    Map(const Map& jon);
    
    Map& operator=(const Map& jon);
    
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
    int m_capacity;
    int keyExists(const KeyType& key) const;
    
    struct match
    {
        KeyType m_key;
        ValueType m_value;
    };
    match* m_stuff;
    // Returns -1 if supplied key does not exist in the map
    // Otherwise, returns the index of the found key in m_mapData
};
#endif /* testMap_h */

