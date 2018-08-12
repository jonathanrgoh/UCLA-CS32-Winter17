#include "StudentWorld.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

GameWorld* createStudentWorld(string assetDir = "")
{
    return new StudentWorld();
}

StudentWorld::StudentWorld()
: m_nStars(0), m_nActiveAliens(0), m_levelNumber(1), m_AliensDestroyed(0), GameWorld("/Users/jonathangoh/Desktop/NachenBlaster 2/DerivedData/NachenBlaster/Build/Products/Debug/Assets")
{

}

StudentWorld::~StudentWorld()
{
    //delete ptrToShip;//is this necessary?
    for (int i = 0; i < m_actors.size(); i++)
    {
        delete m_actors[i];
        //m_actors.erase(m_actors.begin()+i);
    }
}

bool StudentWorld::addActor(int type, int x, int y, int firedBy)//fired by alien(2) or player(1) or not fired (0)
{
    if (type < 1 || type>11)//id numbers for all actors except NachenBlaster and star
        return false;
    
    if (firedBy < 0 || firedBy > 2)
        return false;
    
    switch (type)
    {
        case IID_Smallgon:
            //m_actors.push_back(new Smallgon(this, m_levelNumber));
            break;
        case IID_SMOREGON:
            //m_actors.push_back(new Smoregon(this, m_levelNumber));
            break;
        case IID_SNAGGLEGON:
            //m_actors.push_back(new Snagglegon(this, m_levelNumber));
            break;
        case 9://IID_CABBAGE:
            m_actors.push_back(new CabbageBullet(this, x, y, 1));
            break;
        case 8://IID_TURNIP:
            m_actors.push_back(new TurnipBullet(this, x, y, 2));
            break;
        case 7://IID_TORPEDO:
            m_actors.push_back(new FlatulenceTorpedo(this, x, y, firedBy));
            break;
        case IID_LIFE_GOODIE:
            m_actors.push_back(new LifeGoodie(this, x, y));
            break;
        case IID_REPAIR_GOODIE:
            m_actors.push_back(new RepairGoodie(this, x, y));
            break;
        case IID_TORPEDO_GOODIE:
            m_actors.push_back(new TorpedoGoodie(this, x, y));
            break;
        case IID_EXPLOSION:
            m_actors.push_back(new Explosion(this, x, y));
            break;
            return true;
    }
    return true;
}


int StudentWorld::numberOfActiveAliens() const
{
    return m_nActiveAliens;
}

int StudentWorld::getlevelNumber() const
{
    return m_levelNumber;
}

void StudentWorld::updateDisplayText()
{
    int score = getScore();
    int level = getlevelNumber();
    double healthPercent = ptrToShip->getHealthPct();
    double cabbagePercent = ptrToShip->getCabbagePct();
    int torpedos = ptrToShip->getNumTorpedos();
    int lives = getLives();
    string s = formatDisplay(lives, healthPercent, score, level, cabbagePercent, torpedos);
    setGameStatText(s);
}

string StudentWorld::formatDisplay(int lives, double healthPercent, int score, int level, double cabbagePercent, int torpedos)
{
    ostringstream oss;
    oss.fill('0');
    oss << "Lives: " << setw(2) << lives << "  Health: "
    << healthPercent << "%  Score: " << setw(7) << score << "  Level: " << setw(2) << level << "  Cabbages: " << cabbagePercent << "%  Torpedoes: " << setw(3) << torpedos;
    
    return oss.str();
}

NachenBlaster* StudentWorld::getNachenBlaster()
{
    return ptrToShip;
}

int StudentWorld::getNumAlienFiredProjectiles() const
{
    int count = 0;
    for (int i = 0; i < m_actors.size(); i++)
    {
        Bullet* p = dynamic_cast<Bullet*>(m_actors[i]);
        if (p != NULL)
        {
            if (p->firedBy() == 2)
                count++;
        }
    }
    return count;
}

NachenBlaster* StudentWorld::getCollidingPlayer(Actor* a)
{
    if (sqrt( (pow((ptrToShip->getX() - a->getX()), 2) + pow((ptrToShip->getY() - a->getY()), 2))  < .75*(ptrToShip->getRadius() + a->getRadius())  ))
        return ptrToShip;
    else
        return NULL;
    
}

