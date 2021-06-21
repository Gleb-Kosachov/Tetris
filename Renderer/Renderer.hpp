//
//  Renderer.hpp
//  Renderer
//
//  Created by Глеб Косачёв on 20.06.21.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
    float coordinate[2];
    float color[4];
    Vertex();
    Vertex(float x, float y, float r, float g, float b, float a);
};

class Renderer
{
public:
    Vertex *vertices;
private:
    unsigned int VertexArray, VertexBuffer, IndexBuffer, Shader;
    int MVPlocation;
    constexpr static int max_blocks = 160;
public:
    Renderer();
    ~Renderer();
    void Clear();
    void LoadShader(const char *vpath, const char *fpath);
    void UploadVertices();
    void Draw(unsigned int count);
    void SetMVP(glm::mat4 &MVP);
};

#endif /* Renderer_hpp */
