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
    dataBegin = vertData.size();
    dataEnd = dataBegin+nbPointControl;
    isItInit = true;
}

void gl_repere::createGlObject(QVector<GLfloat> &vertData){

    initVertDataInfo(vertData);
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    for(int i = 1; i < nbPointControl; i++){

        vertices.push_back(posInit[0]+ ((longueur/i)*axe[0]));
        vertices.push_back(posInit[1]+ ((longueur/i)*axe[1]));
        vertices.push_back(posInit[2]+ ((longueur/i)*axe[2]));

        colors.push_back(colr[0]);
        colors.push_back(colr[1]);
        colors.push_back(colr[2]);
    }

    vertices.push_back(posInit[0]);
    vertices.push_back(posInit[1]);
    vertices.push_back(posInit[2]);

    colors.push_back(colr[0]);
    colors.push_back(colr[1]);
    colors.push_back(colr[2]);


    for (int i = 0; i < nbPointControl; ++i) {
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

    glDrawArrays(GL_LINE_STRIP, dataBegin, nbPointControl);
}

double gl_repere::effect(int coordID, int currentCoord){

    return 1;
}
