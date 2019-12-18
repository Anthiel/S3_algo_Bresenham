#ifndef GLAREA_H
#define GLAREA_H

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include "gl_repere.h"
#include "gl_point.h"
#include "gl_segment.h"
#include "gl_bresenham.h"
#include "espaceprojectif.h"
#include "quaternion.h"

class GLArea : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLArea(QWidget *parent = 0);
    ~GLArea() override;

    void setData(QVector<double> listX, QVector<double> listY, int etapeMaxBresenham);
    void setData(int etapeMaxBresenham);
    void setPoint(int ID, int x, int y);
    void drawSegment();
    void processQuaternion();
    void processPositionQuat();
    double degreeToRadian(double angle);

    std::vector <myGlObject*> MyObjects;
    gl_bresenham myBresenham;


public slots:
    void setRadius(double radius);

signals:  // On ne les implémente pas, elles seront générées par MOC ;
          // les paramètres seront passés aux slots connectés.
    void radiusChanged(double newRadius);

protected slots:
    void onTimeout();

protected:
    void initializeGL() override;
    void doProjection();
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;


private:
    double m_angleX = 0;
    double m_angleY = 0;
    double m_angleZ = 0;

    double m_posX = 0;
    double m_posY = 0;
    double m_posZ = 0;
    QPoint lastPos;

    QTimer *m_timer = nullptr;
    double m_radius = 0.5;
    double m_ratio = 1;
    double m_anim = 0;
    QVector<GLfloat> vertData;

    QOpenGLShaderProgram *m_program;

    void makeGLObjects();
    void tearGLObjects();

    QVector3D pointA{0.0, 0.0, 0.0};
    QVector3D pointB{0.0, 0.0, 0.0};

    // quaternion
    double ancienAngleX = 0, ancienAngleY = 0, ancienAngleZ = 0;
    double ancienPosX = 0, ancienPosY = 0, ancienPosZ = 0;

    double quatAngle = 0, quatX = 0, quatY = 0, quatZ = 0;

    bool startQuaternion = false;
    QVector4D quatBegin;
    QVector4D quatEnd;
    QMatrix4x4 savedMatrix;
};

#endif // GLAREA_H
