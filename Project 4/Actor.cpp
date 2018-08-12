//
//  Actor.cpp
//  NachenBlaster
//
//  Created by Jonathan Goh on 2/22/18.
//  Copyright © 2018 David Smallberg. All rights reserved.
//

#include "Actor.h"

#include "StudentWorld.h"
//ACTOR IMPLEMENTATION
Actor::Actor(StudentWorld* ptr, int id, double x, double y, int dir, double s, int d)//does every actor need a pointer?
: GraphObject(id, x, y, dir, s, d), m_alive(true), m_StudentWorld(ptr)
{
    
}

Actor::~Actor()
{
    
}

void Actor::setAlive(bool m)
{
    m_alive = m;
}

bool Actor::isStillAlive()
{
    return m_alive;
}

void Actor::doSomething()
{
    
}

StudentWorld* Actor::getWorld()
{
    //m_StudentWorld = ptrToShip;
    return m_StudentWorld;
}

//SHIP IMPLEMENTATION
Ship::Ship(StudentWorld* ptr, int id, int x, int y, int startHealth)
:Actor(ptr, id, x, y,0,1,0), m_health(startHealth)
{
    
}

int Ship::getHealth() const
{
    return m_health;
}

double Ship::getHealthPct() const
{
    return m_health*2;
}

int Ship::getCabbage() const
{
    return m_cabbage;
}

int Ship::addCabbage()
{
    cabCount++;
    if(m_cabbage<30)
    {
       // int rand=randInt(1,5);
        
        //if(cabCount%5 == 0)
            m_cabbage+=1;
    }
    else
        m_cabbage=30;
    
    return m_cabbage;
}

int Ship::setCabbage(int i)
{
    m_cabbage=m_cabbage-i;
    
    if(m_cabbage<=0)
        m_cabbage=0;
    
    return m_cabbage;
}

double Ship::getCabbagePct() const
{
    double get;
    get = (m_cabbage)*3.34;
    int gets=get;
    return gets;
}

void Ship::decreaseHealth(int amount)
{
    m_health -= amount;
}

void Ship::restoreFullHealth()
{
    if(m_health<=40)
    {
        m_health = m_health+10;
    }
    else
    {
        m_health=50;
    }
}

bool Ship::fire(int type, int firedBy)//alien(2) player(1)
{
    if (type != 9 && type != 7 && type !=8)
        return false;
    if (firedBy != 1 && firedBy != 2)
        return false;
    if (firedBy == 1)
    {
        
        if(type == 9)
        {
            
            getWorld()->addActor(9, getX()+12, getY(), 1);
            getWorld()->playSound(SOUND_PLAYER_SHOOT);
        }
        
        if (type == IID_TORPEDO)
        {
            getWorld()->addActor(type, getX()+12, getY(), 1);
            getWorld()->playSound(SOUND_TORPEDO);
        }
        
        
        
        if(type == 8)
        {
            
            //m_actors.push_back(new Cabbage(this));
            getWorld()->addActor(type, getX()+12, getY(), 1);
            getWorld()->playSound(SOUND_PLAYER_SHOOT);
        }
    }
    
    if (firedBy == 2)
    {
        if (type == IID_TORPEDO)
        {
            getWorld()->addActor(type, getX()-12, getY(), 2);
            getWorld()->playSound(SOUND_TORPEDO);
            
        }
        else
        {
            getWorld()->addActor(type, getX()-12, getY(), 2);
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
        }
        
    }
    return true;
}



//PLAYER SHIP IMPLEMENTATION
NachenBlaster::NachenBlaster(StudentWorld* ptr)
: Ship(ptr, IID_NACHENBLASTER, 0, 128, 50), fired(false), m_torpedos(0)
{
    
}

NachenBlaster::~NachenBlaster()
{
    
}

int NachenBlaster::getNumTorpedos() const
{
    return m_torpedos;
}

void NachenBlaster::addTorpedos(int n)
{
    m_torpedos += n;
}

void NachenBlaster::damage(int amount, bool hitByProjectile)
{
    decreaseHealth(amount);
/////////
    if (getHealth() <= 0)
    {
        setAlive(false);
        getWorld()->playSound(SOUND_DEATH);
        getWorld()->addActor(IID_EXPLOSION, getX(), getY(), 1);
    }
    else
        getWorld()->playSound(SOUND_BLAST);
}

