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
    m_timer->start();
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

void GLArea::processQuaternion(){

    QMatrix4x4 matrixRotation = espaceProjectif::identityMatrix4x4();
    espaceProjectif::rotation(matrixRotation, (degreeToRadian(m_angleX) - degreeToRadian(ancienAngleX)), 1, 0, 0);
    espaceProjectif::rotation(matrixRotation, (degreeToRadian(m_angleY) - degreeToRadian(ancienAngleY)), 0, 1, 0);
    espaceProjectif::rotation(matrixRotation, (degreeToRadian(m_angleZ) - degreeToRadian(ancienAngleZ)), 0, 0, 1);
    quatBegin = quaternion::rotationMatrixToQuaternion(matrixRotation);

    matrixRotation = espaceProjectif::identityMatrix4x4();
    quatEnd = quaternion::rotationMatrixToQuaternion(matrixRotation);

    m_anim = 0;
    startQuaternion = true;
    update();
}

void GLArea::processPositionQuat(){
    ancienAngleX = m_angleX;
    ancienAngleY = m_angleY;
    ancienAngleZ = m_angleZ;

    ancienPosX = m_posX;
    ancienPosY = m_posY;
    ancienPosZ = m_posZ;
}

double GLArea::degreeToRadian(double angle){
    return angle*M_PI/180;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind(); // active le shader program

    QMatrix4x4 matrix;

    GLfloat hr = m_radius, wr = hr * m_ratio;
    matrix.frustum(-wr, wr, -hr, hr, 1.0, 10.0);

    espaceProjectif::translation(matrix, 0, 0, -3.0);

    //mouvement dans la scène avec la souris
    espaceProjectif::translation(matrix, m_posX, m_posY, m_posZ);

    // Rotation de la scène pour l'animation avec ZQSD AE
    espaceProjectif::rotation(matrix, degreeToRadian(m_angleX), 1, 0, 0);
    espaceProjectif::rotation(matrix, degreeToRadian(m_angleY), 0, 1, 0);
    espaceProjectif::rotation(matrix, degreeToRadian(m_angleZ), 0, 0, 1);

    //quaternion
    if(startQuaternion){
        QVector4D quatPosition = quaternion::slerp(quatBegin, quatEnd, m_anim);
        quaternion::quaternionToAxesAngle(quatAngle, quatX, quatY, quatZ, quatPosition);
        espaceProjectif::translation(matrix, (ancienPosX-m_posX)*(1.0-m_anim), (ancienPosY-m_posY)*(1.0-m_anim), (ancienPosZ-m_posZ)*(1.0-m_anim));
        matrix.rotate(quatAngle, quatX, quatY, quatZ);

        if(m_anim >= 1)
            startQuaternion = false;
    }

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


void GLArea::onTimeout()
{
    if (m_anim >= 1) m_anim = 0;
    m_anim += 0.01;
    update();
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

void GLArea::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();
}


void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
}

void GLArea::wheelEvent(QWheelEvent *ev){
    m_posZ += static_cast<float>(ev->delta() * 1.0/100.0);
    update();
}

void GLArea::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}


void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::LeftButton) {
        m_angleX += dy;
        m_angleY += dx;
        update();
    } else if (ev->buttons() & Qt::RightButton) {
        m_posX += dx/10.0f;
        m_posY -= dy/10.0f;
        update();
    } else if (ev->buttons() & Qt::MidButton) {
        m_posX += dx/10.0f;
        m_posY += dy;
        update();
    }

    lastPos = ev->pos();
}



