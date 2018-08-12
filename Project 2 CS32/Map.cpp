//
//  main.cpp
//  project 2
//
//  Created by Jonathan Goh on 1/26/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include <iostream>
#include "Map.h"
using namespace std;

Map::Map() // new map that is empty (size 0)
{
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}

bool Map::empty() const
{
    if(m_size == 0)
    {
        return true;
    }
    
    return false;
}

int Map::size() const
{
    return m_size;    //# Nodes that map is storing
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (contains(key))
    {
        return false; //if contains key already, then don't do anything
    }
    
    Node* p = new Node;
    
    p->pair.value = value;
    p->pair.key = key;
    
    if (empty())
    {
        head = p;
        tail = p;
    }
    
    
    
    p->previous = tail; //node added to start of map
    tail->next = p;
    tail = p;
    p->next = nullptr;
    m_size++;
    
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    Node* p = head;
    
    while (p != nullptr) //iterate through the entire list
    {
        if (p->pair.key == key) //if such a key exists
        {
            p->pair.value = value; //update its value
            return true;
        }
        
        p = p->next;
    }
    
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (update(key, value))
    {
        return true;
    }
    
    else
    {
        return (insert(key, value)); //this will always return true
    }
}

bool Map::erase(const KeyType& key)
{
    if (!contains(key)) //don't do anything if key doesn't exist
    {
        return false;
    }
    
    if (head == nullptr) //if list is empty don't do anything
    {
        return false;
    }
    
    Node* p = head;
    
    if (m_size == 1) //if there is one Node
    {
        m_size--;
        delete head;
        
        head = nullptr;
        tail = nullptr;
        
        return true;
    }

    while (p != nullptr) //if # Nodes greater than 1
    {
        if (p->pair.key == key)
        {
            if (p == tail)
            {
                tail = p->previous;
                tail->next = nullptr;
                delete p;
            }
            
            else if (p == head) //if it reaches the head pointer
            {
                head = p->next;
                head->previous = nullptr; //change prev to nullptr
                delete p;
            }
            
            else
            {
                Node* t2 = p->next;
                Node* t1 = p->previous;
                
                t1->next = t2; //sets to node after
                t2->previous = t1; //sets to node before
                
                delete p;
            }
            
            m_size--;
            
            return true;
        }
        p = p->next; //move to next node in the list
    }
    
    return false;
}

bool Map::contains(const KeyType& key) const
{
    Node* p = head;
    
    while (p != nullptr) //iterate through entire list
    {
        if (p->pair.key == key) //if the key is present return true
        {
            return true;
        }
        
        p = p->next; //move to next Node in the list
    }
    return false;
    
    
    /*
     Node* ptr = keyExists(key);
     if (ptr == nullptr)
     return false;
     return true;
     */
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node* p = head;
    
    while (p != nullptr) //iterate through entire list
    {
        if (p->pair.key == key)
        {
            value = p->pair.value; //sets the value to corresponding key
            
            return true;
        }
        
        p = p->next; //move to next Node in the list
    }
    return false; //returns false if no such key exists
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    Node* p = head;
    
    if (i >= size() || i < 0) //check if i is in bounds
    {
        return false;
    }
    
    for (int j = 0; j < i; j++) //moves to correct position of the list
    {
        p = p->next;
    }
    
    value = p->pair.value;
    key = p->pair.key; //changes respective values of key and value
    
    return true;
}

void Map::swap(Map& other)
{
    
    head = other.head; //switches the head and tail pointers
    tail = other.tail;
    
    Node* tHead = head; //makes temporary pointers for storage
    Node* tTail = tail;
    int tSize = size();
    
    other.head = tHead;
    other.tail = tTail;
    
    m_size = other.size(); //switches the respective sizes
    other.m_size = tSize;
}

Map::~Map()
{
    Node* p = head;
    
    while (p != nullptr) //iterate through the array until the end (nullptr)
    {
        Node* n = p->next; //another new pointer to store the next value of p
        delete p;    //deletes every instance of a node
        p = n;    //original pointer equals node of temp
    }
}

Map::Map(const Map &src)
{
    head=nullptr;
    tail=nullptr;
    m_size=0;
    
    for (int i = 0; i < src.size(); i++)
    {
        KeyType key;
        ValueType val;
        //for each value, call the get member function and then insert
        src.get(i, key, val);
        insert(key, val);
    }
}

Map& Map::operator=(const Map &src) //fixes alliasing
{
    if (&src == this) // if equal, then do nothing
    {
        return *this;
    }
    
    Map temp(src);    //constructs a temp Map identical to src
    swap(temp);
    
    return *this;
    
    /*
     if (this != &rhs) // Aliasing check
     {
     Map temp(rhs);
     swap(temp); // Might as well use the swap function with the copy constructor
     }
     return *this;
    */
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map temp1 = m1;
    Map temp2 = m2;
    temp1.swap(result);    //makes swap have all nodes of m1
    bool comb = true;
    
    for (int i = 0; i < temp2.size(); i++)
    {
        KeyType key;
        ValueType val;
        temp2.get(i, key, val);
        
        if (!result.contains(key))    //if m1 does not contain node of m2
            result.insert(key, val);    //add node
        else
        {
            ValueType val2;
            result.get(key, val2);
            if (val != val2)    //if m1 and m2 have same key but different values
            {
                result.erase(key);    //removes from result Map
                comb = false;    //sets bool comb to false
            }
        }
    }
    return comb;    //after making result Map, not returns true/false
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map temp1 = m1;
    Map temp2 = m2;
    Map empty;
    empty.swap(result);    //swaps result with an empty Map
    
    for (int i = 0; i < temp1.size(); i++)
    {
        KeyType key;
        ValueType val;
        temp1.get(i, key, val);    //gets key and value
        
        if (!temp2.contains(key))    //if m2 does not have key of m1
            result.insert(key, val);    //insert into result
    }
}
