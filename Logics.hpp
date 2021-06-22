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
    float color[4];
    Block(float r, float g, float b, float a);
};

struct Construction
{
    Block **blocks;
    int size;
    ~Construction();
    void Drop();
};

void HandleLeft();
void HandleRight();
void HandleUp();

#endif /* Logics_hpp */
