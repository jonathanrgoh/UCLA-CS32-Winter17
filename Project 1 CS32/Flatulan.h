//
//  Header.h
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/11/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef Flatulan_h
#define Flatulan_h

class City;
class History;

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    History* m_history;
    int   m_row;
    int   m_col;
};


#endif /* Header_h */
