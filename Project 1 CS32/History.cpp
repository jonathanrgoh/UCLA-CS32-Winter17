//
//  History.cpp
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/16/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

#include <stdio.h>
#include "Flatulan.h"
#include "Player.h"
#include "History.h"
#include "City.h"
#include "Game.h"
#include "globals.h"

void clearScreen();

History::History(int nRows, int nCols)
{
    m_rows=nRows;
    m_cols=nCols;
    
}

bool History::record(int r, int c)
{
    if(r<1||c<1||r<MAXROWS||c<MAXCOLS)
    {
        return false;
    }
    else
    {
        for (int r = 0; r < m_rows; r++)
        {
            for (int c = 0; c < m_cols; c++)
                if(grids[r][c]=='0')
                    grids[r][c]='.';
        }
        
        if (grids[r-1][c-1]=='.')
            grids[r-1][c-1]='A';
        else if (grids[r-1][c-1]!='Z')
            grids[r-1][c-1]+=1;
        /* for (int row = 0; row < m_rows; r++)
         {
         for (int col = 0; col < m_cols; c++)
         {
         char& gridsChar = grids[row][col];
         switch (gridsChar)
         {
         case ' ':   gridsChar = '.'; break;
         case '.':  gridsChar = 'A'; break;
         case 'Z':  break;
         default:   gridsChar++; break;  // 'A' through 'Z'
         }
         }
         }
         */
        return true;
    }
}

void History::display() const
{
    clearScreen();
    
    // Draw the grid
    
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
            cout << grids[r][c];
        cout << endl;
    }
    cout << endl;
    
}
