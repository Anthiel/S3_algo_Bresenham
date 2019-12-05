#ifndef ESPACEPROJECTIF_H
#define ESPACEPROJECTIF_H

#include <QMatrix4x4>
#include <iostream>
#include <cmath>

class espaceProjectif
{
public:
    espaceProjectif();
    void printMatrix(QMatrix4x4 matrix);

    QMatrix4x4 transposeMatrix4x4(QMatrix4x4 matrix);
    QMatrix4x4 multiplicationMatrix4x4(QMatrix4x4 matrix1, QMatrix4x4 matrix2);

    void rotation(QMatrix4x4 &matrix, double angle, int x, int y, int z);
    void translation(QMatrix4x4 &matrix, double x, double y, double z);
};

#endif // ESPACEPROJECTIF_H
