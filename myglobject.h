#ifndef MYGLOBJECT_H
#define MYGLOBJECT_H

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>


class myGlObject{
public:
    //virtual ~myGlObject() = 0;
    virtual void display(QVector<GLfloat> &vertData) = 0;

};


#endif // MYGLOBJECT_H