void NachenBlaster::checkForCollisionsWithAliens(NachenBlaster* p)
{
    list<Alien*> collidedWith = getWorld()->getCollidingAliens(p);
    int count = 0;
    for (list<Alien*>::iterator q = collidedWith.begin(); q != collidedWith.end(); q++)
    {
        (*q)->damage(0, false);
        count++;
        if (count == 1) //1/5 chance for blast sound
            damage(5, false);
        getWorld()->playSound(SOUND_BLAST);
        
        getWorld()->addActor(IID_EXPLOSION, getX(), getY(), 0);
    }
    
}

void NachenBlaster::doSomething()
{//check for collision with aliens before it moves and after it moves
    //have goodies check for collisoins with player
    //projectiles check for collisions with players and aliens
    if(getCabbage()<=30)
    {
        addCabbage();
    }
    
    checkForCollisionsWithAliens(this);
    if (getHealth() <= 0)
    {
        return;
        
    }
    int key;
    if (getWorld()->getKey(key))//WHY DOESNT IT WORK AS SMOOTHLY
    {
        //user hit a key this tick
        switch (key)
        {
            case KEY_PRESS_LEFT://move player to the left
                if (getX() > 0)
                    moveTo(getX()-6, getY());
                break;
            case KEY_PRESS_RIGHT://move player to the right
                if (getX() < VIEW_WIDTH-1)
                    moveTo(getX()+6, getY());
                break;
            case KEY_PRESS_UP://move player up
                if (getY()< VIEW_HEIGHT-1)
                    moveTo(getX(), getY()+6);
                break;
            case KEY_PRESS_DOWN://move player down
                if (getY() > 0)
                    moveTo(getX(), getY()-6);
                break;
            case KEY_PRESS_SPACE:
                if (fired)
                    fired = false;
                else
                {
                    if(getCabbage()>=5)
                    {
                        fire(9, 1);//fire and set fired to true
                        fired = true;
                        setCabbage(5);
                    }
                }
                break;
            case KEY_PRESS_TAB:
                if (m_torpedos > 0)
                {
                    if (fired)
                        fired = false;
                    else
                    {
                        if(getY() != VIEW_HEIGHT -1)
                        {
                            fire(IID_TORPEDO, 1);
                            fired = true;
                            m_torpedos--;
                        }
                    }
                }
                
                break;
        }
    }
    else
        fired = false;
    return;//for (int i = 0; i < m_actors.size(); i++)
}



//STAR IMPLEMENTATION
Star::Star(StudentWorld* ptr)//constructor
:Actor(ptr, IID_STAR, VIEW_WIDTH-1, randInt(0, 255), 0, (randInt(5,50))/100.00, 3)
{
    
}

Star::Star(StudentWorld* ptr, int x, int y)
:Actor(ptr, IID_STAR, x, y, 0, (randInt(5,50))/100.00, 3)
{
    
}

void Star::setX(int i)
{
    moveTo(randInt(0, VIEW_WIDTH-1),getY());
}

void Star::setY(int i)
{
    moveTo(getX(),randInt(0, VIEW_WIDTH-1));
}

void Star::doSomething()
{
    if (getX() >= 0)
        moveTo(getX()-1, getY());
    else
    {
        setAlive(false);
        //StudentWorld move() should delete it
    }
    return;
}

Star::~Star()
{
    
}


//Explosion IMPLEMENTATION
Explosion::Explosion(StudentWorld* ptr, int x, int y)//constructor
:Actor(ptr, IID_EXPLOSION, x, y, 0, 1, 0), expCount(4)
{
    
}



void Explosion::doSomething()
{
    expCount--;
    
    if(expCount==0)
    {
        setAlive(false);
        expCount=4;
    }
    
    setSize(pow(1.5,expCount));
    return;
}

Explosion::~Explosion()
{
    
}


//BULLET IMPLEMENTATION
Bullet::Bullet(StudentWorld* ptr, int bulletType, int x, int y, int firedBy, int damagePoints)
: Actor(ptr, bulletType, x, y, 20,.5,1), m_bulletType(bulletType) , m_damagePoints(damagePoints), m_firedBy(firedBy)//1 is NachenBlaster, 2 is alien
{
    
}

