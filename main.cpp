//
//  main.cpp
//  Tetris
//
//  Created by Глеб Косачёв on 20.06.21.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Renderer/Renderer.hpp"

void Init(SDL_Window *&w, SDL_GLContext &cont, unsigned int &width, unsigned int &height);
void Shutdown(SDL_Window *&w, SDL_GLContext &cont);

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
                            //handle UP
                            break;
                        case SDLK_a:
                        case SDLK_LEFT:
                            //handle LEFT
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            //handle RIGHT
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            //handle DOWN
                            break;
                    }
                }
            }
            renderer.Clear();
            
            
            
            renderer.Draw(160);
            
            SDL_GL_SwapWindow(window);
        }
    }
    Shutdown(window, context);
    return 0;
}

void Init(SDL_Window *&w, SDL_GLContext &cont, unsigned int &width, unsigned int &height)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error initializing SDL!" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        std::exit(1);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

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
    SDL_GL_DeleteContext(cont);
    SDL_DestroyWindow(w);
    SDL_Quit();
}
