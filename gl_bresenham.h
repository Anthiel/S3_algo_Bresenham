#ifndef GL_BRESENHAM_H
#define GL_BRESENHAM_H

#include <QVector>
#include <myglobject.h>
#include <gl_point.h>

class gl_bresenham
{
public:
    gl_bresenham();
    void setData(QVector <double> listX, QVector <double> listY);
    void initBuild(std::vector <myGlObject*> &MyObjects);
    void build(int nbBuild, std::vector <myGlObject*> &MyObjects);

    bool isInit = false;
    QVector <double> dataX, dataY;
    int nombreBase = 100;
    int dataBegin;
};

#endif // GL_BRESENHAM_H
