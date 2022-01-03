#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Socrates::doSomething2(){
    int ch;
    if (getAPointerToMyStudentWorld()->getKey(ch))
    {
    // user hit a key during this tick!
    switch (ch)
    {
        case KEY_PRESS_LEFT://counter clockwise
            m_posAngle+=5;
            moving();
            break;
        case KEY_PRESS_RIGHT: //clockwise
            m_posAngle-=5;
            moving();
            break;
        case KEY_PRESS_ENTER:{
            if(m_flameStk!=0){
                for(int i = 0; i < 16; i++){
                    int newdir = getDirection()+22*i;
                    newdir%=360;
                    Flame* flame = new Flame(getX() + cos(newdir/180.0*M_PI)*SPRITE_WIDTH, getY() + sin(newdir/180.0 * M_PI)*SPRITE_WIDTH, newdir, getAPointerToMyStudentWorld());
                    getAPointerToMyStudentWorld()->addActor(flame);
                    getAPointerToMyStudentWorld()->playSound(SOUND_PLAYER_FIRE);
                }
            m_flameStk--;
            }
            break;
        }
        case KEY_PRESS_SPACE:{
            if(m_sprayStk!=0){
            Spray* spray = new Spray(getX() + cos(getDirection()/180.0*M_PI)*SPRITE_WIDTH, getY() + sin(getDirection()/180.0 * M_PI)*SPRITE_WIDTH, getDirection(),getAPointerToMyStudentWorld());
            getAPointerToMyStudentWorld()->addActor(spray);
            m_sprayStk--;
                getAPointerToMyStudentWorld()->playSound(SOUND_PLAYER_SPRAY);
            }
            break;
        }
    }
    }
    else if(m_sprayStk<20){
        m_sprayStk++;
    }
}
void Socrates::moving(){
    int x = VIEW_RADIUS*(1+cos(m_posAngle/180.0*M_PI));
    int y = VIEW_RADIUS*(1+sin(m_posAngle/180.0*M_PI));
    moveTo(x,y);
    setDirection((m_posAngle+180)%360);
}

void Projectile::doSomething(){
    if(!isAlive()){
           return;
       }
    Actor* actor = getAPointerToMyStudentWorld()->collide(this);
    if(actor!=nullptr){
        if(!actor->hasHealth()){
            actor->dead();
        }
        else{
            //SUBTRACT HEALTH
            actor->changeHealth(-1 * m_dmg);
            if(actor->isAlive()){
                actor->OuchBacteria();
            }
        }
        dead();
    }
    else{
       for(int i = 0; i < SPRITE_WIDTH; i++){
           if(distTraveled() >= maxDist()){
               dead();
               return;
           }
           moveForward();
           traveled(1);
       }
    }
}

void Pit::doSomething(){
    if(m_countAggr == 0 && m_countReg == 0 && m_countE == 0){
        dead();
        return;
    }
    int summon = randInt(1, 50);
    int random;
    bool empty = false;
    if(summon == 1){
        //summon
        while(1){
            random = randInt(1, 3);
            switch(random){
                case 1:
                    if(m_countReg == 0){
                        empty = true;
                    }
                    else{
                        getAPointerToMyStudentWorld()->addActor(new RegSalmonella(getX(), getY(), getAPointerToMyStudentWorld()));
                        m_countReg--;
                    }
                    break;
                case 2:
                    if(m_countAggr == 0){
                        empty = true;
                    }
                    else{
                        getAPointerToMyStudentWorld()->addActor(new AggrSalmonella(getX(), getY(), getAPointerToMyStudentWorld()));
                        m_countAggr--;
                    }
                    break;
                case 3:
                    if(m_countE == 0){
                        empty = true;
                    }
                    else{
                        getAPointerToMyStudentWorld()->addActor(new Ecoli(getX(), getY(), getAPointerToMyStudentWorld()));
                        m_countE--;
                    }
                    break;
            }
            if(!empty){
                getAPointerToMyStudentWorld()->playSound(SOUND_BACTERIUM_BORN);
                break;
            }
            empty = false;
        }
    }
}

void Agent::doSomething(){
    if(m_health <= 0){
        dead();
    }
    doSomething2();
}


bool Bacterium::blocked(){
    double x = getX() + cos(getDirection()/180.0*M_PI)*3;
    double y = getY() + sin(getDirection()/180.0*M_PI)*3;
    if(getAPointerToMyStudentWorld()->thereIsDirt(x, y) || getAPointerToMyStudentWorld()->distance(x, VIEW_WIDTH/2, y, VIEW_HEIGHT/2) >= VIEW_RADIUS){
        return true;
    }
    return false;
}
void Bacterium::randomDir(){
    int randDir = randInt(0, 359);
    setDirection(randDir);
    m_movePlanDist = 10;
}
bool Bacterium::followHim(int pixel){
        double x = getX() + cos(getDirection()/180.0*M_PI)*pixel;
        double y = getY() + sin(getDirection()/180.0*M_PI)*pixel;
        if(!getAPointerToMyStudentWorld()->thereIsDirt(x, y)){
            moveAngle(getDirection(), pixel);
            return true;
        }
    return false;
}
void Bacterium::deathBehavior(){
    if(!isAlive()){
        int chance = randInt(1, 2);
        if(chance==1){
            getAPointerToMyStudentWorld()->addActor(new Food(getX(), getY(), getAPointerToMyStudentWorld()));
        }
        deathSound();
        return;
    }
}

