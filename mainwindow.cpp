#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(-10, 10);
    ui->plot->yAxis->setRange(-10, 10);

    ui->plot->addGraph(); // la droite entre les deux points
    ui->plot->addGraph(); // bresenham

    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 3.0), QBrush(Qt::black), 9));

    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 1.5), QBrush(Qt::red), 9));
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineOnPlot(double x1, double y1, double x2, double y2){

    QVector<double> X{x1,x2};
    QVector<double> Y{y1,y2}; 

    ui->plot->graph(0)->setData(X,Y);
    ui->plot->replot();
}

void MainWindow::resetBresenham(){
    ui->plot->graph(1)->data()->clear();
    etapeMaxBresenham = 0;
    etape = 0;
    prendrePartieVector();
    ui->openGLWidget->setData(etapeMaxBresenham);
    maxBresenham = 0;
    ui->openGLWidget->update();
    ui->plot->replot();
}

void MainWindow::addPixel(QVector<double> &listX, QVector<double> &listY, double x, double y){
    listX.push_back(x);
    listY.push_back(y);
}

void MainWindow::processPartOfBresenham(QVector<double> &listX, QVector<double> &listY, QVector<int> distance,
                                        int &princValue, int &maxPrincValue, int &otherValue, int ID,
                                        bool firstOpe, bool secOpe, bool thirdOpe, int operatorChoose){

    /*  ID : Sélection de la valeur principale "princValue" = 0 -> x ; 1 -> y
     *  Sélection des signes "firstOpe", "secOpe", "thirdOpe" + ou - avec + -> true, - -> false
     *  la valeur principale est celle avec le test while avec sa valeur max (x2 ou y2 si c'est x1 ou y1)
     *  operatorChoose permet de choisir entre "<" (0), "<="(1), ">"(2), ">="(3)
    */

    if(ID < 0 || ID > 1){
        std::cerr << "processPartOfBresenham : ID supérieur à 1 ou inférieur à 0" << std::endl;
        return;
    }

    int err = distance[ID];
    distance[ID] = err * 2;
    distance[1-ID] *= 2;

    etape = 1;

    do{
        switch(ID){
            case 0: addPixel(listX, listY, princValue, otherValue); break;
            case 1: addPixel(listX, listY, otherValue, princValue); break;
            default: std::cerr << "processPartOfBresenham : ID supérieur à 1 ou inférieur à 0" << std::endl; break;
        }
        if(firstOpe) princValue++;
        else         princValue--;

        if(secOpe) err += distance[1-ID];
        else       err -= distance[1-ID];

        bool condition = false;

        switch(operatorChoose){
            case 0: if(err < 0) condition = true; break;
            case 1: if(err <= 0) condition = true; break;
            case 2: if(err > 0) condition = true; break;
            case 3: if(err >= 0) condition = true; break;
            default: std::cerr << "processPartOfBresenham : operatorChoose supérieur à 3 ou inférieur à 0" << std::endl; break;
        }

        if(condition){

            if(thirdOpe) otherValue++;
            else         otherValue--;

            err += distance[ID];
        }
        etape++;

    }while(princValue != maxPrincValue && etape < etapeMaxBresenham);

    std::cout<< "étape : " << etape << std::endl;
    if(etapeMaxBresenham <= 0) return;

    switch(ID){
        case 0: addPixel(listX, listY, princValue, otherValue); break;
        case 1: addPixel(listX, listY, otherValue, princValue); break;
        default: std::cerr << "processPartOfBresenham : ID supérieur à 1 ou inférieur à 0" << std::endl; break;
    }
}

