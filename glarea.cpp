#include "glarea.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


GLArea::GLArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "init GLArea" ;

    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
                        // cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
    setFormat(sf);
    qDebug() << "Depth is"<< format().depthBufferSize();

    setEnabled(true);  // événements clavier et souris
    setFocusPolicy(Qt::StrongFocus); // accepte focus
    setFocus();                      // donne le focus

    m_timer = new QTimer(this);
    m_timer->setInterval(50);  // msec
    connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect (this, SIGNAL(radiusChanged(double)), this, SLOT(setRadius(double)));
}

GLArea::~GLArea()
{
    qDebug() << "destroy GLArea";

    delete m_timer;

    // Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
    // dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
    makeCurrent();
    tearGLObjects();
    doneCurrent();
}


/* ALGOS & FONCTIONS BASIQUES */

void GLArea::setData(QVector<double> listX, QVector<double> listY, int etapeMaxBresenham){
    myBresenham.setData(listX, listY);
    myBresenham.build(etapeMaxBresenham,MyObjects);
    update();
}
void GLArea::setData(int etapeMaxBresenham){
    myBresenham.build(etapeMaxBresenham,MyObjects);
    update();
}

void GLArea::setPoint(int ID, int x, int y){

    QVector3D tmp = QVector3D(x/10.0, y/10.0, 0);
    if(ID < 1){
        pointA = tmp;
        MyObjects[3]->setPositionPoint(pointA);
    }
    else{
        pointB = tmp;
        MyObjects[4]->setPositionPoint(pointB);
    }
    drawSegment();
    update();
}

void GLArea::drawSegment(){
    MyObjects[5]->setPositionPoint(pointA, pointB);
    MyObjects[5]->createGlObject();
}

/* OPENGL AREA */

void GLArea::initializeGL()
{
    qDebug() << __FUNCTION__ ;
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    makeGLObjects();

    // shaders
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);
    if (! m_program->link()) {  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << m_program->log();
    }

    // récupère identifiants de "variables" dans les shaders
    //m_posAttr = m_program->attributeLocation("posAttr");
    //m_colAttr = m_program->attributeLocation("colAttr");
    //m_matrixUniform = m_program->uniformLocation("matrix");
}


void GLArea::makeGLObjects()
{
    //les objets - Reperes
    MyObjects.push_back(new gl_repere(2, {0.0, 0.0, 0.0}, 2, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, true));
    MyObjects.push_back(new gl_repere(2, {0.0, 0.0, 0.0}, 2, {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, true));
    MyObjects.push_back(new gl_repere(2, {0.0, 0.0, 0.0}, 2, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, true));

    //les objets - Point segment
    MyObjects.push_back(new gl_point(pointA, {1.0, 1.0, 0.0}, 0.01, true));
    MyObjects.push_back(new gl_point(pointB, {1.0, 1.0, 0.0}, 0.01, true));

    //les objets - segment
    MyObjects.push_back(new gl_segment(pointA, pointB, {1.0, 1.0, 0.0}, true));

    //les objets - bresenham
    myBresenham.initBuild(MyObjects);

    //création des objets GL
    for(int i = 0; i < MyObjects.size(); i++)
        MyObjects.at(i)->createGlObject();
}


void GLArea::tearGLObjects()
{
    for(auto object : MyObjects)
        object->tearGLObjects();
}


void GLArea::resizeGL(int w, int h)
{
    qDebug() << __FUNCTION__ << w << h;

    // C'est fait par défaut
    glViewport(0, 0, w, h);

    m_ratio = (double) w / h;
    // doProjection();
}

void GLArea::paintGL()
{
    qDebug() << __FUNCTION__ ;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_program->bind(); // active le shader program

    QMatrix4x4 matrix;

    GLfloat hr = m_radius, wr = hr * m_ratio;
    matrix.frustum(-wr, wr, -hr, hr, 1.0, 5.0);

    espaceProj.translation(matrix, 0, 0, -3.0);
    //matrix.translate(0, 0, -3.0);

    // Rotation de la scène pour l'animation
    espaceProj.rotation(matrix, m_angleX*M_PI/180, 1, 0, 0);
    espaceProj.rotation(matrix, m_angleY*M_PI/180, 0, 1, 0);
    espaceProj.rotation(matrix, m_angleZ*M_PI/180, 0, 0, 1);

    //matrix.rotate(static_cast<float>(m_angle), 0, 1, 0);
    //matrix.rotate(static_cast<float>(m_angle), 1, 0, 0);

    m_program->setUniformValue("matrix", matrix);

    //méthode d'affichage (ligne, triangle etc)
    for(int i = 0; i < MyObjects.size(); i++)
        MyObjects.at(i)->display(*m_program);

    m_program->release();
}

void GLArea::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();

    switch(ev->key()) {
        case Qt::Key_Space :
            if (m_timer->isActive())
                m_timer->stop();
            else m_timer->start();
            break;
        //en avant sur X
        case Qt::Key_Z :
            m_angleX += 1;
            if (m_angleX >= 360) m_angleX -= 360;
            update();
            break;
        //en arrière sur X
        case Qt::Key_S :
            m_angleX -= 1;
            if (m_angleX <= 360) m_angleX += 360;
            update();
            break;

        //en avant sur Y
        case Qt::Key_D :
            m_angleY += 1;
            if (m_angleY >= 360) m_angleY -= 360;
            update();
            break;
        //en arrière sur Y
        case Qt::Key_Q :
            m_angleY -= 1;
            if (m_angleY <= 360) m_angleY += 360;
            update();
            break;

        //en avant sur Z
        case Qt::Key_E :
            m_angleZ += 1;
            if (m_angleZ >= 360) m_angleZ -= 360;
            update();
            break;
        //en arrière sur Z
        case Qt::Key_A :
             m_angleZ -= 1;
             if (m_angleZ <= 360) m_angleZ += 360;
             update();
             break;

        case Qt::Key_R :
            if (ev->text() == "r")
                 setRadius(m_radius-0.05);
            else setRadius(m_radius+0.05);
            break;
    }
}

void GLArea::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();
}

void GLArea::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void GLArea::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void GLArea::onTimeout()
{

}

void GLArea::setRadius(double radius)
{
    qDebug() << __FUNCTION__ << radius << sender();
    if (radius != m_radius && radius > 0.01 && radius <= 10) {
        m_radius = radius;
        qDebug() << "  emit radiusChanged()";
        emit radiusChanged(radius);
        update();
    }
}