list<Alien*> StudentWorld::getCollidingAliens(Actor* a)
{
    list<Alien*> collidedWith;
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (sqrt( (pow((m_actors[i]->getX() - a->getX()), 2) + pow((m_actors[i]->getY() - a->getY()), 2))  < (.75*(m_actors[i]->getRadius() + a->getRadius() + 20))  ))
        {
            Alien* b = dynamic_cast<Alien*>(m_actors[i]);
            if (b != NULL)
                collidedWith.push_front(b);
        }
    }
    return collidedWith;
}




int StudentWorld::init()
{
    ptrToShip = new NachenBlaster(this);
    m_nActiveAliens = 0;
    m_AliensDestroyed = 0;
    m_nStars = 0;
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    tick++;
    
    //Creates Correct Amount of Aliens
    int S,S1,S2,S3;
    S1=60;
    S2=20+(m_levelNumber * 5);
    S3=5+(m_levelNumber * 10);
    S=S1+S2+S3;
    
        int maxAliens = (4+(.5 * m_levelNumber));
        if (m_nActiveAliens < maxAliens)
        {
            int random1 = randInt(1, S);
            
            if(random1 < S1)
            {
                m_actors.push_back(new Smallgon(this, m_levelNumber));
                m_nActiveAliens++;
            }
            else if(random1 >= S1 && random1 < S1+S2)
            {
                m_actors.push_back(new Smoregon(this, m_levelNumber));
                m_nActiveAliens++;
            }
            else if(random1 >= S1+S2 && random1 < S)
            {
                m_actors.push_back(new Snagglegon(this, m_levelNumber));
                m_nActiveAliens++;
            }
            
        }
   // }

    //CREATES STARS
    
    if (m_nStars==0)
    {
        m_nStars=31;
        for(int i=0; i<30;i++)
        {
            m_actors.push_back(new Star(this,randInt(0,VIEW_WIDTH-1),randInt(0,VIEW_HEIGHT-1)));
        }
    }
    
    if (m_nStars >= 31)
    {
        m_nStars=1;
    }
    
    if (m_nStars < 31)
    {
        int rnd=randInt(1,15);
        if(rnd==5)
        {
            //m_actors.push_back(new Star(this,randInt(0,VIEW_WIDTH-1),randInt(0,VIEW_HEIGHT-1)));
            m_actors.push_back(new Star(this));
            m_nStars++;
        }
    }
    
    
    //UPDATE THE GAME STATUS LINE
    updateDisplayText();
    
    //GIVE EACH ACTOR A CHANCE TO DO SOMETHING
    if (ptrToShip->isStillAlive())
        ptrToShip->doSomething();
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors[i]->isStillAlive() == true)
            m_actors[i]->doSomething();
    }
    
    //DELETE DEAD ACTORS
    for (int i = 0; i <m_actors.size(); i++)
    {
        if (m_actors[i]->isStillAlive() == false)
        {
            Alien* a = dynamic_cast<Alien*>(m_actors[i]);
            if (a != NULL)
            {
                m_nActiveAliens--;
                if (a->diedByCollision() == false)
                    m_AliensDestroyed++;
            }
            delete m_actors[i];
            m_actors.erase(m_actors.begin()+i);
            i--;
        }
    }
    
    if (m_AliensDestroyed >= (m_levelNumber * 4)+6)
    {
        m_levelNumber++;
        m_AliensDestroyed = 0;
        m_nActiveAliens = 0;
        
        for (int i = 0; i <m_actors.size(); i++)
        {
            
                delete m_actors[i];
                m_actors.erase(m_actors.begin()+i);
                i--;
            
        }
        
        
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (ptrToShip->isStillAlive() == false)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    else
        
        return GWSTATUS_CONTINUE_GAME;
    //decLives();
    //return GWSTATUS_PLAYER_DIED;// This code is here merely to allow the game to build, run, and terminate after hitting enter a few times
}

void StudentWorld::cleanUp()
{
    delete ptrToShip;//is this necessary?
    for (int i = 0; i < m_actors.size(); i++)
    {
        delete m_actors[i];
        m_actors.erase(m_actors.begin()+i);
    }
}

// Students:  Add code to this file (if you wish), StudentWorld.h, actor.h and actor.cpp


