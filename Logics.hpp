//
//  Logics.hpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#ifndef Logics_hpp
#define Logics_hpp

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
    Block ***bottom_blocks = nullptr;
    int bottom_blocks_size = 0;
    ~Construction();
};

void GenConstruction();

void HandleLeft();
void HandleRight();
void HandleUp();

#endif /* Logics_hpp */
