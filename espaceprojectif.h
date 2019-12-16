#ifndef ESPACEPROJECTIF_H
#define ESPACEPROJECTIF_H

#include <QMatrix4x4>
#include <iostream>
#include <cmath>

class espaceProjectif
{
public:
    espaceProjectif();
    static void printMatrix(QMatrix4x4 matrix);
    static QMatrix4x4 identityMatrix4x4();

    static QMatrix4x4 transposeMatrix4x4(QMatrix4x4 matrix);
    static QMatrix4x4 multiplicationMatrix4x4(QMatrix4x4 matrix1, QMatrix4x4 matrix2);

    static void rotation(QMatrix4x4 &matrix, double angle, int x, int y, int z);
    static void scale(QMatrix4x4 &matrix, double x, double y, double z);
    static void translation(QMatrix4x4 &matrix, double x, double y, double z);
};

#endif // ESPACEPROJECTIF_H
