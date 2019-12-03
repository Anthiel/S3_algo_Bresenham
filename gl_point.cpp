#include "gl_point.h"

gl_point::gl_point(QVector3D pos, QVector3D color, double h)
{
    posInit = pos;
    colr = color;
    hauteur = h;
}


void gl_point::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}

void gl_point::createGlObject(){

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

    for (int i = 0; i < nbPointStructure*division; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++)
            vertData.append(colors[i*3+j]);
    }
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}
/*
void gl_point::display(){
    for(int debut = 0; debut < division*nbPointStructure; debut+=nbPointStructure)
        glDrawArrays(GL_TRIANGLES, debut, nbPointStructure);
}
*/
void gl_point::display(){

    m_vbo.bind();

    int debut = 0;

    for(int i = 0; i < division; i++){
        glDrawArrays(GL_TRIANGLES, debut, nbPointStructure);
        debut += 3;
    }
    m_vbo.release();
}


void gl_point::tearGLObjects()
{
    m_vbo.destroy();
}
