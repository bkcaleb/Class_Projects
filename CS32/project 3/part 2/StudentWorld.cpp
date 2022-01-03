#include "StudentWorld.h"
#include "GameConstants.h"

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

double StudentWorld::distance(const int x1, const int x2, const int y1, const int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int randomCoord(){
    return randInt(VIEW_WIDTH/2 - VIEW_RADIUS, VIEW_WIDTH/2 + VIEW_RADIUS);
}

bool StudentWorld::checkSameCoord(int x, int y){
    for(int i = 0; i < m_actors.size(); i++){
        //find distance from the center of the objs using distance formula
        if(distance(x, m_actors[i]->getX(), y, m_actors[i]->getY()) <= SPRITE_WIDTH){
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
    
    
//    add random amount of dirt
    int maxDirt = max(20, 180-20*getLevel());
    for(int i = 0; i < maxDirt; i++){
        while(1){
        int randPosX = randomCoord();
        int randPosY = randomCoord();
            if(distance(randPosX, VIEW_WIDTH/2, randPosY, VIEW_WIDTH/2) < 120){
                m_actors.push_back(new Dirt(randPosX,randPosY, this));
                break;
            }
        }
    }

    //adding food
    int minFood = min(5*getLevel(), 25);
    for(int i = 0; i < minFood; i++){
        while(1){
            int randPosX = randomCoord();
            int randPosY = randomCoord();
            if(randomPositions(randPosX, randPosY)){
                m_actors.push_back(new Food(randPosX, randPosY, this));
                break;
            }
        }
    }
    
    //add pit
    for(int i = 0; i < getLevel(); i++){
        while(1){
            int randPosX = randomCoord();
            int randPosY = randomCoord();
            if(randomPositions(randPosX, randPosY)){
                m_actors.push_back(new Pit(randPosX, randPosY, this));
                break;
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // The term "actors" refers to all bacteria, Socrates, goodies,
    // pits, flames, spray, foods, etc.
    // Give each actor a chance to do something, incl. Socrates
    
    if(m_player->isAlive()){
        m_player->doSomething();
    }else{
        decLives();
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isAlive()){
            m_actors[i]->doSomething();
        }
    }
    
    removeDeadGameObjects();
    
    //check if the level is comepleted
    if(finishedLevel()){
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    //adding fungus and goodies
    int maxFungus = max(510 - getLevel() * 10, 200);
    int chanceFungus = randInt(0, maxFungus-1);
    int maxGoodie = max(510 - getLevel() * 10, 250);
    int chanceGoodie = randInt(0, maxGoodie -1);
    if(chanceFungus == 0){
        while(1){
            int randPosX = randomCoord();
            int randPosY = randomCoord();
            if(distance(randPosX, VIEW_WIDTH/2, randPosY, VIEW_WIDTH/2) == VIEW_RADIUS){
                int lifetime =  max(randInt(0, 300 - 10 * getLevel() - 1), 50);
                addActor(new Fungus(randPosX, randPosY, lifetime, this));
                break;
            }
        }
    }
    if(chanceGoodie == 0){
        while(1){
            int randPosX = randomCoord();
            int randPosY = randomCoord();
            if(distance(randPosX, VIEW_WIDTH/2, randPosY, VIEW_WIDTH/2) == VIEW_RADIUS){
                int chance = randInt(1, 10);
                if(chance >=1 && chance <= 6){
                    //add restore
                    int lifetime = max(randInt(0, 300 - 10 * getLevel() - 1), 50);
                    addActor(new Restore(randPosX, randPosY, lifetime, this));
                    break;
                }
                else if(chance >6 && chance <=9){
                    int lifetime = max(randInt(0, 300 - 10 * getLevel() - 1), 50);
                    addActor(new FlameGoods(randPosX, randPosY, lifetime, this));
                    break;
                }
                else{
                    int lifetime = max(randInt(0, 300 - 10 * getLevel() - 1), 50);
                    addActor(new ExtraLife(randPosX, randPosY, lifetime, this));
                    break;
                }
            }
        }
    }
    setGameStatText(updateDisplayText());
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while(m_actors.size()>0){
        delete m_actors.back();
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
            delete *it;
            m_actors.erase(it--);
        }
    }
}

Socrates* StudentWorld::collideWithPlayer(const Actor* a)
{
    double actX = a->getX();
    double actY = a->getY();
            
    double playerX = m_player->getX();
    double playerY = m_player->getY();
            
    int dist = distance(actX, playerX, actY, playerY);
    
    if (dist <= SPRITE_WIDTH){
        playSound(SOUND_PLAYER_HURT);
        return m_player;
    }
    
    return nullptr;
}

Actor* StudentWorld::collide(const Actor *a){
    for(int i = 0; i < m_actors.size(); i++){
        if(a!=m_actors[i] && m_actors[i]->damagable()){
            double actX = a->getX();
            double actY = a->getY();
                    
            double actorX = m_actors[i]->getX();
            double actorY = m_actors[i]->getY();
                    
            int dist = distance(actX, actorX, actY, actorY);
            
            if (dist <= SPRITE_WIDTH){
                return m_actors[i];
            }
        }
    }
    return nullptr;
}

bool StudentWorld::thereIsDirt(const int x, const int y){
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isDirt()){
            if(distance(m_actors[i]->getX(), x, m_actors[i]->getY(), y) <= SPRITE_WIDTH/2){
                return true;
            }
        }
    }
    return false;
}

Actor* StudentWorld::closestFood(const Actor *a){
    double actX = a->getX();
    double actY = a->getY();
    Actor* temp = nullptr;
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isFood() && distance(m_actors[i]->getX(), actX, m_actors[i]->getY(), actY) <= VIEW_RADIUS){
            if(temp == nullptr){
                temp = m_actors[i];
            }
            else{
                double dist1 = distance(m_actors[i]->getX(), actX, m_actors[i]->getY(), actY);
                double dist2 = distance(temp->getX(), actX, temp->getY(), actY);
                if(dist1 < dist2){
                    temp = m_actors[i];
                }
            }
        }
    }
    return temp;
}

Actor* StudentWorld::collideWithFood(const Actor *a){
    double x = a->getX();
    double y = a->getY();
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isFood()){
            if(distance(m_actors[i]->getX(), x, m_actors[i]->getY(), y) <= SPRITE_WIDTH){
                return m_actors[i];
            }
        }
    }
    return nullptr;
}

