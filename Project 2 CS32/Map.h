//
//  Map.h
//  project 2
//
//  Created by Jonathan Goh on 1/26/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef Map_h
#define Map_h
#include <string>

typedef std::string KeyType;
typedef double ValueType;

//typedef int KeyType;
//typedef std::string ValueType;

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
    ~Map();
    Map(const Map &src);
    Map& operator=(const Map &src);
    
private:
    struct data
    {
        KeyType key;
        ValueType value;
    };
    
    struct Node
    {
        data pair;
        Node* next;
        Node* previous;
    };
    
    Node *head;
    Node *tail;
    int m_size;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

#endif /* Map_h */
