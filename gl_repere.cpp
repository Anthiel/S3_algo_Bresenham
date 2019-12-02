#include "gl_repere.h"

gl_repere::gl_repere(int nbPoint, QVector3D pos, double l, QVector3D ax, QVector3D color)
{
    nbPointControl = nbPoint;
    posInit = pos-(l/2.0)*ax;
    longueur = l;
    axe = ax;
    colr = color;
}

void gl_repere::initVertDataInfo(QVector<GLfloat> &vertData){
    dataBegin = vertData.size()/6;
    dataEnd = dataBegin+nbPointControl;
    isItInit = true;
}

void gl_repere::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}

void gl_repere::createGlObject(QVector<GLfloat> &vertData){

    initVertDataInfo(vertData);

    divisionAxe = 21;
    double hauteurAxePerpendiculaire = 0.05;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    //axe principal
    createPoint(vertices, colors, posInit, colr);

    for(double i = 1.0; i < nbPointControl; i++){

        QVector3D coord(posInit[0]+ ((longueur/i)*axe[0]),
                        posInit[1]+ ((longueur/i)*axe[1]),
                        posInit[2]+ ((longueur/i)*axe[2]));
        createPoint(vertices, colors, coord, colr);
    }

    //axes perpendiculaires à l'axe principal

    for(double i = 0.0; i <= divisionAxe - 1; i++){

        QVector3D coord(posInit[0]+ ((longueur*(i/(divisionAxe-1)))*axe[0] + hauteurAxePerpendiculaire*axe[1]),
                        posInit[1]+ ((longueur*(i/(divisionAxe-1)))*axe[1] + hauteurAxePerpendiculaire*(axe[0]+axe[2])),
                        posInit[2]+ ((longueur*(i/(divisionAxe-1)))*axe[2]));
        createPoint(vertices, colors, coord, colr);

        coord = QVector3D(posInit[0]+ ((longueur*(i/(divisionAxe-1)))*axe[0] - hauteurAxePerpendiculaire*axe[1]),
                          posInit[1]+ ((longueur*(i/(divisionAxe-1)))*axe[1] - hauteurAxePerpendiculaire*(axe[0]+axe[2])),
                          posInit[2]+ ((longueur*(i/(divisionAxe-1)))*axe[2]));
        createPoint(vertices, colors, coord, colr);
    }


    for (int i = 0; i < nbPointControl + 2*divisionAxe; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++)
            vertData.append(colors[i*3+j]);
    }
}

void gl_repere::display(QVector<GLfloat> &vertData){

    if(!isItInit){
        std::cout << "erreur : display gl_repere : vertdataInfo non init" << std::endl;
        return;
    }

    int debut = dataBegin;

    glDrawArrays(GL_LINE_STRIP, debut, nbPointControl);

    debut += nbPointControl;

    for(int i = 0; i < divisionAxe; i++){
        glDrawArrays(GL_LINE_STRIP, debut, 2);
        debut += 2;
    }
}

double gl_repere::effect(QVector<GLfloat> &vertData, QVector3D currentCoord){
    return 1;
}
