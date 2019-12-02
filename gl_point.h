#ifndef GL_POINT_H
#define GL_POINT_H

#include <iostream>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "myglobject.h"

class gl_point : public myGlObject
{
public:
    gl_point(QVector3D pos, QVector3D color, double h);
    void initVertDataInfo(QVector<GLfloat> &vertData) override;
    void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) override;
    void createGlObject(QVector<GLfloat> &vertData) override;
    void display(QVector<GLfloat> &vertData) override;
    double effect(QVector<GLfloat> &vertData, QVector3D currentCoord) override;


    bool isItInit = false;
    int dataBegin = 0;
    int vertDataBegin = 0;
    int dataEnd = 0;
    int nbPointStructure = 3; //pour un triangle : 3 points necessaires

    int nbPointControl = 8; // 8 points dans un cube
    int division = 12; // 12 triangles dans un cube

    QVector3D posInit {0.0, 0.0, 0.0};
    QVector3D colr {1.0, 1.0, 1.0};
    double hauteur = 0.02;
};

#endif // GL_POINT_H
