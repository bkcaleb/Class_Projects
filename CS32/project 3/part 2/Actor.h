#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor:public GraphObject{
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world):GraphObject(imageID, startX, startY, dir, depth, size){
        m_alive = true;
        m_world = world;
    }
    virtual ~Actor(){
    }
    virtual void doSomething() = 0;
    bool isAlive() const{
        return m_alive;
    }
    void dead(){
        m_alive = false;
    }
    StudentWorld* getAPointerToMyStudentWorld() const{
        return m_world;
    }
    virtual bool damagable() const{
        return false;
    }
    virtual bool hasHealth() const{
        return false;
    }
    virtual bool isDirt() const{
        return false;
    }
    virtual bool isFood() const{
        return false;
    }
    virtual int getHealth() const{
        return -1;
    }
    virtual void changeHealth(int num){}
    virtual bool badguys() const{
        return false;
    }
    virtual void OuchBacteria(){}
private:
    bool m_alive;
    StudentWorld* m_world;
};

class Dirt:public Actor{
public:
    Dirt(double startX, double startY, StudentWorld* world):Actor(IID_DIRT, startX, startY, 0, 1, 1.0, world){}
    virtual ~Dirt(){}
    virtual bool damagable() const{
        return true;
    }
    virtual void doSomething(){
    }
    virtual bool isDirt() const{
        return true;
    }
};

class Food:public Actor{
public:
    Food(double startX, double startY, StudentWorld* world):Actor(IID_FOOD, startX, startY, 90, 1, 1.0, world){
    }
    virtual ~Food(){
    }
    virtual bool isFood() const{
        return true;
    }
    virtual void doSomething(){}
};

class Projectile: public Actor{
public:
    Projectile(int maxDist, int dmg, int imageId, double startX, double startY, Direction dir, StudentWorld* world):Actor(imageId, startX, startY, dir, 1, 1.0, world){
        m_maxDist = maxDist;
        m_travel = 0;
        m_dmg = dmg;
    }
    virtual ~Projectile(){}
    int maxDist() const{
        return m_maxDist;
    }
    int distTraveled() const {
        return m_travel;
    }
    void traveled(int dist){
        m_travel+=dist;
    }
    virtual void doSomething();
private:
    int m_maxDist;
    int m_travel;
    int m_dmg;
};

class Flame:public Projectile{
public:
    Flame(double startX, double startY, Direction dir, StudentWorld* world):Projectile(32, 5, IID_FLAME, startX, startY, dir, world){}
    virtual~Flame(){}
};

class Spray:public Projectile{
public:
    Spray(double startX, double startY, Direction dir, StudentWorld* world):Projectile(112, 2, IID_SPRAY, startX, startY, dir, world){}
    virtual ~Spray(){}
};

class Pit:public Actor{
public:
    Pit(double startX, double startY, StudentWorld* world):Actor(IID_PIT, startX, startY, 0, 1, 1.0, world){
        m_countE = 2;
        m_countReg = 5;
        m_countAggr = 3;
    }
    virtual void doSomething();
    virtual bool badguys() const{
        return true;
    }
private:
    int m_countReg;
    int m_countAggr;
    int m_countE;
};

class Agent:public Actor{
public:
    Agent(int imageID, int health, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world):Actor(imageID, startX, startY, dir, depth, size, world){
        m_health = health;
    }
    virtual bool damagable() const{
        return true;
    }
    virtual bool hasHealth() const{
        return true;
    }
    virtual int getHealth() const{
        return m_health;
    }
    virtual void changeHealth(int num){
        m_health+=num;
    }
    virtual void doSomething();
    virtual void doSomething2()=0;
private:
    int m_health;
};

class Socrates:public Agent{
public:
    Socrates(double startX, double startY, StudentWorld* world):Agent(IID_PLAYER, 100, startX, startY, 0, 0, 1.0, world){
        m_posAngle = 180;
        m_sprayStk = 20;
        m_flameStk = 5;
    }
    virtual ~Socrates(){
    }
    virtual void doSomething2();
    void changeFlameStk(int num){
        m_flameStk+=num;
    }
    int getSpraystk() const{
        return m_sprayStk;
    }
    int getFlamestk() const{
        return m_flameStk;
    }
    void moving();
private:
    int m_posAngle;
    int m_sprayStk;
    int m_flameStk;
};

