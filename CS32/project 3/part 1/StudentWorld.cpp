#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

bool StudentWorld::inRangeOfCircle(const int x, const int y){
    return (x-VIEW_WIDTH/2)*(x-VIEW_WIDTH/2) + (y-VIEW_HEIGHT/2)*(y-VIEW_HEIGHT/2) < VIEW_RADIUS*VIEW_RADIUS;
}

int randomCoord(){
    return randInt(VIEW_WIDTH/2 - VIEW_RADIUS, VIEW_WIDTH/2 + VIEW_RADIUS);
}

bool StudentWorld::checkSameCoord(int x, int y){
    for(int i = 0; i < m_actors.size(); i++){
        //find distance from the center of the objs using distance formula
        if(sqrt((x - m_actors[i]->getX())*(x - m_actors[i]->getX()) + (y- m_actors[i]->getY())*(y- m_actors[i]->getY())) < SPRITE_WIDTH){
            return true;
        }
    }
    return false;
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_player =  nullptr;
}
StudentWorld::~StudentWorld(){
    cleanUp();
}
int StudentWorld::init()
{
    //add player
    m_player = new Socrates(0, VIEW_RADIUS, this);
    
    
    //add random amount of dirt
    int maxDirt = max(20, 180-20*getLevel());
    for(int i = 0; i < maxDirt; i++){
        while(1){
        int randPosX = randomCoord();
        int randPosY = randomCoord();
            if(inRangeOfCircle(randPosX, randPosY)){
                m_actors.push_back(new Dirt(randPosX,randPosY, this));
                break;
            }
        }
    }

//
//    //adding food
//    int minFood = min(5*getLevel(), 25);
//    for(int i = 0; i < minFood; i++){
//        while(1){
//            int randPosX = randomCoord();
//            int randPosY = randomCoord();
//            if(inRangeOfCircle(randPosX, randPosY)){
//                if(!checkSameCoord(randPosX, randPosY)){
//                    m_actors.push_back(new Food(randPosX, randPosY, this));
//                    break;
//                }
//            }
//        }
//    }
//
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // The term "actors" refers to all bacteria, Socrates, goodies,
    // pits, flames, spray, foods, etc.
    // Give each actor a chance to do something, incl. Socrates
    for(int i = 0; i < m_actors.size(); i++){
        if(m_player->isAlive()){
            m_player->doSomething();
        }else{
            return GWSTATUS_PLAYER_DIED;
        }
        
        if(m_actors[i]->isAlive()){
            m_actors[i]->doSomething();
        }
    }
    return GWSTATUS_CONTINUE_GAME;
//    for each of the actors in the game world
//    {
//     if (actor[i] is still active/alive)
//     {
//     // tell each actor to do something (e.g. move)
//     actor[i]->doSomething();
//    if (SocratesDiedDuringThisTick())
//    return GWSTATUS_PLAYER_DIED;
//    if (SocratesCompletedTheCurrentLevel())
//    {
//    return GWSTATUS_FINISHED_LEVEL;
//    }
//     }
//    }
//    // Remove newly-dead actors after each tick
//    removeDeadGameObjects(); // delete dead game objects
//    // Potentially add new actors to the game (e.g., goodies or fungi)
//    addNewActors();
//    // Update the Game Status Line
//    updateDisplayText(); // update the score/lives/level text at screen top
//    // the player hasn’t completed the current level and hasn’t died, so
//    // continue playing the current level
//    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while(m_actors.size()>0){
        m_actors.pop_back();
    }
    delete m_player;
    m_player = nullptr;
}

void StudentWorld::addActor(Actor *add){
    m_actors.push_back(add);
}

void StudentWorld::removeDeadGameObjects(){
   vector<Actor*>::iterator it;
    for (it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if(!(*it)->isAlive()){
            m_actors.erase(it--);
        }
    }
}
