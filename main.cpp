//
//  main.cpp
//  Tetris
//
//  Created by Глеб Косачёв on 20.06.21.
//

#include <iostream>
#include <optional>
#include <chrono>
#include <array>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Renderer.hpp"
#include "Logics.hpp"

std::optional<Block> *field;
Construction falling_construction;

void Init(SDL_Window *&w, SDL_GLContext &cont, unsigned int &width, unsigned int &height);
void Shutdown(SDL_Window *&w, SDL_GLContext &cont);

void Display(Renderer &r)
{
    int quads = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (field[i * 10 + j].has_value())
            {
                r.vertices[quads * 4] = Vertex(j, i, field[i * 10 + j].value().color);
                r.vertices[quads * 4 + 1] = Vertex(j + 1, i, field[i * 10 + j].value().color);
                r.vertices[quads * 4 + 2] = Vertex(j + 1, i + 1, field[i * 10 + j].value().color);
                r.vertices[quads * 4 + 3] = Vertex(j, i + 1, field[i * 10 + j].value().color);
                quads++;
            }
        }
    }
    r.UploadVertices();
    r.Clear();
    r.Draw(quads);
}

int main(int argc, const char * argv[]) {
    
    SDL_Window *window;
    SDL_GLContext context;
    unsigned int ScreenWidth = 300, ScreenHeight = 480;
    
    Init(window, context, ScreenWidth, ScreenHeight);
    SDL_GL_MakeCurrent(window, context);
    
    glm::mat4 proj = glm::ortho(0.0f, 10.0f, 0.0f, 16.0f);
    
    {
        Renderer renderer;
        renderer.LoadShader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
        renderer.SetMVP(proj);
        
        int OffsetTime = 500;
        
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        
        GenConstruction();
        
        SDL_Event event;
        while (true)
        {
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    break;
                if (event.type == SDL_WINDOWEVENT)
                {
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        break;
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        ScreenWidth = event.window.data1;
                        ScreenHeight = event.window.data2;
                        glViewport(0, 0, ScreenWidth, ScreenHeight);
                        float var = static_cast<float>(ScreenHeight) / ScreenWidth;
                        if (var > 1.6)
                        {
                            float k = ScreenWidth / 10;
                            proj = glm::ortho(0.0f, 10.0f, -((static_cast<float>(ScreenHeight) - static_cast<float>(ScreenWidth) * 1.6f) / 2.0f) / k, (static_cast<float>(ScreenHeight) - static_cast<float>(ScreenWidth) * 1.6f) / 2.0f / k + 16.0f);
                        }
                        else
                        {
                            float k = ScreenHeight / 16;
                            proj = glm::ortho(-(static_cast<float>(ScreenWidth) - static_cast<float>(ScreenHeight) / 1.6f) / 2 / k, (static_cast<float>(ScreenWidth) - static_cast<float>(ScreenHeight) / 1.6f) / 2 / k + 10.0f, 0.0f, 16.0f);
                        }
                        renderer.SetMVP(proj);
                    }
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_UP:
                            HandleUp();
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            HandleLeft();
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            HandleRight();
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            OffsetTime = 200;
                            break;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {
                    if (event.key.keysym.sym == SDLK_DOWN)
                        OffsetTime = 500;
                }
            }
            
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() >= OffsetTime)
            {
                start = std::chrono::high_resolution_clock::now();
                Drop();
                
                bool s = false;
                repeat:
                for (int i = 0; i < falling_construction.bottom_blocks_size; i++)
                {
                    Block &block = field[(*falling_construction.bottom_blocks[i])->position[1] * 10 + (*falling_construction.bottom_blocks[i])->position[0]].value();
                    if (field[(block.position[1] - 1) * 10 + block.position[0]] || !block.position[1])
                    {
                        if (s)
                            std::exit(0);
                        s = true;
                        GenConstruction();
                        goto repeat;
                        break;
                    }
                }
            }
            
            CheckFullRow();
            
            Display(renderer);
            
            SDL_GL_SwapWindow(window);
        }
    }
    Shutdown(window, context);
    return 0;
}

void Init(SDL_Window *&w, SDL_GLContext &cont, unsigned int &width, unsigned int &height)
{
    field = new std::optional<Block>[16 * 10];
    for (int i = 0; i < 160; i++)
        field[i].reset();
    
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error initializing SDL!" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        std::exit(1);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    w = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!w)
    {
        std::cout << "Error creating window!" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        std::exit(1);
    }
    
    cont = SDL_GL_CreateContext(w);
    if (!cont)
    {
        std::cout << "Error creating OpenGL context!" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        std::exit(1);
    }
    
    glClearColor(0, 0, 0, 1);
}

void Shutdown(SDL_Window *&w, SDL_GLContext &cont)
{
    delete[] field;
    SDL_GL_DeleteContext(cont);
    SDL_DestroyWindow(w);
    SDL_Quit();
}
