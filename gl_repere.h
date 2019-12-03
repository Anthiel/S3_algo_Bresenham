#ifndef GL_REPERE_H
#define GL_REPERE_H

#include <iostream>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "myglobject.h"

class gl_repere : public myGlObject
{
public:
    gl_repere(int nbPoint, QVector3D pos, double h, QVector3D ax, QVector3D color);
    void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) override;
    void createGlObject() override;
    void display() override;
    void tearGLObjects() override;


    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;

    int nbPointStructure = 2; //pour une ligne : 2 points necessaires

    int nbPointControl = 2;

    QVector3D posInit {0.0, 0.0, 0.0};
    QVector3D axe {1.0, 0.0, 0.0}; // par defaut, on utilise l'axe X
    QVector3D colr {1.0, 1.0, 1.0};
    double longueur = 0.0;

    int divisionAxe = 11;


};

#endif // GL_REPERE_H
