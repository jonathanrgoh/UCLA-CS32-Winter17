#ifndef _STUDENTWORLD_H_
#define _STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <list>
#include <vector>
#include <stdlib.h>

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, actor.h, and actor.cpp
class Actor;
class StudentWorld : public GameWorld
{
public:
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    bool addActor(int type, int x, int y, int firedBy);
    int getlevelNumber() const;
    double getHealthPct() const;
    double getCabbagePct() const;
    int numberOfActiveAliens() const;
    void updateDisplayText();
    list<Alien*> getCollidingAliens(Actor* a);
    NachenBlaster* getCollidingPlayer(Actor* a);
    NachenBlaster* getNachenBlaster();
    int getNumAlienFiredProjectiles() const;
    string formatDisplay(int lives, double healthPercent, int score, int level, double cabbagePercent, int torpedos);
    StudentWorld();
    ~StudentWorld();
private:
    vector<Actor*> m_actors;
    int m_nStars;
    NachenBlaster* ptrToShip;
    int m_nActiveAliens;
    int m_levelNumber;
    int m_AliensDestroyed;
    int tick;
    
};

#endif // _GAMEWORLD_H_
