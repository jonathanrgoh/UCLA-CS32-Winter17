//
//  History.h
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/16/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
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
};

#endif /* History_h */
