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
    virtual void createGlObject(QVector<GLfloat> &vertData) = 0;
    virtual void initVertDataInfo(QVector<GLfloat> &vertData) = 0;
    virtual void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) = 0;
    virtual double effect(QVector<GLfloat> &vertData, QVector3D currentCoord) = 0;


};


#endif // MYGLOBJECT_H