Bullet::~Bullet()
{
    
}

int Bullet::firedBy() const
{
    return m_firedBy;
}

void Bullet::checkForCollision(Bullet* b)
{
    if (m_firedBy == 1)
    {
        bool collided = false;
        list<Alien*> collidedWith = getWorld()->getCollidingAliens(b);
        for (list<Alien*>::iterator p = collidedWith.begin(); p != collidedWith.end(); p++)
        {
            (*p)->damage(m_damagePoints, true);
            collided = true;
        }
        if (collided == true)
        {
            setAlive(false);
        }
    }
    if (m_firedBy == 2)
    {
        NachenBlaster* collideWith = getWorld()->getCollidingPlayer(b);
        if (collideWith != NULL)
        {
            collideWith->damage(m_damagePoints, true);
            setAlive(false);
            
        }
    }
}

void Bullet::doSomething()
{
    checkForCollision(this);
    ////////////////////////
    if (m_firedBy == 1)
    {
        if(getX() <= VIEW_WIDTH-1)
            moveTo(getX()+8, getY());
        else
        {
            setAlive(false);
        }
    }
    
    if (m_firedBy == 2)
    {
        if(getX() >= 0)
            moveTo(getX()-6, getY());
        else
        {
            setAlive(false);
        }
    }
    ////////////////////////
    checkForCollision(this);
    return;
    //check for collision
}

//CABBAGE BULLET IMPLEMENTATION
CabbageBullet::CabbageBullet(StudentWorld* ptr, int x, int y, int firedBy)
: Bullet(ptr, 9, x, y, 1, 2)
{
    
}

CabbageBullet::~CabbageBullet()
{
    
}

//TURNIP BULLET IMPLEMENTATION
TurnipBullet::TurnipBullet(StudentWorld* ptr, int x, int y, int firedBy)
: Bullet(ptr, IID_TURNIP, x, y, firedBy, 2)
{
    
}

TurnipBullet::~TurnipBullet()
{
    
}

//FLATULENCE TORPEDO IMPLEMENTATION
FlatulenceTorpedo::FlatulenceTorpedo(StudentWorld* ptr, int x, int y, int firedBy)
: Bullet(ptr, IID_TORPEDO, x, y, firedBy, 8)
{
    
}

FlatulenceTorpedo::~FlatulenceTorpedo()
{
    
}

//ALIEN IMPLEMENTATION
Alien::Alien(StudentWorld* ptr, int id, int startHealth, int worth)
: Ship(ptr, id, VIEW_WIDTH-1, randInt(0,255), startHealth) , m_Worth(worth), m_diedByCollision(true)//, m_justHit(false)
{
    
}

int Alien::getWorth()
{
    return m_Worth;
}

Alien::~Alien()
{
    
}

bool Alien::diedByCollision()
{
    return m_diedByCollision;
}
/*
 void Alien::setJustHit(bool j)
 {
 m_justHit = j;
 }
 bool Alien::getJustHit()
 {
 return m_justHit;
 }*/

void Alien::damage(int points, bool hitByProjectile)
{
    if (hitByProjectile == true)
    {
        decreaseHealth(points);
        getWorld()->playSound(SOUND_BLAST);
    }
    
    else
        decreaseHealth(getHealth());
    
    if (getHealth() <= 0)
    {
        if (hitByProjectile == true)
        {
            getWorld()->increaseScore(m_Worth);
            m_diedByCollision = false;
        }
        setAlive(false);
        getWorld()->playSound(SOUND_DEATH);
        getWorld()->addActor(IID_EXPLOSION, getX(), getY(), 0);
        //////
        if (m_diedByCollision == false)
        {
            //////////////////////////////////////////////////////////////////////////////////
            Snagglegon* s = dynamic_cast<Snagglegon*>(this);
            if (s != NULL)
            {
                s->maybeDropGoodie();
                getWorld()->playSound(SOUND_DEATH);
            }
            Smoregon* w = dynamic_cast<Smoregon*>(this);
            if (w != NULL)
            {
                w->maybeDropGoodie();
                getWorld()->playSound(SOUND_DEATH);
            }
        }
    }
    
    else
    {
        getWorld()->playSound(SOUND_BLAST);
    }
    return;
}

