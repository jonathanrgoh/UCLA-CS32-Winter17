//
//  testCarMap.cpp
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/22/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include "CarMap.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main()
{
    CarMap c;
    
    c.addCar("Car1");
    assert(c.fleetSize() == 1);
    c.addCar("Car2");
    assert(c.fleetSize() == 2);
    assert(c.gas("Car1") == 0 && c.gas("Car2") == 0);
    assert(c.addGas("Car2", 10));
    assert(c.gas("Car2") == 10);
    assert(c.addGas("Car2", 15));
    assert(c.gas("Car2") == 25);
    assert(!c.addGas("Car1", -1000));
    assert(c.gas("Car1") == 0);
    assert(c.addGas("Car1", 100));
    assert(c.gas("Car1") == 100);
    
    std::cerr << "\nPart 1\n";
    c.print();
    
    
    CarMap cc(c);
    assert(cc.fleetSize() == 2);
    assert(cc.gas("Car1") == 100);
    assert(cc.gas("Car2") == 25);
    assert(cc.useGas("Car1", 1000)==false);
    assert(cc.useGas("Car1", 50)==true);
    assert(cc.gas("Car1") == 50);
    std::cerr << "\nPart 2\n";
    cc.print();
    
    cout << "Passed all tests" << endl;
    
    
//    ValueType v = -1234.5;
//    assert( !c.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
//    c.insert("xyz", 9876.5);
//    assert(c.size() == 1);
//    KeyType k = "hello";
//    assert(c.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
//    cout << "Passed all tests" << endl;
}

