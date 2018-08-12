//
//  mainRough.cpp
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/12/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

// gas.cpp
#include "Flatulan.h"
#include "Player.h"
#include "History.h"
#include "City.h"
#include "Game.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}

