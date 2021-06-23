//
//  Logics.cpp
//  Tetris
//
//  Created by Глеб Косачёв on 21.06.21.
//

#include "Logics.hpp"
#include <optional>
#include <iostream>
#include <array>
#include <ctime>

extern std::optional<Block> *field;
extern Construction falling_construction;

Block::Block(int x, int y, float r, float g, float b, float a): position{x, y}, color{r, g, b, a}
{
}

Construction::~Construction()
{
    delete[] bottom_blocks;
    delete[] blocks;
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
    falling_construction.~Construction();
    falling_construction = Construction();
    switch (falling_construction.type = std::rand() % 5) {
        case 0:
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
            falling_construction.rotation_axis = &falling_construction.blocks[2];
            break;
        case 1:
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
            falling_construction.rotation_axis = nullptr;
            break;
        case 2:
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
            falling_construction.rotation_axis = &falling_construction.blocks[1];
            break;
        case 3:
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
            falling_construction.rotation_axis = &falling_construction.blocks[0];
            break;
        case 4:
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
            falling_construction.rotation_axis = &falling_construction.blocks[1];
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

bool ShouldReverse()
{
    std::vector<int> indices;
    for (int i = 0; i < falling_construction.size; i++)
    {
        indices.push_back(falling_construction.blocks[i]->position[0]);
    }
    for (int i = 0; i < indices.size(); i++)
    {
        if (std::count(indices.begin(), indices.end(), indices[i]) == 1)
        {
            indices.erase(indices.begin() + i);
            i--;
        }
    }
    std::sort(indices.begin(), indices.end());
    std::unique(indices.begin(), indices.end());
    for (int i = 0; i < indices.size(); i++)
    {
        int last_height = -1;
        for (int j = 0; j < falling_construction.size; j++)
        {
            if (falling_construction.blocks[j]->position[0] == indices[i])
            {
                if (last_height > falling_construction.blocks[j]->position[1]) return true;
                last_height = falling_construction.blocks[j]->position[1];
            }
        }
    }
    return false;
}

void HandleUp()
{
    if (!falling_construction.rotation_axis) return;
    if (falling_construction.type == 3)
    {
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (&falling_construction.blocks[i] == falling_construction.rotation_axis)
                continue;
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            if (coords[0] < 0 || coords[1] < 0 || coords[0] >= 10 || coords[1] >= 16) return;
        }
        std::vector<int> indices = {3, 1, 2};
        for (int &i : indices)
        {
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            field[coords[1] * 10 + coords[0]] = field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].value();
            falling_construction.blocks[i] = &field[coords[1] * 10 + coords[0]].value();
            field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].reset();
            falling_construction.blocks[i]->position[0] = coords[0];
            falling_construction.blocks[i]->position[1] = coords[1];
        }
        for (int i = 15; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                std::cout << field[i * 10 + j].has_value() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        if (ShouldReverse()) std::reverse(falling_construction.blocks, falling_construction.blocks + falling_construction.size);
        std::vector<Block **> bottom_blocks;
        delete[] falling_construction.bottom_blocks;
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (!field[(falling_construction.blocks[i]->position[1] - 1) * 10 + falling_construction.blocks[i]->position[0]].has_value()) bottom_blocks.push_back(&falling_construction.blocks[i]);
        }
        falling_construction.bottom_blocks = new Block **[bottom_blocks.size()];
        falling_construction.bottom_blocks_size = bottom_blocks.size();
        for (int i = 0; i < bottom_blocks.size(); i++)
        {
            falling_construction.bottom_blocks[i] = bottom_blocks[i];
        }
    }
    else if (falling_construction.type == 4)
    {
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (&falling_construction.blocks[i] == falling_construction.rotation_axis)
                continue;
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            if (coords[0] < 0 || coords[1] < 0 || coords[0] >= 10 || coords[1] >= 16) return;
        }
        std::vector<int> indices = {0, 3, 2};
        for (int &i : indices)
        {
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            field[coords[1] * 10 + coords[0]] = field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].value();
            falling_construction.blocks[i] = &field[coords[1] * 10 + coords[0]].value();
            field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].reset();
            falling_construction.blocks[i]->position[0] = coords[0];
            falling_construction.blocks[i]->position[1] = coords[1];
        }
        for (int i = 15; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                std::cout << field[i * 10 + j].has_value() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        if (ShouldReverse()) std::reverse(falling_construction.blocks, falling_construction.blocks + falling_construction.size);
        std::vector<Block **> bottom_blocks;
        delete[] falling_construction.bottom_blocks;
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (!field[(falling_construction.blocks[i]->position[1] - 1) * 10 + falling_construction.blocks[i]->position[0]].has_value()) bottom_blocks.push_back(&falling_construction.blocks[i]);
        }
        falling_construction.bottom_blocks = new Block **[bottom_blocks.size()];
        falling_construction.bottom_blocks_size = bottom_blocks.size();
        for (int i = 0; i < bottom_blocks.size(); i++)
        {
            falling_construction.bottom_blocks[i] = bottom_blocks[i];
        }
    }
    else
    {
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (&falling_construction.blocks[i] == falling_construction.rotation_axis)
                continue;
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            if (coords[0] < 0 || coords[1] < 0 || coords[0] >= 10 || coords[1] >= 16) return;
        }
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (&falling_construction.blocks[i] == falling_construction.rotation_axis)
                continue;
            std::array<int, 2> coords;
            coords[0] = (*falling_construction.rotation_axis)->position[0] + (*falling_construction.rotation_axis)->position[1] - falling_construction.blocks[i]->position[1];
            coords[1] = (*falling_construction.rotation_axis)->position[1] + falling_construction.blocks[i]->position[0] - (*falling_construction.rotation_axis)->position[0];
            field[coords[1] * 10 + coords[0]] = field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].value();
            falling_construction.blocks[i] = &field[coords[1] * 10 + coords[0]].value();
            field[falling_construction.blocks[i]->position[1] * 10 + falling_construction.blocks[i]->position[0]].reset();
            falling_construction.blocks[i]->position[0] = coords[0];
            falling_construction.blocks[i]->position[1] = coords[1];
        }
        for (int i = 15; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                std::cout << field[i * 10 + j].has_value() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        if (ShouldReverse()) std::reverse(falling_construction.blocks, falling_construction.blocks + falling_construction.size);
        std::vector<Block **> bottom_blocks;
        delete[] falling_construction.bottom_blocks;
        for (int i = 0; i < falling_construction.size; i++)
        {
            if (!field[(falling_construction.blocks[i]->position[1] - 1) * 10 + falling_construction.blocks[i]->position[0]].has_value()) bottom_blocks.push_back(&falling_construction.blocks[i]);
        }
        falling_construction.bottom_blocks = new Block **[bottom_blocks.size()];
        falling_construction.bottom_blocks_size = bottom_blocks.size();
        for (int i = 0; i < bottom_blocks.size(); i++)
        {
            falling_construction.bottom_blocks[i] = bottom_blocks[i];
        }
    }
}

void HandleLeft()
{
    
}

void HandleRight()
{
    
}
