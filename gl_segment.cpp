#include "gl_segment.h"

gl_segment::gl_segment(QVector3D pos, QVector3D posSuiv, QVector3D color)
{
    posInit = pos;
    colr = color;
    hauteur = h;
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

    //face du bas
    QVector3D coord(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    //face du haut
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);

    //face du gauche
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    //face du droite
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    //face du devant
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] + hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    //face du derriere
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] + hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] + hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);
    coord = QVector3D(posInit[0] - hauteur, posInit[1] - hauteur, posInit[2] - hauteur);
    createPoint(vertices, colors, coord, colr);

    for (int i = 0; i < 3*division; ++i) {
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
        std::cout << "erreur : display gl_repere : vertdataInfo non init" << std::endl;
        return;
    }

    int debut = dataBegin;

    for(int i = 0; i < division; i++){
        glDrawArrays(GL_TRIANGLES, debut, 3);
        debut += 3;
    }
}

double gl_segment::effect(int coordID, int currentCoord){

    return 1;
}
