#include "gl_segment.h"

gl_segment::gl_segment(QVector3D pos, QVector3D posSuiv, QVector3D color)
{
    posInit = pos;
    posNext = posSuiv;
    colr = color;
}

void gl_segment::initVertDataInfo(QVector<GLfloat> &vertData){
    dataBegin = vertData.size()/6;
    dataEnd = dataBegin+nbPointControl;
    isItInit = true;
}

void gl_segment::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}

void gl_segment::createGlObject(QVector<GLfloat> &vertData){

    initVertDataInfo(vertData);

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    QVector3D coord(posInit[0], posInit[1], posInit[2]);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posNext[0], posNext[1], posNext[2]);
    createPoint(vertices, colors, coord, colr);

    for (int i = 0; i < nbPointStructure*division; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++)
            vertData.append(colors[i*3+j]);
    }
}

void gl_segment::display(QVector<GLfloat> &vertData){

    if(!isItInit){
        std::cout << "erreur : display gl_segment : vertdataInfo non init" << std::endl;
        return;
    }

    int debut = dataBegin;

    for(int i = 0; i < division; i++){
        glDrawArrays(GL_LINES, debut, nbPointStructure);
        debut += nbPointStructure;
    }
}

double gl_segment::effect(QVector<GLfloat> &vertData, QVector3D currentCoord){
    return 1.0;
}
