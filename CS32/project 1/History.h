//
//  History.hpp
//  CS32 P1
//
//  Created by Caleb Lee on 1/12/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_row;
    int m_col;
    char arr[MAXROWS][MAXCOLS];
};
#endif /* History_hpp */
