#include <glad.h>
#include "OpenGLDevice.h"

void OpenGLDevice::InitFramebuffer()
{

    glClearColor(0.0f, 0.1f, 0.25f, 1.0f);
    glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());
    float vertices[] = {
        // positions               // texture coords
         1.0f,  1.0f, 0.0f,      1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,      1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,      0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,      0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void OpenGLDevice::DeviceRender(unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
