#include "gl_repere.h"

gl_repere::gl_repere(int nbPoint, QVector3D pos, double l, QVector3D ax, QVector3D color)
{
    nbPointControl = nbPoint;
    posInit = pos-(l/2.0)*ax;
    longueur = l;
    axe = ax;
    colr = color;
}

void gl_repere::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}

void gl_repere::createGlObject(){

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

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}


void gl_repere::display(QOpenGLShaderProgram &m_program){

    m_vbo.bind();
    m_program.setAttributeBuffer("posAttr",
        GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program.setAttributeBuffer("colAttr",
        GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    m_program.enableAttributeArray("posAttr");
    m_program.enableAttributeArray("colAttr");

    for(int debut = 0; debut <= divisionAxe*nbPointStructure; debut+=nbPointStructure)
        glDrawArrays(GL_LINE_STRIP, debut, nbPointStructure);

    m_program.disableAttributeArray("posAttr");
    m_program.disableAttributeArray("colAttr");
    m_vbo.release();
}

void gl_repere::tearGLObjects()
{
    m_vbo.destroy();
}
