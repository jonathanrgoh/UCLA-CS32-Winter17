//
//  CarMap.cpp
//  HW1 CS32
//
//  Created by Jonathan Goh on 1/22/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include "CarMap.h"
#include <iostream>

CarMap::CarMap()
{
    
}

bool CarMap::addCar(std::string license)
{
    if(m_license.insert(license, 0))
    {
        return true;
    }
    return false;
}

double CarMap::gas(std::string license) const
{
    double gasCount;
    
    return (m_license.get(license, gasCount) ? gasCount : -1);

//    double gasCount=0;
//    if(m_license.contains(license))
//    {
//        m_license.get(license, gasCount);
//        return true;
//    }
//    return -1;
}
//// If a car with the given license plate is in the map, return the
//// number of gallons of gas in its tank; otherwise, return -1.

bool CarMap::addGas(std::string license, double gallons)
{
    double current;
    
    if (!m_license.get(license, current) || gallons < 0)
    {
        return false;
    }
    
    current+=gallons;
    
    return m_license.update(license, current);
//    double current=0;
//    if(m_license.contains(license) && gallons>=0)
//    {
//        current = (gas(license)+gallons);
//        m_license.update(license, current);
//        return true;
//    }
//    return false;
}
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.

bool CarMap::useGas(std::string license, double gallons)
{
    double current;
    
    if (!m_license.get(license, current) || gallons < 0 || gas(license)<gallons)
        return false;
    
    current-=gallons;
    
    return m_license.update(license, current);
    
}
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.

int CarMap::fleetSize() const
{
    return m_license.size();
}// Return the number of cars in the CarMap.

void CarMap::print() const
{
    for(int i = 0; i < fleetSize(); i++)
    {
        KeyType j;
        ValueType k;
        m_license.get(i, j, k);
        std::cout<<j<<" "<<k<< std::endl;
    }
}
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.

