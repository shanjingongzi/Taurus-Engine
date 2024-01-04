#include "glad.h"
#include "Cube.h"
#include "glProgram.h"
#include "glShader.h"
#include <vector>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

std::string Cube::execPath;

Cube::Cube()
{
    float vertex[]{
        -1.0f,	-1.0f,	-1.0f,
        1.0f,	-1.0f,	-1.0f,
        1.0f,	1.0f,	-1.0f,
        -1.0f,	1.0f,	-1.0f,

        -1.0f,	-1.0f,	1.0f,
        1.0f,	-1.0f,	1.0f,
        1.0f,	1.0f,	1.0f,
        -1.0f,	1.0f,	1.0f,

    };
    indices=
    {
        0,1,2,
        2,3,0,

       //bcak
        4,7,6,
        6,5,4,

        //left
        0,3,7,
        7,4,0,

        //right
        1,5,6,
        6,2,1,

        //top

        3,2,6,
        6,7,3,

        //buttom

        0,4,5,
        5,1,0
    };
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    count=indices.size();
    glGenBuffers(1,&ebo);
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*3,(void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    programPtr=new glProgram();
#ifdef _MSC_VER
    programPtr->AddShader(new glShader(GL_VERTEX_SHADER,execPath+std::string("\\shader\\vertex.glsl")));
    programPtr->AddShader(new glShader(GL_FRAGMENT_SHADER,execPath+std::string("\\shader\\fragment.glsl")));
#elif __clang__
    programPtr->AddShader(new glShader(GL_VERTEX_SHADER,execPath+std::string("/shader/vertex.glsl")));
    programPtr->AddShader(new glShader(GL_FRAGMENT_SHADER,execPath+std::string("/shader/fragment.glsl")));
#elif __GNU__
    programPtr->AddShader(new glShader(GL_VERTEX_SHADER, "./shader/vertex.glsl"));
	programPtr->AddShader(new glShader(GL_FRAGMENT_SHADER, "./shader/fragment.glsl"));
#endif
    programPtr->Link();
}

Cube::~Cube()
{

}

void Cube::Bind()
{
    programPtr->Use();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    programPtr->SetVector4("color", glm::value_ptr(lineColor));
}

void Cube::Render()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,0);
//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//	glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,0);
}

void Cube::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

IProgram* Cube::program()
{
    return programPtr;
}

void Cube::Regsiter()
{
}

struct Register
{
    Register() {
        Cube::Regsiter();
    }
};
