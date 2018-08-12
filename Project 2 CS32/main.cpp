//
//  main.cpp
//  project 2
//
//  Created by Jonathan Goh on 1/26/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    double d = 42;
    assert(m.get("Fred", d) && d == 123);
    d = 42;
    string s1;
    assert(m.get(0, s1, d) && ((s1 == "Fred" && d == 123) || (s1 == "Ethel" && d == 456)));
    string s2;
    assert(m.get(1, s2, d) && s1 != s2 && ((s2 == "Fred" && d == 123) || (s2 == "Ethel" && d == 456)));
}

bool empty() { return true; }

int main()
{
    test();
    
    Map m1;
    assert(m1.size() == 0);
    assert(m1.empty());
    assert(!m1.contains("testKey"));
    assert(m1.insert("testKey", 0));
    KeyType k1;
    ValueType v1;
    assert(!m1.insert("testKey", 0));
    assert(m1.get("testKey", v1));
    assert(v1 == 0);
    assert(m1.size() == 1);
    assert(m1.update("testKey", 10));
    assert(m1.get("testKey", v1));
    assert(v1 == 10);
    assert(m1.get(0, k1, v1));
    assert(k1 == "testKey" && v1 == 10);
    assert(!m1.get(1, k1, v1));
    assert(m1.insertOrUpdate("Key2", 1));
    assert(m1.size() == 2);
    assert(m1.contains("testKey") && m1.contains("Key2"));
    assert(m1.insertOrUpdate("Key2", 100));
    assert(m1.get("Key2", v1));
    assert(v1 == 100);
    KeyType k2;
    ValueType v2;
    assert(m1.get(0, k1, v1) && m1.get(1, k2, v2));
    assert(!m1.erase("NotExist"));
    assert(m1.erase("testKey"));
    assert(m1.size() == 1);
    assert(!m1.contains("testKey"));
    assert(m1.get(0, k1, v2));
    assert(k1 == "Key2" && v2 == 100);
    assert(!m1.get(1, k1, v1));
    assert(m1.insert("Key3", 3) && m1.insert("Key4", 4) && m1.insert("Key5", 5));
    assert(m1.size() == 4);
    Map m2;
    assert(m2.empty());
    m1.swap(m2);
    assert(m1.empty());
    assert(m2.size() == 4);
    const Map emptyMap;
    m1 = emptyMap;
    m2 = emptyMap;
    assert(m1.empty() && m2.empty());
    m1.insert("Fred", 123);
    m1.insert("Ethel", 456);
    m1.insert("Lucy", 789);
    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);
    Map result;
    assert(combine(m1, m2, result));
    assert(result.size() == 4);
    assert(result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel"));
    Map m4(m1);
    assert(combine(m4, m2, result));
    assert(result.size() == 4);
    assert(result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel"));
    m2 = emptyMap;
    m2.insert("Lucy", 654);
    m2.insert("Ricky", 321);
    assert(!combine(m1, m2, result));
    assert(result.size() == 3);
    assert(result.contains("Fred") && result.contains("Ricky") && result.contains("Ethel") && !result.contains("Lucy"));
    result = emptyMap;
    Map& result2 = m1;
    m2 = emptyMap;
    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);
    m2.insert("Ethel", 654);
    subtract(m1, m2, result2);
    assert(result2.size() == 1);
    assert(result2.contains("Fred"));
    Map original;
    original.insert("one", 1);
    original.insert("two", 2);
    original.insert("three", 3);
    original.swap(original);
    assert(original.size() == 3);
    m1 = emptyMap;
    m2 = emptyMap;
    m2.insert("name1", 0);
    m1.insert("name1", 1);
    m1.insert("name2", 2);
    combine(m1, m2, m1);
    assert(m1.size() == 1);
    assert(!m1.contains("name1"));
    Map m8(m1);
    assert(!m8.insert("testKey", 0));
    assert(m8.get("testKey", v1));
    assert(v1 == 10);
    v1 = 0;
    
    std::cerr << "All tests succeeded!" << endl;
}


