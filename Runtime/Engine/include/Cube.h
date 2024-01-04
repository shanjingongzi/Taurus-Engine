#ifndef CUBE_H
#define CUBE_H
#include "IRenderObject.h"
#include "IProgram.h"
#include <vector>
#include "glm/glm.hpp"
class Cube:public IRenderObject
{
public:
    static std::string execPath;
public:
    Cube();
    virtual ~Cube();
    void Render()override;
    void Bind()override;
    void Unbind()override;
    IProgram *program()override;
    static void Regsiter();
    glm::vec4 lineColor=glm::vec4(1.0f,1.0f,1.0f,1.0f);
private:
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    IProgram *programPtr;
    unsigned int count;
    std::vector<unsigned int>indices;
    glm::mat4 model=glm::mat4(1.0);

};
#endif
