#pragma once //OPENGL_H


#include <QWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLShaderProgram>

QT_BEGIN_NAMESPACE
class QOpenGLContext;
QT_END_NAMESPACE

class OpenGL : public QWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT;

public:
    OpenGL();

    ~OpenGL();

    virtual void initialiaze();

protected:

};
