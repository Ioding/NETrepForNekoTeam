#ifndef SHADER_H
#define SHADER_H

#include<QOpenGLShaderProgram>

class Shader
{
public:
    GLuint ID;

    Shader() {};
    ~Shader();

    Shader& Use();
};

#endif // SHADER_H
