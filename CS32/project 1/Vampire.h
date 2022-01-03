//
//  vampires.h
//  CS32 P1
//
//  Created by Caleb Lee on 1/9/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#ifndef vampires_hpp
#define vampires_hpp

#include <stdio.h>


class Arena;
class Vampire
{
  public:
      // Constructor
    Vampire(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};
#endif /* vampires_hpp */
