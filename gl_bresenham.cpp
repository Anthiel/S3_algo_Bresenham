#include "gl_bresenham.h"

gl_bresenham::gl_bresenham()
{
    nombreBase = 100;
}


void gl_bresenham::setData(QVector <double> listX, QVector <double> listY){

    dataX = listX;
    dataY = listY;
}

void gl_bresenham::initBuild(std::vector <myGlObject*> &MyObjects){

    dataBegin = MyObjects.size();
    for(int i = 0; i < nombreBase; i++)
        MyObjects.push_back(new gl_point({0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, 0.01, false));
    isInit = true;
}

void gl_bresenham::build(int nbBuild, std::vector <myGlObject*> &MyObjects){

    if(!isInit)
        initBuild(MyObjects);

    for(int i = 0; i < nombreBase; i++){
        if(i<dataX.size() && i<dataY.size())
            MyObjects[dataBegin+i]->setPositionPoint({static_cast<float>(dataX[i]/10.0),
                                                      static_cast<float>(dataY[i]/10.0),
                                                      0});

        std::cout << "nombre build : " << nbBuild << std::endl;
        if(i < nbBuild)
            MyObjects[dataBegin+i]->setDisplay(true);
        else MyObjects[dataBegin+i]->setDisplay(false);
    }
}