void Alien::maybeDropGoodie()
{
    return;
}

//ALIEN BASE IMPLEMENTATION
AlienBase::AlienBase(StudentWorld* ptr, int id, int level, int worth)
: Alien(ptr, id, level , worth), m_state(0), m_canAct(true), flightPlan(0), dirX(-2), dirY(0)
{
    
}

AlienBase::~AlienBase()
{
    
}

void AlienBase::setCanAct(bool m)
{
    m_canAct = m;
}

void AlienBase::setdirY(int i)
{
    dirY=i;
}

void AlienBase::setdirX(int i)
{
    dirX=i;
}

void AlienBase::doSomething()
{
    
    if (m_canAct == false)
    {
        m_canAct = true;
        return;
    }
    
    if (m_canAct != false)
    {
        m_canAct = ! m_canAct;
        if (m_state == 0)
        {
            flightPlan--;
            moveTo(getX()-2,getY()+dirY);

            if(getY()>=VIEW_HEIGHT-1)
            {
                dirY=2*(-1);
            }
            if(getY()<=0)
            {
                dirY=2*1;
            }
            if(flightPlan<=0)
            {
                if(flightPlan<=0)
                {
                    dirY=(randInt(-1,1))*2;
                    
                }
            }
            if(flightPlan<=0)
                flightPlan=randInt(1,32);
            
            m_state=1;
            
            if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
            {
                return;
            }
            else
            {
                setAlive(false);
            }
            return;
        }
        
        if (m_state == 1)
        {
            
            
            flightPlan--;
            if(getY()>=VIEW_HEIGHT-1)
            {
                dirY=2*(-1);
            }
            if(getY()<=0)
            {
                dirY=2*1;
            }
            if(flightPlan<=0)
            {
                
                if(flightPlan<=0)
                {
                    dirY=(randInt(-1,1))*2;
                    
                }
            }
            if(flightPlan<=0)
                flightPlan=randInt(1,32);
            
            moveTo(getX()-2, getY()+dirY);
            
            
        
            int chancesOfFiring = randInt(1,(20/getWorld()->getlevelNumber())+5);
            
            if (chancesOfFiring == 1)
            {
                //int numAlienBullets = getWorld()->getNumAlienFiredProjectiles(); //projectiles
                if ( getY() == getWorld()->getNachenBlaster()->getY() || getY()+1 == getWorld()->getNachenBlaster()->getY() || getY()+2 == getWorld()->getNachenBlaster()->getY() || getY()+3 == getWorld()->getNachenBlaster()->getY()|| getY()+4 == getWorld()->getNachenBlaster()->getY() || getY()-1 == getWorld()->getNachenBlaster()->getY()|| getY()-2 == getWorld()->getNachenBlaster()->getY()|| getY()-3 == getWorld()->getNachenBlaster()->getY()|| getY()-4 == getWorld()->getNachenBlaster()->getY())
                {
                    getWorld()->addActor(IID_TURNIP, getX()-1, getY(), 2);
                    getWorld()->playSound(SOUND_ALIEN_SHOOT);
                }
            }
            
            
            if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
            {
                return;
            }
            else
            {
                setAlive(false);
            }
            return;
            
            
        }
    }
    m_state=0;
}

//SMALLGON IMPLEMENTATION
Smallgon::Smallgon(StudentWorld* ptr, int level)
: AlienBase(ptr, IID_Smallgon, 5*(1+(level-1)*.1), 250)
{
    setSize(1.5);
}

Smallgon::~Smallgon()
{
    
}

void Smallgon::doSomething()
{
    AlienBase::doSomething();
}

void Smallgon::maybeDropGoodie()
{
    return;
}

//SMOREGON IMPLEMENTATION
Smoregon::Smoregon(StudentWorld* ptr, int level)
: AlienBase(ptr, IID_SMOREGON, 5*(1+(level-1)*.1), 250), rogue(false)
{
    setSize(1.5);
}

Smoregon::~Smoregon()
{
    
}

