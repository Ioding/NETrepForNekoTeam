#ifndef RESOURCEMANAGE_H
#define RESOURCEMANAGE_H

#include <QMap>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class resourcemanage
{
public:
    resourcemanage();

    QMap<QString,QOpenGLShaderProgram> Shaders;
    QMap<QString,QOpenGLTexture> Textures;

};

#endif // RESOURCEMANAGE_H
