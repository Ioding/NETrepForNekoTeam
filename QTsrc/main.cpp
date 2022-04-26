#include "opengl.h"

#include <QApplication>
#include <QtOpenGL>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGL w;
    w.show();
    return a.exec();
}
