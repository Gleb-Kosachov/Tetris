//
//  Logics.hpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#ifndef Logics_hpp
#define Logics_hpp

#include <stdio.h>

struct Block
{
    int position[2];
    float color[4];
};

struct Construction
{
    Block **blocks;
    bool falling;
};

void HandleLeft();
void HandleRight();
void HandleDown();
void HandleUp();

#endif /* Logics_hpp */