Socrates* StudentWorld::foundHim(const Actor *a, int pixel){
      double actX = a->getX();
      double actY = a->getY();
              
      double playerX = m_player->getX();
      double playerY = m_player->getY();
              
      int dist = distance(actX, playerX, actY, playerY);
      
      if (dist <= pixel)
          return m_player;
      
      return nullptr;
}

string StudentWorld::updateDisplayText(){
    ostringstream oss;
    oss << "Score: ";
    int positive = 1;
    if(getScore()<0){
        oss << "-";
        positive = -1;
    }
    oss<< setw(6);
    oss.fill('0');
    oss << getScore()* positive;
    oss.fill(' ');
    oss << setw(9) << "Level: " << getLevel();
    oss << setw(9) << "Lives: " << getLives();
    oss << setw(10) << "Health: " << m_player->getHealth();
    oss << setw(10) << "Sprays: " << m_player->getSpraystk();
    oss << setw(9) << "Flame: " << m_player->getFlamestk();
    string s = oss.str();
    return s;
}

bool StudentWorld::finishedLevel(){
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->badguys()){
            return false;
        }
    }
    return true;
}

bool StudentWorld::randomPositions(int x, int y){
    if(distance(x, VIEW_WIDTH/2, y, VIEW_WIDTH/2) < 120){
        if(!checkSameCoord(x, y)){
            return true;
        }
    }
    return false;
}
