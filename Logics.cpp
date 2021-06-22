//
//  Logics.cpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#include "Logics.hpp"
#include <optional>

extern std::optional<Block> *field;
extern Construction *falling_construction;

Block::Block(float r, float g, float b, float a): color{r, g, b, a}
{
}

Construction::~Construction()
{
    delete[] blocks;
}

void HandleUp()
{
    
}

void HandleLeft()
{
    
}

void HandleRight()
{
    
}

void HandleDown()
{
    
}