void Smoregon::doSomething()
{
    int chancesOfRogue = randInt(1,(20/getWorld()->getlevelNumber())+5);
    
    
    int chancesOfFiring = randInt(1,(20/getWorld()->getlevelNumber())+5);
    
    if (chancesOfFiring == 1)
    {
        //int numAlienBullets = getWorld()->getNumAlienFiredProjectiles(); //projectiles
        if ( getY() == getWorld()->getNachenBlaster()->getY() || getY()+1 == getWorld()->getNachenBlaster()->getY() || getY()+2 == getWorld()->getNachenBlaster()->getY() || getY()+3 == getWorld()->getNachenBlaster()->getY()|| getY()+4 == getWorld()->getNachenBlaster()->getY() || getY()-1 == getWorld()->getNachenBlaster()->getY()|| getY()-2 == getWorld()->getNachenBlaster()->getY()|| getY()-3 == getWorld()->getNachenBlaster()->getY()|| getY()-4 == getWorld()->getNachenBlaster()->getY())
        {
            getWorld()->addActor(IID_TURNIP, getX()-1, getY(), 2);
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
        }
    }

    if (rogue==true)
    {
        moveTo(getX()-5, getY());
        if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
        {
            return;
        }
        else
        {
            setAlive(false);
        }
    }
    else if(chancesOfRogue==1)
    {
        if (getY() == getWorld()->getNachenBlaster()->getY() || getY()+1 == getWorld()->getNachenBlaster()->getY() || getY()+2 == getWorld()->getNachenBlaster()->getY() || getY()+3 == getWorld()->getNachenBlaster()->getY()|| getY()+4 == getWorld()->getNachenBlaster()->getY() || getY()-1 == getWorld()->getNachenBlaster()->getY()|| getY()-2 == getWorld()->getNachenBlaster()->getY()|| getY()-3 == getWorld()->getNachenBlaster()->getY()|| getY()-4 == getWorld()->getNachenBlaster()->getY())
        {
            moveTo(getX()-5, getY());
            rogue=true;
            if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
            {
                return;
            }
            else
            {
                setAlive(false);
            }
        }
        
    }
    else
    {
        AlienBase::doSomething();
        setCanAct(true);
        rogue=false;
        if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
        {
            return;
        }
        else
        {
            setAlive(false);
        }
    }
    
}

void Smoregon::maybeDropGoodie()
{
    int p = rand() % 100;
    if (p < 33)
    {
        int p2 = rand() % 100;
        if (p2 <50)
            getWorld()->addActor(IID_REPAIR_GOODIE, getX(), getY(), 0);
        else
            getWorld()->addActor(IID_TORPEDO_GOODIE, getX(), getY(), 0);
    }
    return;
}

//SNAGGLEGON IMPLEMENTATION
Snagglegon::Snagglegon(StudentWorld* ptr, int level)
: Alien(ptr, IID_SNAGGLEGON, 12 * ((level * .1 + .9)), 1000), m_canAct(true), m_justHit(false),dirYY(1.75)
{
    setSize(1.5);
}

Snagglegon::~Snagglegon()
{
    
}

void Snagglegon::setJustHit(bool j)
{
    m_justHit = j;
}

void Snagglegon::maybeDropGoodie()
{
    int p = rand() % 100;
    if (p <(100/6))
        getWorld()->addActor(IID_LIFE_GOODIE, getX(), getY(), 0);
    return;
}

void Snagglegon::damage(int points, bool hitByProjectile)
{
    Alien::damage(points, hitByProjectile);
    if (hitByProjectile == true)
        m_justHit = true;
}

