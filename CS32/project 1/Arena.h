//
//  arena.hpp
//  CS32 P1
//
//  Created by Caleb Lee on 1/9/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#ifndef arena_hpp
#define arena_hpp

#include <stdio.h>
#include "globals.h"
#include "History.h"


class Vampire;
class Player;
class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     vampireCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVampiresAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVampire(int r, int c);
    bool addPlayer(int r, int c);
    void moveVampires();
    
    History& history();

  private:
    int      m_grid[MAXROWS][MAXCOLS];
    int      m_rows;
    int      m_cols;
    Player*  m_player;
    Vampire* m_vampires[MAXVAMPIRES];
    int      m_nVampires;
    int      m_turns;
    History  m_his;
      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};
#endif /* arena_hpp */
