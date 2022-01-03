#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
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
    double distance(const int x, const int x2, const int y1, const int y2);
    Socrates* collideWithPlayer(const Actor* a);
    Actor* collide(const Actor* a);
    bool thereIsDirt(const int x, const int y);
    Actor* closestFood(const Actor *a);
    Actor* collideWithFood(const Actor* a);
    Socrates* foundHim(const Actor* a, int pixel);
    string updateDisplayText();
    bool finishedLevel();
    bool randomPositions(int x, int y);
private:
    vector<Actor*> m_actors;
    Socrates* m_player;
};
int randomCoord();
#endif // STUDENTWORLD_H_
