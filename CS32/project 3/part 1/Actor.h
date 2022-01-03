#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor;
class Dirt;
class Flame;
class Spray;
class Actor:public GraphObject{
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething() = 0;
    bool isAlive() const;
    void dead();
    StudentWorld* getAPointerToMyStudentWorld() const;
private:
    bool m_alive;
    StudentWorld* m_world;
};

class Dirt:public Actor{
public:
    Dirt(double startX, double startY, StudentWorld* world);
    virtual ~Dirt();
    virtual void doSomething();
private:
};

class Socrates:public Actor{
public:
    Socrates(double startX, double startY, StudentWorld* world);
    virtual ~Socrates();
    virtual void doSomething();
private:
    int m_posAngle;
};
//
//class Food:public Actor{
//public:
//    Food(double startX, double startY, StudentWorld* world):Actor(IID_FOOD, startX, startY, 90, 1, 1.0, world){
//    }
//    virtual ~Food();
//    virtual void doSomething(){}
//    };
//
//class Projectile: public Actor{
//public:
//    Projectile(int stack, int maxDist, int imageId, double startX, double startY, Direction dir, StudentWorld* world):Actor(imageId, startX, startY, dir, 1, 1.0, world){
//        m_stack = stack;
//        m_maxDist = maxDist;
//        m_maxStack = stack;
//        m_travel = 0;
//    }
//    virtual ~Projectile();
//    void changeStack(int num){
//        m_stack +=num;
//    }
//    int currentStack() const{
//        return m_stack;
//    }
//    int maxStack()const{
//        return m_maxStack;
//    }
//    int maxDist() const{
//        return m_maxDist;
//    }
//    int distTraveled() const {
//        return m_travel;
//    }
//    void traveled(int dist){
//        m_travel+=dist;
//    }
//private:
//    int m_stack;
//    int m_maxDist;
//    int m_maxStack;
//    int m_travel;
//};
//
//class Flame:public Projectile{
//public:
//    Flame(double startX, double startY, Direction dir, StudentWorld* world):Projectile(5, 32, IID_FLAME, startX, startY, dir, world){
//    }
//    virtual ~Flame();
//    virtual void doSomething();
//};
//
//class Spray:public Projectile{
//public:
//    Spray(double startX, double startY, Direction dir, StudentWorld* world):Projectile(20, 112, IID_SPRAY, startX, startY, dir, world){
//    }
//};
//
//class Goodies:public Actor{
//public:
//    Goodies(int imageId, double startX, double startY, StudentWorld* world):Actor(imageId, startX, startY, 0, 1, 1.0, world){
//        m_life = 0;
//    }
//    virtual void setLife()=0;
//    void loseLife(){
//        m_life--;
//    }
//    int getLife() const{
//        return m_life;
//    }
//private:
//    int m_life;
//};
//
//class Heal:public Goodies{
//public:
//    Heal(double startX, double startY,StudentWorld* world):Goodies(IID_RESTORE_HEALTH_GOODIE, startX, startY, world){
//    }
//    virtual void setLife(){
//
//    }
//};
#endif // ACTOR_H_
