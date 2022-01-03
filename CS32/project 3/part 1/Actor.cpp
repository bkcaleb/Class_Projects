#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* world):GraphObject(imageID, startX, startY, dir, depth, size){
    m_alive = true;
    m_world = world;
}
Actor::~Actor(){
}
bool Actor::isAlive() const{
    return m_alive;
}
void Actor::dead(){
    m_alive = false;
}
StudentWorld* Actor::getAPointerToMyStudentWorld() const{
    return m_world;
}

Dirt::Dirt(double startX, double startY, StudentWorld* world):Actor(IID_DIRT, startX, startY, 0, 1, 1.0, world){
}
Dirt::~Dirt(){
}

void Dirt::doSomething(){
}


Socrates::Socrates(double startX, double startY, StudentWorld* world):Actor(IID_PLAYER, startX, startY, 0, 0, 1.0, world){
    m_posAngle = 180;
}
Socrates::~Socrates(){
}
void Socrates::doSomething(){
    int ch;
    int x;
    int y;
    if (getAPointerToMyStudentWorld()->getKey(ch))
    {
    // user hit a key during this tick!
    switch (ch)
    {
        case KEY_PRESS_LEFT://counter clockwise
            m_posAngle+=5;
            x = VIEW_RADIUS*(1+cos(m_posAngle/180.0*M_PI));
            y = VIEW_RADIUS*(1+sin(m_posAngle/180.0*M_PI));
            moveTo(x,y);
            setDirection((m_posAngle+180)%360);
            break;
        case KEY_PRESS_RIGHT: //clockwise
            m_posAngle-=5;
            x = VIEW_RADIUS*(1+cos(m_posAngle/180.0*M_PI));
            y = VIEW_RADIUS*(1+sin(m_posAngle/180.0*M_PI));
            moveTo(x,y);
            setDirection((m_posAngle+180)%360);
            break;
//        case KEY_PRESS_ENTER:
//            Flame* flame = new Flame(getX(), getY(), getDirection(), getAPointerToMyStudentWorld());
//            getAPointerToMyStudentWorld()->addActor(flame);
//            break;

//    case KEY_PRESS_SPACE:
//   // ... add spray in front of Socrates...;
//    break;
//    // etc…
    }
    }
}
//
//void Flame::doSomething(){
//    if(!isAlive()||currentStack() == 0){
//        return;
//    }
//    //check if it hits damagable object
//
//    //if not then move
//    for(int i = 0; i < SPRITE_WIDTH; i++){
//        if(distTraveled() >= 32){
//            dead();
//            changeStack(-1);
//            return;
//        }
//        moveForward();
//        traveled(1);
//    }
//}
