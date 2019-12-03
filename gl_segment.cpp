#include "gl_segment.h"

gl_segment::gl_segment(QVector3D pos, QVector3D posSuiv, QVector3D color)
{
    posInit = pos;
    posNext = posSuiv;
    colr = color;
}

void gl_segment::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}

void gl_segment::createGlObject(){

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

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

/*
void gl_segment::display(){

    std::cout << "size vertdata : " << vertData.size() << " size max : " << division*nbPointStructure << std::endl;

    for(int debut = 0; debut < division*nbPointStructure; debut+=nbPointStructure)
        glDrawArrays(GL_LINES, debut, nbPointStructure);
}
*/

void gl_segment::display(QOpenGLShaderProgram &m_program){

    m_vbo.bind();
    m_program.setAttributeBuffer("posAttr",
        GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program.setAttributeBuffer("colAttr",
        GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    m_program.enableAttributeArray("posAttr");
    m_program.enableAttributeArray("colAttr");

    int debut = 0;

    for(int i = 0; i < division; i++){
        glDrawArrays(GL_LINES, debut, nbPointStructure);
        debut += nbPointStructure;
    }
    m_program.disableAttributeArray("posAttr");
    m_program.disableAttributeArray("colAttr");
    m_vbo.release();
}

void gl_segment::tearGLObjects()
{
    m_vbo.destroy();
}
