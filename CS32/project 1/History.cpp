//
//  History.cpp
//  CS32 P1
//
//  Created by Caleb Lee on 1/12/20.
//  Copyright © 2020 Caleb Lee. All rights reserved.
//
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;
#include "History.h"

History::History(int nRows, int nCols){
    m_row = nRows;
    m_col = nCols;
    for(int i = 1; i <= MAXROWS; i++){
        for(int j = 1; j <= MAXCOLS; j++){
            arr[i-1][j-1] = '.';
        }
    }
}
bool History::record(int r, int c){
    if(r < 1 || r > MAXROWS || c < 1 || c > MAXCOLS){
        return false;
    }
    
    if(arr[r-1][c-1] == '.'){
        arr[r-1][c-1] = 'A';
    }
    else if(arr[r-1][c-1] == 'Z'){
        arr[r-1][c-1] = 'Z';
    }
    else{
        arr[r-1][c-1]++;
    }
    return true;
}
void History::display() const{
    clearScreen();
    
   for (int r = 1; r <= m_row; r++)
    {
        for (int c = 1; c <= m_col; c++)
            cout << arr[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