void MainWindow::drawBresenham(int x1, int y1, int x2, int y2){

    listX.clear(), listY.clear();
    int dx = x2 - x1;
    int dy = y2 - y1;

    QVector<int> distance{dx, dy};

    if(dx != 0){
        if(dx > 0){
            if(dy != 0){

                /*########## 1er CADRAN ##########*/
                if(dy > 0){

                    /*########## 1er OCTANT ##########*/
                    if(dx >= dy)
                        processPartOfBresenham(listX, listY, distance, x1, x2, y1, 0, true, false, true, 0);

                    /*########## 2nd OCTANT ##########*/
                    else
                        processPartOfBresenham(listX, listY, distance, y1, y2, x1, 1, true, false, true, 0);

                }

                /*########## 4eme CADRAN ##########*/
                else{

                    /*########## 8eme OCTANT ##########*/
                    if(dx >= -dy)
                        processPartOfBresenham(listX, listY, distance, x1, x2, y1, 0, true, true, false, 0);

                    /*########## 7eme OCTANT ##########*/
                    else
                        processPartOfBresenham(listX, listY, distance, y1, y2, x1, 1, false, true, true, 2);

                }
            }
            /*########## VECTEUR HORIZONTAL ##########*/
            else // dy == 0
                for(; x1 <= x2; x1++){
                    addPixel(listX, listY, x1, y1);
                    etape++;
                }
        }

        else if(dx < 0){
            if(dy != 0){

                /*########## 2eme CADRAN ##########*/
                if(dy > 0){

                    /*########## 4eme OCTANT ##########*/
                    if(-dx >= dy)
                        processPartOfBresenham(listX, listY, distance, x1, x2, y1, 0, false, true, true, 3);

                    /*########## 3eme OCTANT ##########*/
                    else
                        processPartOfBresenham(listX, listY, distance, y1, y2, x1, 1, true, true, false, 1);
                }

                /*########## 3eme CADRAN ##########*/
                else{
                    /*########## 5eme OCTANT ##########*/
                    if(dx <= dy)
                        processPartOfBresenham(listX, listY, distance, x1, x2, y1, 0, false, false, false, 3);

                    /*########## 6eme OCTANT ##########*/
                    else
                        processPartOfBresenham(listX, listY, distance, y1, y2, x1, 1, false, false, false, 3);

                }
            }

            /*########## VECTEUR HORIZONTAL ##########*/
            else //dy == 0
                for(; x1 >= x2; x1--){
                    addPixel(listX, listY, x1, y1);
                    etape++;
                }
        }
    }
    else{ // dx == 0

        if(dy != 0){
        /*########## VECTEUR VERTICAL ##########*/
            if(dy > 0)
                for(; y1 <= y2; y1++){
                    addPixel(listX, listY, x1, y1);
                    etape++;
                }
             else if(dy < 0)
                for(; y1 >= y2; y1--){
                    addPixel(listX, listY, x1, y1);
                    etape++;
                }
        }
    }
    for(int i = 0; i < listX.size(); i++){
        std::cout << "list n°" << i << " listX : "<< listX[i] << " listY : " << listY[i] << std::endl;
    }
}




/* SLOT de Qt */

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    resetBresenham();
    x1 = arg1.toInt();
    ui->openGLWidget->setPoint(0,x1,y1);
}

void MainWindow::on_spinBox_2_valueChanged(const QString &arg1)
{
    resetBresenham();
    y1 = arg1.toInt();
    ui->openGLWidget->setPoint(0,x1,y1);
}

void MainWindow::on_spinBox_3_valueChanged(const QString &arg1)
{
    resetBresenham();
    x2 = arg1.toInt();
    ui->openGLWidget->setPoint(1,x2,y2);
}

void MainWindow::on_spinBox_4_valueChanged(const QString &arg1)
{
    resetBresenham();
    y2 = arg1.toInt();
    ui->openGLWidget->setPoint(1, x2,y2);
}

void MainWindow::on_pushButton_clicked()
{
    drawLineOnPlot(x1, y1, x2, y2);
    ui->openGLWidget->drawSegment();
    resetBresenham();
}

void MainWindow::prendrePartieVector(){
    lY.clear() ; lX.clear();
    for(int i=0; i<etapeMaxBresenham;i++){
        lY.push_back(listY[i]);
        lX.push_back(listX[i]);
    }
}

void MainWindow::on_BresenhamButton_clicked()
{
    drawLineOnPlot(x1, y1, x2, y2);
    resetBresenham();
    etapeMaxBresenham = INT_MAX;
    drawBresenham(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
    etapeMaxBresenham = etape;
    maxBresenham = etape;
    /*
    std::cout << "on bresenham : après draw" << std::endl;
    for(int i = 0; i < listX.size(); i++){
        std::cout << "list n°" << i << " listX : "<< listX[i] << " listY : " << listY[i] << std::endl;
    }*/
    prendrePartieVector();
/*
    std::cout << "on bresenham : après prendrepartie" << std::endl;
    std::cout << "valeur de etapeMaxbresenham " << etapeMaxBresenham << std::endl;
    for(int i = 0; i < lX.size(); i++){
        std::cout << "list n°" << i << " listX : "<< lX[i] << " listY : " << lY[i] << std::endl;
    }*/
    ui->plot->graph(1)->setData(lX,lY);

    ui->openGLWidget->setData(listX, listY, etapeMaxBresenham);

    ui->plot->replot();
    ui->openGLWidget->update();
}

void MainWindow::on_EtapePrec_clicked()
{
    drawLineOnPlot(x1, y1, x2, y2);
    if(etapeMaxBresenham <=0)
        return;

    etapeMaxBresenham--;
    ui->openGLWidget->setData(etapeMaxBresenham);
    prendrePartieVector();
    ui->plot->graph(1)->setData(lX,lY);
    ui->plot->replot();
    ui->openGLWidget->update();
    std::cout << "etapeMax : " << etapeMaxBresenham << std::endl;
}

void MainWindow::on_EtapeSuiv_clicked()
{
    drawLineOnPlot(x1, y1, x2, y2);

    if(maxBresenham <= etapeMaxBresenham)
        return;
    etapeMaxBresenham++;
    ui->openGLWidget->setData(etapeMaxBresenham);
    prendrePartieVector();
    ui->plot->graph(1)->setData(lX,lY);
    ui->plot->replot();
    ui->openGLWidget->update();
    std::cout << "etapeMax : " << etapeMaxBresenham << std::endl;
}

void MainWindow::on_supprBresenham_clicked()
{
    resetBresenham();
}


