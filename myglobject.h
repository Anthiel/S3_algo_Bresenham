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
    virtual void display() = 0;
    virtual void createGlObject() = 0;
    virtual void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) = 0;
    virtual void tearGLObjects() = 0;


protected:
    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;

};


#endif // MYGLOBJECT_H