void Snagglegon::doSomething()
{
    if (m_canAct == false)
    {
        m_canAct = true;
        return;
    }
    
    if (m_canAct != false)
    {
        m_canAct = ! m_canAct;
        if (m_state == 0)
        {
            
            moveTo(getX()-1.75,getY()+dirYY);
            
            if(getY()>=VIEW_HEIGHT-1)
            {
                dirYY=1.75*(-1);
            }
            if(getY()<=0)
            {
                dirYY=1.75*1;
            }
           
            
            m_state=1;
            
            if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
            {
                return;
            }
            else
            {
                setAlive(false);
            }
            return;
        }
        
        if (m_state == 1)
        {
            
            
            flightPlan--;
            if(getY()>=VIEW_HEIGHT-1)
            {
                dirYY=1.75*(-1);
            }
            if(getY()<=0)
            {
                dirYY=1.75*1;
            }
            
            
            moveTo(getX()-1.75, getY()+dirYY);
            
            
            int chancesOfFiring = randInt(1,(15/getWorld()->getlevelNumber())+10);
            
            if (chancesOfFiring == 1)
            {
                //int numAlienBullets = getWorld()->getNumAlienFiredProjectiles(); //projectiles
                if ( getY() == getWorld()->getNachenBlaster()->getY() || getY()+1 == getWorld()->getNachenBlaster()->getY() || getY()+2 == getWorld()->getNachenBlaster()->getY() || getY()+3 == getWorld()->getNachenBlaster()->getY()|| getY()+4 == getWorld()->getNachenBlaster()->getY() || getY()-1 == getWorld()->getNachenBlaster()->getY()|| getY()-2 == getWorld()->getNachenBlaster()->getY()|| getY()-3 == getWorld()->getNachenBlaster()->getY()|| getY()-4 == getWorld()->getNachenBlaster()->getY())
                {
                    getWorld()->addActor(IID_TORPEDO, getX()-1, getY(), 2);
                    getWorld()->playSound(SOUND_TORPEDO);
                }
            }
            
            
            if (getX() > 0)        //IMPORTANT SET DEAD IF OFF SCREEN
            {
                return;
            }
            else
            {
                setAlive(false);
            }
            return;
            
            
        }
    }
    m_state=0;
}

//GOODIE IMPLEMENTATION
Goodie::Goodie(StudentWorld* ptr, int id,  double x, double y)
: Actor(ptr, id, x, y,0,.5,1), m_ticksLeftToLive(double(100/getWorld()->getlevelNumber() +30)), m_goodieTickLifeTime(100/getWorld()->getlevelNumber() +30), m_actEvery3Ticks(0)
{
    
}

Goodie::~Goodie()
{
    
}

void Goodie::doSomething()
{
    NachenBlaster* collidedWith = getWorld()->getCollidingPlayer(this);
    if (collidedWith != NULL)
        doSpecialAction(collidedWith);
    else
    {
        //setBrightness((double(m_ticksLeftToLive)/m_goodieTickLifeTime) + .2);
        if (getX() <= 0|| getY()<=0|| getY()>=VIEW_HEIGHT)
        {
            //setVisible(false);
            setAlive(false);
            return;
        }
     
            if (getX() >=0)
                moveTo(getX()-.75, getY()-.75);
            else
            {
                setAlive(false);
                return;
            }
    }
    collidedWith = getWorld()->getCollidingPlayer(this);
    if (collidedWith != NULL)
        doSpecialAction(collidedWith);
}

//REPAIR GOODIE IMPLEMENTATION
RepairGoodie::RepairGoodie(StudentWorld* ptr, int x, int y)
: Goodie(ptr, IID_REPAIR_GOODIE, x, y)
{
    
}

RepairGoodie::~RepairGoodie()
{
    
}

void RepairGoodie::doSpecialAction(NachenBlaster* p)
{
    p->getWorld()->playSound(SOUND_GOODIE);
    p->getWorld()->increaseScore(100);
    p->restoreFullHealth();
    //setVisible(false);
    setAlive(false);
}

//TORPEDO GOODIE IMPLEMENTATION
TorpedoGoodie::TorpedoGoodie(StudentWorld* ptr, int x, int y)
: Goodie(ptr, IID_TORPEDO_GOODIE, x, y)
{
    
}

TorpedoGoodie::~TorpedoGoodie()
{
    
}

void TorpedoGoodie::doSpecialAction(NachenBlaster* p)
{
    p->getWorld()->playSound(SOUND_GOODIE);
    p->getWorld()->increaseScore(100);
    p->addTorpedos(5);
    setAlive(false);
}

//LIFE GOODIE IMPLEMENTATION
LifeGoodie::LifeGoodie(StudentWorld* ptr, int x, int y)
: Goodie(ptr, IID_LIFE_GOODIE, x, y)
{
    
}

LifeGoodie::~LifeGoodie()
{
    
}

void LifeGoodie::doSpecialAction(NachenBlaster* p)
{
    p->getWorld()->increaseScore(100);
    p->getWorld()->playSound(SOUND_GOODIE);
    p->getWorld()->incLives();
    //setVisible(false);
    setAlive(false);
}

// Students:  Add code to this file (if you wish), actor.h, StudentWorld.h, and StudentWorld.cpp
