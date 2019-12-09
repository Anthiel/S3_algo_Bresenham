#include "espaceprojectif.h"

espaceProjectif::espaceProjectif()
{

}


void espaceProjectif::printMatrix(QMatrix4x4 matrix){
    for(int row = 0; row < 4 ; row++){
        for(int j = 0; j < 4; j++)
            std::cout << " " << matrix.row(row)[j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

QMatrix4x4 espaceProjectif::transposeMatrix4x4(QMatrix4x4 matrix){

    QMatrix4x4 newMatrix(matrix.column(0)[0], matrix.column(0)[1], matrix.column(0)[2], matrix.column(0)[3],
                         matrix.column(1)[0], matrix.column(1)[1], matrix.column(1)[2], matrix.column(1)[3],
                         matrix.column(2)[0], matrix.column(2)[1], matrix.column(2)[2], matrix.column(2)[3],
                         matrix.column(3)[0], matrix.column(3)[1], matrix.column(3)[2], matrix.column(3)[3]);
    return newMatrix;
}

QMatrix4x4 espaceProjectif::multiplicationMatrix4x4(QMatrix4x4 matrix1, QMatrix4x4 matrix2){

    std::vector<float> resultat;

    for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++){
        resultat.push_back(matrix1.row(i)[0] * matrix2.column(j)[0] +
                           matrix1.row(i)[1] * matrix2.column(j)[1] +
                           matrix1.row(i)[2] * matrix2.column(j)[2] +
                           matrix1.row(i)[3] * matrix2.column(j)[3]);
    }

    QMatrix4x4 res(resultat[0], resultat[1], resultat[2], resultat[3],
                   resultat[4], resultat[5], resultat[6], resultat[7],
                   resultat[8], resultat[9], resultat[10], resultat[11],
                   resultat[12], resultat[13], resultat[14], resultat[15]);
    return res;
}


void espaceProjectif::rotation(QMatrix4x4 &matrix, double angle, int x, int y, int z){

    if(x != 1 && y != 1 && z != 1){
        std::cout << "error espaceProjectif::rotation : paramètres x y et z avec une mauvaise valeure" << std::endl;
        return;
    }

    if(x == 1){
        QMatrix4x4 xMatrix(1, 0, 0, 0,
                           0, static_cast<float>(cos(angle)), static_cast<float>(-sin(angle)), 0,
                           0, static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0,
                           0, 0, 0, 1);
        matrix = multiplicationMatrix4x4(matrix, xMatrix);
    }
    if(y == 1){
        QMatrix4x4 yMatrix(static_cast<float>(cos(angle)), 0, static_cast<float>(sin(angle)), 0,
                           0, 1, 0, 0,
                           static_cast<float>(-sin(angle)), 0, static_cast<float>(cos(angle)), 0,
                           0, 0, 0, 1);
        matrix = multiplicationMatrix4x4(matrix, yMatrix);
    }
    if(z == 1){
        QMatrix4x4 zMatrix(static_cast<float>(cos(angle)), static_cast<float>(-sin(angle)), 0, 0,
                           static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);
        matrix = multiplicationMatrix4x4(matrix, zMatrix);
    }
}


void espaceProjectif::scale(QMatrix4x4 &matrix, double x, double y, double z){
    QMatrix4x4 scaleMatrix(x, 0, 0, 0,
                           0, y, 0, 0,
                           0, 0, z, 0,
                           0, 0, 0, 1);
    matrix = multiplicationMatrix4x4(matrix, scaleMatrix);
}


void espaceProjectif::translation(QMatrix4x4 &matrix, double x, double y, double z){
    QMatrix4x4 translMatrix(1, 0, 0, x,
                            0, 1, 0, y,
                            0, 0, 1, z,
                            0, 0, 0, 1);
    matrix = multiplicationMatrix4x4(matrix, translMatrix);
}
