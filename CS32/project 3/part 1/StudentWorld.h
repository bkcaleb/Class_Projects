#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool checkSameCoord(int x, int y);
    void addActor(Actor* add);
    void removeDeadGameObjects();
    bool inRangeOfCircle(const int x,const int y);
private:
    vector<Actor*> m_actors;
    Socrates* m_player;
};
int randomCoord();
#endif // STUDENTWORLD_H_
