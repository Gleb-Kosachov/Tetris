//
//  Renderer.cpp
//  Renderer
//
//  Created by Глеб Косачёв on 20.06.21.
//

#include "Renderer.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

bool glCheckErrors()
{
    if (GLenum error = glGetError())
    {
        std::cout << "OpenGL error: " << error << std::endl;
        return true;
    }
    return false;
}

void glClearErrors()
{
    while (glGetError());
}

#define GL_CALL(func)\
glClearErrors();\
func;\
if (glCheckErrors()) {std::cout << "File: " << __FILE__ << std::endl << "Line: " << __LINE__ << std::endl << "Function: " << #func << std::endl; std::abort();}

Vertex::Vertex()
{
}

Vertex::Vertex(float x, float y, float r, float g, float b, float a): coordinate{x, y}, color{r, g, b, a}
{
}

Renderer::Renderer()
{
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error initializing GLEW!" << std::endl;
        std::exit(1);
    }
    GL_CALL(glGenVertexArrays(1, &VertexArray));
    GL_CALL(glBindVertexArray(VertexArray));
    
    GL_CALL(glGenBuffers(1, &VertexBuffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * max_blocks * 4, nullptr, GL_DYNAMIC_DRAW));
    vertices = new Vertex[max_blocks * 4];
    
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(sizeof(float) * 2)));
    
    GL_CALL(glGenBuffers(1, &IndexBuffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer));
    unsigned int indices[max_blocks * 6];
    for (int i = 0; i < max_blocks; i++)
    {
        indices[i * 6] = i * 4;
        indices[i * 6 + 1] = i * 4 + 1;
        indices[i * 6 + 2] = i * 4 + 2;
        indices[i * 6 + 3] = i * 4;
        indices[i * 6 + 4] = i * 4 + 2;
        indices[i * 6 + 5] = i * 4 + 3;
    }
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
}

Renderer::~Renderer()
{
    delete[] vertices;
    GL_CALL(glDeleteBuffers(1, &VertexBuffer));
    GL_CALL(glDeleteBuffers(1, &IndexBuffer));
    GL_CALL(glDeleteVertexArrays(1, &VertexArray));
    GL_CALL(glDeleteProgram(Shader));
}

void Renderer::Clear()
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

namespace {
    std::pair<std::string, std::string> ReadShader(const char *vfilepath, const char *ffilepath)
    {
        std::pair<std::string, std::string> result;
        std::ifstream vfile(vfilepath);
        if (!vfile.is_open()) std::cout << "File not open!" << std::endl;
        while (!vfile.eof())
        {
            std::string temp;
            std::getline(vfile, temp);
            result.first += temp + '\n';
        }
        std::ifstream ffile(ffilepath);
        if (!ffile.is_open()) std::cout << "File not open!" << std::endl;
        while (!ffile.eof())
        {
            std::string temp;
            std::getline(ffile, temp);
            result.second += temp + '\n';
        }
        return result;
    }

    unsigned int CreateShader(const char *vertex, const char *fragment)
    {
        GL_CALL(unsigned int result = glCreateProgram());
        GL_CALL(unsigned int vshader = glCreateShader(GL_VERTEX_SHADER));
        GL_CALL(unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER));
        int s = strlen(vertex);
        GL_CALL(glShaderSource(vshader, 1, &vertex, nullptr));
        GL_CALL(glCompileShader(vshader));
        int compiled;
        GL_CALL(glGetShaderiv(vshader, GL_COMPILE_STATUS, &compiled));
        if (compiled == GL_FALSE)
        {
            std::cout << "Error compiling vertex shader!" << std::endl;
            int length;
            GL_CALL(glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &length));
            GLchar *msg = new GLchar[length];
            GL_CALL(glGetShaderInfoLog(vshader, length, &length, msg));
            std::cout << msg << std::endl;
        }
        s = strlen(fragment);
        GL_CALL(glShaderSource(fshader, 1, &fragment, nullptr));
        GL_CALL(glCompileShader(fshader));
        GL_CALL(glGetShaderiv(fshader, GL_COMPILE_STATUS, &compiled));
        if (compiled == GL_FALSE)
        {
            std::cout << "Error compiling fragment shader!" << std::endl;
            int length;
            GL_CALL(glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &length));
            GLchar *msg = new GLchar[length];
            GL_CALL(glGetShaderInfoLog(fshader, length, &length, msg));
            std::cout << msg << std::endl;
            return 1;
        }
        GL_CALL(glAttachShader(result, vshader));
        GL_CALL(glAttachShader(result, fshader));
        GL_CALL(glLinkProgram(result));
        GL_CALL(glValidateProgram(result));
        return result;
    }
}

void Renderer::LoadShader(const char *vpath, const char *fpath)
{
    std::pair<std::string, std::string> shaderSource = ReadShader(vpath, fpath);
    GL_CALL(Shader = CreateShader(shaderSource.first.c_str(), shaderSource.second.c_str()));
    GL_CALL(glUseProgram(Shader));
    GL_CALL(MVPlocation = glGetUniformLocation(Shader, "MVP"));
    if (MVPlocation == -1)
    {
        std::cout << "MVP does not exist in shader" << std::endl;
        std::abort();
    }
}

void Renderer::UploadVertices()
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
    GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * max_blocks * 4, vertices));
}

void Renderer::Draw(unsigned int count)
{
    GL_CALL(glBindVertexArray(VertexArray));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer));
    GL_CALL(glUseProgram(Shader));
    GL_CALL(glDrawElements(GL_TRIANGLES, count * 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::SetMVP(glm::mat4 &MVP)
{
    GL_CALL(glUniformMatrix4fv(MVPlocation, 1, GL_FALSE, &MVP[0][0]));
}
