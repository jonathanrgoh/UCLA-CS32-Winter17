//
//  Player.h
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/16/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "History.h"



/*class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    char m_notConverted;
    char grids[MAXROWS][MAXCOLS]={{0}};
    City* m_city;
    int m_cols;
    int m_rows;
};*/

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};



#endif /* Player_h */
