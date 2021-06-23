//
//  Logics.cpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#include "Logics.hpp"
#include <optional>
#include <array>
#include <ctime>

extern std::optional<Block> *field;
extern Construction falling_construction;

Block::Block(int x, int y, float r, float g, float b, float a): position{x, y}, color{r, g, b, a}
{
}

Construction::~Construction()
{
    delete[] blocks;
    delete[] bottom_blocks;
}

void GenConstruction()
{
    std::srand(std::time(NULL));
    float color[4];
    color[3] = 1;
    switch (std::rand() % 5)
    {
        case 0:
            color[0] = 1;
            color[1] = color[2] = 0;
            break;
        case 1:
            color[0] = color[2] = 0;
            color[1] = 1;
            break;
        case 2:
            color[0] = color[1] = 0;
            color[2] = 1;
            break;
        case 3:
            color[0] = color[1] = 1;
            color[2] = 0;
            break;
        case 4:
            color[0] = 1;
            color[1] = 0.5;
            color[2] = 0.2;
            break;
    }
    switch (std::rand() % 5) {
        case 0:
            falling_construction.~Construction();
            falling_construction = Construction();
            falling_construction.blocks = new Block *[4];
            falling_construction.size = 4;
            field[15 * 10 + 3] = Block(3, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[0] = &field[15 * 10 + 3].value();
            field[15 * 10 + 4] = Block(4, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[1] = &field[15 * 10 + 4].value();
            field[15 * 10 + 5] = Block(5, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[2] = &field[15 * 10 + 5].value();
            field[15 * 10 + 6] = Block(6, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[3] = &field[15 * 10 + 6].value();
            falling_construction.bottom_blocks = new Block **[4];
            falling_construction.bottom_blocks_size = 4;
            for (int i = 0 ; i < 4; i++)
            {
                falling_construction.bottom_blocks[i] = &falling_construction.blocks[i];
            }
            break;
        case 1:
            falling_construction.~Construction();
            falling_construction = Construction();
            falling_construction.blocks = new Block *[4];
            falling_construction.size = 4;
            field[14 * 10 + 4] = Block(4, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[0] = &field[14 * 10 + 4].value();
            field[14 * 10 + 5] = Block(5, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[1] = &field[14 * 10 + 5].value();
            field[15 * 10 + 4] = Block(4, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[2] = &field[15 * 10 + 4].value();
            field[15 * 10 + 5] = Block(5, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[3] = &field[15 * 10 + 5].value();
            falling_construction.bottom_blocks = new Block **[2];
            falling_construction.bottom_blocks_size = 2;
            falling_construction.bottom_blocks[0] = &falling_construction.blocks[0];
            falling_construction.bottom_blocks[1] = &falling_construction.blocks[1];
            break;
        case 2:
            falling_construction.~Construction();
            falling_construction = Construction();
            falling_construction.blocks = new Block *[4];
            falling_construction.size = 4;
            field[14 * 10 + 3] = Block(3, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[0] = &field[14 * 10 + 3].value();
            field[14 * 10 + 4] = Block(4, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[1] = &field[14 * 10 + 4].value();
            field[15 * 10 + 4] = Block(4, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[2] = &field[15 * 10 + 4].value();
            field[15 * 10 + 5] = Block(5, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[3] = &field[15 * 10 + 5].value();
            falling_construction.bottom_blocks = new Block **[3];
            falling_construction.bottom_blocks_size = 3;
            falling_construction.bottom_blocks[0] = &falling_construction.blocks[0];
            falling_construction.bottom_blocks[1] = &falling_construction.blocks[1];
            falling_construction.bottom_blocks[2] = &falling_construction.blocks[3];
            break;
        case 3:
            falling_construction.~Construction();
            falling_construction = Construction();
            falling_construction.blocks = new Block *[4];
            falling_construction.size = 4;
            field[14 * 10 + 3] = Block(3, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[0] = &field[14 * 10 + 3].value();
            field[14 * 10 + 4] = Block(4, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[1] = &field[14 * 10 + 4].value();
            field[14 * 10 + 5] = Block(5, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[2] = &field[14 * 10 + 5].value();
            field[15 * 10 + 3] = Block(3, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[3] = &field[15 * 10 + 3].value();
            falling_construction.bottom_blocks = new Block **[3];
            falling_construction.bottom_blocks_size = 3;
            falling_construction.bottom_blocks[0] = &falling_construction.blocks[0];
            falling_construction.bottom_blocks[1] = &falling_construction.blocks[1];
            falling_construction.bottom_blocks[2] = &falling_construction.blocks[2];
            break;
        case 4:
            falling_construction.~Construction();
            falling_construction = Construction();
            falling_construction.blocks = new Block *[4];
            falling_construction.size = 4;
            field[14 * 10 + 3] = Block(3, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[0] = &field[14 * 10 + 3].value();
            field[14 * 10 + 4] = Block(4, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[1] = &field[14 * 10 + 4].value();
            field[14 * 10 + 5] = Block(5, 14, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[2] = &field[14 * 10 + 5].value();
            field[15 * 10 + 4] = Block(4, 15, color[0], color[1], color[2], color[3]);
            falling_construction.blocks[3] = &field[15 * 10 + 4].value();
            falling_construction.bottom_blocks = new Block **[3];
            falling_construction.bottom_blocks_size = 3;
            falling_construction.bottom_blocks[0] = &falling_construction.blocks[0];
            falling_construction.bottom_blocks[1] = &falling_construction.blocks[1];
            falling_construction.bottom_blocks[2] = &falling_construction.blocks[2];
            break;
    }
}

bool IsFalling(int x, int y)
{
    if (!field[y * 10 + x].has_value()) return true;
    for (int i = 0; i < falling_construction.size; i++)
    {
        if (&field[y * 10 + x].value() == falling_construction.blocks[i]) return true;
    }
    return false;
}

void CheckFullRow()
{
    for (int i = 0; i < 16; i++)
    {
        bool full = true;
        for (int j = 0; j < 10; j++)
        {
            if (!field[i * 10 + j].has_value())
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            for (int j = 0; j < 10; j++)
                field[i * 10 + j].reset();
            for (int j = i + 1; j < 16; j++)
            {
                for (int o = 0; o < 10; o++)
                {
                    if (!IsFalling(o, j))
                    {
                        field[(j - 1) * 10 + o] = field[j * 10 + o];
                        field[j * 10 + o].reset();
                    }
                }
            }
        }
    }
}

void Drop()
{
    for (int j = 0; j < falling_construction.size; j++)
    {
        std::optional<Block> &block = field[falling_construction.blocks[j]->position[1] * 10 + falling_construction.blocks[j]->position[0]];
        field[(block.value().position[1] - 1) * 10 + block.value().position[0]] = block.value();
        falling_construction.blocks[j] = &field[(falling_construction.blocks[j]->position[1] - 1) * 10 + falling_construction.blocks[j]->position[0]].value();
        block.reset();
        falling_construction.blocks[j]->position[1]--;
    }
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
