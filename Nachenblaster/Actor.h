//
//  Actor.h
//  NachenBlaster
//
//  Created by Jonathan Goh on 2/22/18.
//  Copyright © 2018 David Smallberg. All rights reserved.
//

#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
public:
    Actor(StudentWorld* ptr, int id, double x, double y, int dir, double s, int d);
    virtual ~Actor();
    virtual void doSomething() = 0;
    bool isStillAlive();
    StudentWorld* getWorld();
    void setAlive(bool m);
    
private:
    bool m_alive;
    StudentWorld* m_StudentWorld;//pg23 hint at bottom
};


class Ship : public Actor
{
public:
    Ship(StudentWorld* ptr, int id, int x, int y, int startHealth);
    int getHealth() const;
    double getHealthPct() const;
    int getCabbage() const;
    int addCabbage();
    int setCabbage(int i);
    double getCabbagePct() const;
    void decreaseHealth(int amount);
    void restoreFullHealth();
    bool fire(int type, int firedBy);
    
private:
    int m_health;
    int m_cabbage;
    int cabCount;
    
};


class NachenBlaster : public Ship   //public Actor
{
public:
    NachenBlaster(StudentWorld* ptr);
    virtual ~NachenBlaster();
    virtual void doSomething();
    int getNumTorpedos() const;
    void addTorpedos(int n);
    void damage(int amount, bool hitByProjectile);//(int amount, bool hitByProjectile)
    void checkForCollisionsWithAliens(NachenBlaster* p);
    //virtual void fire();
private:
    int m_torpedos;
    bool fired;
};


class Alien : public Ship
{
public:
    Alien(StudentWorld* ptr, int id, int startHealth, int worth);
    virtual ~Alien();
    virtual void damage(int points, bool hitByProjectile);
    bool diedByCollision();
    virtual void maybeDropGoodie() = 0;
    virtual void doSomething() = 0;
    int getWorth();
    
private:
    int m_Worth;
    bool m_diedByCollision;
};


class AlienBase : public Alien
{
public:
    AlienBase(StudentWorld* ptr, int id, int level, int worth);
    virtual ~AlienBase();
    virtual void doSomething();
    void setCanAct(bool m);
    void setdirY(int i);
    void setdirX(int i);
    
private:
    int m_state;
    bool m_canAct;
    int flightPlan;
    int dirX;
    int dirY;
};


class Smallgon : public AlienBase
{
public:
    Smallgon(StudentWorld* ptr, int level);
    virtual ~Smallgon();
    virtual void maybeDropGoodie();
    virtual void doSomething();
    
private:
};


class Smoregon : public AlienBase
{
public:
    Smoregon(StudentWorld* ptr, int level);
    virtual ~Smoregon();
    virtual void doSomething();
    virtual void maybeDropGoodie();
    
private:
    bool rogue;
    int m_malfunctionTime;
};


class Snagglegon : public Alien
{
public:
    Snagglegon(StudentWorld* world, int level);
    virtual ~Snagglegon();
    virtual void damage(int points, bool hitByProjectile);
    void setJustHit(bool j);
    virtual void maybeDropGoodie();
    virtual void doSomething();
    
private:
    int m_state;
    bool m_canAct;
    bool m_justHit;
    int flightPlan;
    int dirXX;
    int dirYY;
};


class Bullet : public Actor
{
public:
    Bullet(StudentWorld* ptr, int bulletType, int x, int y, int firedBy, int damagePoints);
    virtual ~Bullet();
    void doSomething();
    int firedBy() const;
    void checkForCollision(Bullet* b);
    
private:
    int m_firedBy; //1 is NachenBlaster 2 is alien
    int m_damagePoints;
    int m_bulletType;//to be used in doSomething to determine damage
};


class TurnipBullet :public Bullet
{
public:
    TurnipBullet(StudentWorld* ptr, int x, int y, int firedBy);
    virtual ~TurnipBullet();
    
private:
};


class CabbageBullet :public Bullet
{
public://////////////////////////////////
    /////////////////////////////////////
    CabbageBullet(StudentWorld* ptr, int x, int y, int firedBy);
    virtual ~CabbageBullet();
    
private:
};


class FlatulenceTorpedo :public Bullet
{
public:
    FlatulenceTorpedo(StudentWorld* ptr, int x ,int y, int firedBy);
    virtual ~FlatulenceTorpedo();
    
private:
};


class Goodie : public Actor
{
public:
    Goodie(StudentWorld* ptr, int id, double x, double y);
    virtual ~Goodie();
    virtual void doSomething();
    virtual void doSpecialAction(NachenBlaster* p) = 0;
    
private:
    int m_goodieTickLifeTime;
    int m_ticksLeftToLive;
    int m_actEvery3Ticks;
};


class TorpedoGoodie : public Goodie
{
public:
    TorpedoGoodie(StudentWorld* ptr, int x, int y);
    virtual ~TorpedoGoodie();
    virtual void doSpecialAction(NachenBlaster* p);
    
private:
};


class RepairGoodie : public Goodie
{
public:
    RepairGoodie(StudentWorld* ptr, int x, int y);
    virtual ~RepairGoodie();
    virtual void doSpecialAction(NachenBlaster* p);
    
private:
};


class LifeGoodie : public Goodie
{
public:
    LifeGoodie(StudentWorld* ptr, int x, int y);
    virtual ~LifeGoodie();
    virtual void doSpecialAction(NachenBlaster* p);
    
private:
};


class Star : public Actor
{
public:
    Star(StudentWorld* ptr);
    Star(StudentWorld* ptr, int x, int y);
    virtual ~Star();
    virtual void doSomething();
    void setX(int i);
    void setY(int i);
    
private:
};

class Explosion : public Actor
{
public:
    Explosion(StudentWorld* ptr, int x, int y);
    virtual ~Explosion();
    virtual void doSomething();
    
private:
    int expCount;
};

#endif // _ACTOR_H_