void Bacterium::doSomething2(){
    deathBehavior();
    OnlyAggrSal();
    Socrates* playerHit = getAPointerToMyStudentWorld()->collideWithPlayer(this);
    
    if(playerHit!=nullptr){
        playerHit->changeHealth(-1*m_dmg);
        if(playerHit->isAlive()){
            getAPointerToMyStudentWorld()->playSound(SOUND_PLAYER_HURT);
        }
        if(skip()){
            return;
        }
    }
    else{
        if(m_foodCount >= 3){
            double newX = getX();
            if(getX() > VIEW_WIDTH/2){
                newX-=SPRITE_WIDTH/2;
            }
            else if(getX() < VIEW_WIDTH/2){
                newX+=SPRITE_WIDTH/2;
            }
            double newY = getY();
            if(getY() > VIEW_HEIGHT/2){
                newY-=SPRITE_WIDTH/2;
            }
            else if(getY() < VIEW_HEIGHT/2){
                newY+=SPRITE_WIDTH/2;
            }
            diffAdding(newX,newY);
            m_foodCount = 0;
            if(skip()){
                return;
            }
        }
        else{
            Actor* food = getAPointerToMyStudentWorld()->collideWithFood(this);
            if(food!=nullptr){
                m_foodCount+=1;
                food->dead();
            }
        }
    }
    OnlySalmonella();
    OnlyEcoli();
}

void Salmonella::OnlySalmonella(){
    //salmonella special
    if(!skip()){
        if(getPlanDist() > 0){
            setPlanDist(getPlanDist()-1);
            if(blocked()){
                randomDir();
            }
            else{
                moveAngle(getDirection(), 3);
            }
            return;
        }
        else{
            Actor* a = getAPointerToMyStudentWorld()->closestFood(this);
            if(a==nullptr){
                randomDir();
                return;
            }
            else{
                if(blocked()){
                    randomDir();
                    return;
                }
                else{
                    double newDir = atan2((a->getY()-getY()),(a->getX()-getX()))*180.0/M_PI;
                    setDirection(newDir);
                    setPlanDist(10);
                    return;
                }
            }
        }
    }
}
void Salmonella::deathSound(){
getAPointerToMyStudentWorld()->playSound(SOUND_SALMONELLA_DIE);
}
void Salmonella::OuchBacteria(){
    getAPointerToMyStudentWorld()->playSound(SOUND_SALMONELLA_HURT);
}

void RegSalmonella::diffAdding(double newX, double newY){
    getAPointerToMyStudentWorld()->addActor(new RegSalmonella(newX, newY, getAPointerToMyStudentWorld()));
}

void AggrSalmonella::diffAdding(double newX, double newY){
    getAPointerToMyStudentWorld()->addActor(new AggrSalmonella(newX, newY, getAPointerToMyStudentWorld()));
}
void AggrSalmonella::OnlyAggrSal(){
    Socrates* player = getAPointerToMyStudentWorld()->foundHim(this, 72);
    //step 2
    if(player!=nullptr){
         double newDir = atan2((player->getY()-getY()),(player->getX()-getX()))*180.0/M_PI;
         setDirection(newDir);
        followHim(3);
        m_skip = true;
    }
}

void Ecoli::OnlyEcoli(){
    //ecoli special
    Socrates* player = getAPointerToMyStudentWorld()->foundHim(this, 256);
    //step 2
    if(player!=nullptr){
        double newDir = atan2((player->getY()-getY()),(player->getX()-getX()))*180.0/M_PI;
        setDirection(newDir);
        for(int i = 0; i < 10; i++){
            if(followHim(2)){
                return;
            }
            else{
                setDirection(getDirection()+10);
            }
        }
    }
}
void Ecoli::diffAdding(double newX, double newY){
     getAPointerToMyStudentWorld()->addActor(new Ecoli(newX, newY, getAPointerToMyStudentWorld()));
}
void Ecoli::deathSound(){
    getAPointerToMyStudentWorld()->playSound(SOUND_ECOLI_DIE);
}
void Ecoli::OuchBacteria(){
    getAPointerToMyStudentWorld()->playSound(SOUND_ECOLI_HURT);
}

void Goodie::doSomething(){
    if(!isAlive()){
        return;
    }
    m_lifetime++;
    if(m_lifetime >= m_maxLife){
        dead();
        return;
    }
    Socrates* player = getAPointerToMyStudentWorld()->collideWithPlayer(this);
    if(player!=nullptr){
        getAPointerToMyStudentWorld()->playSound(SOUND_GOT_GOODIE);
        getAPointerToMyStudentWorld()->increaseScore(m_score);
        dead();
        doSomethingGoodie(player);
        return;
    }
}

void Restore::doSomethingGoodie(Socrates* player){
        player->changeHealth(100 - player->getHealth());
}

void FlameGoods::doSomethingGoodie(Socrates* player){
           player->changeFlameStk(5);
}

void ExtraLife::doSomethingGoodie(Socrates* player){
        getAPointerToMyStudentWorld()->incLives();
}

void Fungus::doSomethingGoodie(Socrates* player){
        player->changeHealth(-20);
}

