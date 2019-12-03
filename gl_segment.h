#ifndef GL_SEGMENT_H
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
    gl_segment(QVector3D pos, QVector3D posSuiv, QVector3D color, bool isDisplay);

    void setPositionPoint(QVector3D pos) override;
    void setPositionPoint(QVector3D pos, QVector3D posSuiv) override;
    void setDisplay(bool mode) override;

    void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) override;
    void createGlObject() override;
    void display(QOpenGLShaderProgram &m_program) override;
    void tearGLObjects() override;


    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;
    bool displayIt = true;

    int nbPointControl = 2; // 8 points dans un cube
    int division = 1; // 12 triangles dans un cube
    int nbPointStructure = 2; //pour une ligne : 2 points necessaires

    QVector3D posInit {0.0, 0.0, 0.0};
    QVector3D posNext {0.1, 0.0, 0.0};
    QVector3D colr {1.0, 1.0, 1.0};
};

#endif // GL_SEGMENT_H
