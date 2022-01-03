//
//  Game.hpp
//  CS32 P1
//
//  Created by Caleb Lee on 1/9/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

class Arena;
class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};
  
      // Mutators
    void play();

#endif /* Game_hpp */
