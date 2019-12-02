#ifndef GL_POINT_H
#define GL_SEGMENT_H

#include <iostream>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "myglobject.h"

class gl_segment : public myGlObject
{
public:
    gl_segment(QVector3D pos, QVector3D posSuiv, QVector3D color);
    void initVertDataInfo(QVector<GLfloat> &vertData) override;
    void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) override;
    void createGlObject(QVector<GLfloat> &vertData) override;
    void display(QVector<GLfloat> &vertData) override;
    double effect(int coordID, int currentCoord);


    bool isItInit = false;
    int dataBegin = 0;
    int dataEnd = 0;

    int nbPointControl = 2; // 8 points dans un cube
    int division = 1; // 12 triangles dans un cube

    QVector3D posInit {0.0, 0.0, 0.0};
    QVector3D posNext {0.1, 0.0, 0.0};
    QVector3D colr {1.0, 1.0, 1.0};
};

#endif // GL_SEGMENT_H
