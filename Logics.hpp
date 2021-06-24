//
//  Logics.hpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#ifndef Logics_hpp
#define Logics_hpp

#include <vector>

struct Block
{
    int position[2];
    float color[4];
    Block(int x, int y, float r, float g, float b, float a);
};

struct Construction
{
    Block **blocks = nullptr;
    int size = 0;
    Block **rotation_axis;
    int type;
    ~Construction();
};

void GenConstruction();
void CheckFullRow();
void Drop();
bool IsFalling(int x, int y);

void HandleLeft();
void HandleRight();
void HandleUp();

#endif /* Logics_hpp */