class Bacterium:public Agent{
public:
    Bacterium(int imageID, int health, int dmg, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world):Agent(imageID, health, startX, startY, dir, depth, size, world){
        m_movePlanDist = 0;
        m_foodCount = 0;
        m_dmg = dmg;
    }
    int getPlanDist() const{
        return m_movePlanDist;
    }
    void setPlanDist(int num){
        m_movePlanDist=num;
    }
    virtual bool badguys() const{
        return true;
    }
    bool followHim(int pixel);
    bool blocked();
    void randomDir();
    virtual void deathBehavior();
    virtual void doSomething2();
    virtual void OnlySalmonella() = 0;
    virtual void OnlyEcoli()= 0;
    virtual bool skip()const{
        return false;
    }
    virtual void deathSound() = 0;
    virtual void diffAdding(double newX, double newY) =0;
    virtual void OnlyAggrSal(){}
private:
    int m_movePlanDist;
    int m_foodCount;
    int m_dmg;
};

class Salmonella:public Bacterium{
public:
    Salmonella(double startX, double startY, int health, int dmg, StudentWorld* world):Bacterium(IID_SALMONELLA, health, dmg, startX, startY, 90, 0, 1.0, world){
        m_dmg = dmg;
    }
    virtual void OnlySalmonella();
    virtual void deathSound();
    virtual void OuchBacteria();
    virtual void OnlyEcoli(){}
private:
    int m_dmg;
};

class RegSalmonella:public Salmonella{
public:
    RegSalmonella(double startX, double startY, StudentWorld* world):Salmonella(startX, startY, 4, 1, world){}
    virtual void diffAdding(double newX, double newY);
};

class AggrSalmonella:public Salmonella{
public:
    AggrSalmonella(double startX, double startY, StudentWorld* world):Salmonella(startX, startY, 10, 2, world){
        m_skip = false;
    }
    virtual bool skip()const{
        return m_skip;
    }
    virtual void OnlyAggrSal();
    virtual void diffAdding(double newX, double newY);
private:
    bool m_skip;
};

class Ecoli:public Bacterium{
public:
    Ecoli(double startX, double startY, StudentWorld* world):Bacterium(IID_ECOLI, 5, 4, startX, startY, 90, 0 ,1.0, world){}
    virtual void OnlyEcoli();
    virtual void diffAdding(double newX, double newY);
    virtual void deathSound();
    virtual void OuchBacteria();
    virtual void OnlySalmonella(){}
};

class Goodie:public Actor{
public:
    Goodie(int imageID, int lifetime, int score, double startX, double startY, StudentWorld* world):Actor(imageID, startX, startY, 0, 1, 1.0, world){
        m_maxLife = lifetime;
        m_lifetime = 0;
        m_score = score;
    }
    virtual void doSomething();
    virtual void doSomethingGoodie(Socrates* player) = 0;
    virtual bool damagable() const{
        return true;
    }
private:
    int m_lifetime;
    int m_maxLife;
    int m_score;
};

class Restore:public Goodie{
public:
    Restore(double startX, double startY, int lifetime, StudentWorld* world):Goodie(IID_RESTORE_HEALTH_GOODIE, lifetime, 250, startX, startY, world){}
    virtual void doSomethingGoodie(Socrates*player);
private:
    
};

class FlameGoods:public Goodie{
public:
    FlameGoods(double startX, double startY, int lifetime, StudentWorld* world):Goodie(IID_FLAME_THROWER_GOODIE, lifetime, 300, startX, startY, world){}
    virtual void doSomethingGoodie(Socrates*player);
};

class ExtraLife:public Goodie{
public:
    ExtraLife(double startX, double startY, int lifetime, StudentWorld* world):Goodie(IID_EXTRA_LIFE_GOODIE, lifetime, 500, startX, startY, world){}
    virtual void doSomethingGoodie(Socrates*player);
};

class Fungus:public Goodie{
public:
    Fungus(double startX, double startY, int lifetime, StudentWorld* world):Goodie(IID_FUNGUS, lifetime, -50, startX, startY, world){}
    virtual void doSomethingGoodie(Socrates*player);
};
#endif // ACTOR_H_
