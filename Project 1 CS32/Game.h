//
//  Game.h
//  Project 1 CS32
//
//  Created by Jonathan Goh on 1/16/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

#endif /* Game_h */
