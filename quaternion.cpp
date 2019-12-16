#include "quaternion.h"

quaternion::quaternion()
{

}

void quaternion::printQuat(QVector4D quat){
    std::cout << quat[0] << " " << quat[1] << " " << quat[2] << " " << quat[3] << std::endl;
}

QVector4D quaternion::normalizeQuaternion(QVector4D quat){
    double norme = sqrt(pow(quat[0],2) + pow(quat[1],2) + pow(quat[2],2) + pow(quat[3],2));
    return QVector4D(quat[0]/norme, quat[1]/norme, quat[2]/norme, quat[3]/norme);
}

double quaternion::getDot(QVector4D qLeft, QVector4D qRight){
    double dot = qLeft[0] * qRight[0] + qLeft[1] * qRight[1] + qLeft[2] * qRight[2] + qLeft[3] * qRight[3];
    return dot;
}


double quaternion::getAngle(QVector4D qLeft, QVector4D qRight){
    double dot = qLeft[0] * qRight[0] + qLeft[1] * qRight[1] + qLeft[2] * qRight[2] + qLeft[3] * qRight[3];
    return acos(dot);
}

QMatrix4x4 quaternion::quaternionToRotationMatrix(double a, double b, double c, double d){

    QMatrix4x4 newMatrix(a*a + b*b - c*c - d*d, 2*b*c - 2*a*d, 2*a*c + 2*b*d, 0,
                         2*a*d + 2*b*c, a*a - b*b + c*c - d*d, 2*c*d - 2*a*b, 0,
                         2*b*d - 2*a*c, 2*a*b + 2*c*d, a*a - b*b - c*c + d*d, 0,
                         0, 0, 0, 1);
    return newMatrix;
}

QVector4D quaternion::rotationMatrixToQuaternion(QMatrix4x4 matrix){

    float S, X, Y, Z, W;
    double trace = 1 + matrix.data()[0] + matrix.data()[5] + matrix.data()[10];

    if (trace > 0.00000001){
        S = sqrt(trace) * 2;
        X = (matrix.data()[9] - matrix.data()[6]) / S;
        Y = (matrix.data()[2] - matrix.data()[8]) / S;
        Z = (matrix.data()[4] - matrix.data()[1]) / S;
        W = 0.25 * S;
        return QVector4D(X,Y,Z,W);
    }

    if (matrix.data()[0] > matrix.data()[5] && matrix.data()[0] > matrix.data()[10])  {	// colonne 0:
        S  = sqrt( 1.0 + matrix.data()[0] - matrix.data()[5] - matrix.data()[10] ) * 2;
        X = 0.25 * S;
        Y = (matrix.data()[4] + matrix.data()[1]) / S;
        Z = (matrix.data()[2] + matrix.data()[8]) / S;
        W = (matrix.data()[9] - matrix.data()[6]) / S;
    }
    else if (matrix.data()[5] > matrix.data()[10]) {	// colonne 1:
        S = sqrt(1.0 + matrix.data()[5] - matrix.data()[0] - matrix.data()[10]) * 2;
        X = (matrix.data()[4] + matrix.data()[1]) / S;
        Y = 0.25 * S;
        Z = (matrix.data()[9] + matrix.data()[6]) / S;
        W = (matrix.data()[2] - matrix.data()[8]) / S;
    }
    else { // colonne 2:
        S = sqrt(1.0 + matrix.data()[10] - matrix.data()[0] - matrix.data()[5]) * 2;
        X = (matrix.data()[2] + matrix.data()[8]) / S;
        Y = (matrix.data()[9] + matrix.data()[6]) / S;
        Z = 0.25 * S;
        W = (matrix.data()[4] - matrix.data()[1]) / S;
    }

    return QVector4D(X,Y,Z,W);
}


void quaternion::quaternionToAxesAngle(double &angle, double &axeX, double &axeY, double &axeZ, QVector4D quat){

    quat = normalizeQuaternion(quat);
    double cos_a = quat[3];
    angle = acos( cos_a ) * 2;
    angle = angle * 180/M_PI;
    double sin_a = sqrt( 1.0 - cos_a * cos_a );


    if ( fabs( sin_a ) < 0.0005 ) sin_a = 1;

    axeX = quat[0] / sin_a;
    axeY = quat[1] / sin_a;
    axeZ = quat[2] / sin_a;
}


QVector4D quaternion::slerp(QVector4D quat1, QVector4D quat2, double t) {

    quat1 = normalizeQuaternion(quat1);
    quat2 = normalizeQuaternion(quat2);

    double dot = getDot(quat1, quat2);

    if (dot < 0.0f) {
        quat2 = -quat2;
        dot = -dot;
    }

    const double DOT_THRESHOLD = 0.9995;

    if (dot > DOT_THRESHOLD) {
        QVector4D result = quat1 + t*(quat2 - quat1);
        result = normalizeQuaternion(result);
        return result;
    }

    double theta_0 = acos(dot);        // theta_0 = angle entre quat1 et quat2
    double theta = theta_0*t;          // theta = angle entre quat1 et result
    double sin_theta = sin(theta);
    double sin_theta_0 = sin(theta_0);

    double s0 = cos(theta) - dot * sin_theta / sin_theta_0;
    double s1 = sin_theta / sin_theta_0;

    return (s0 * quat1) + (s1 * quat2);
}

//get rotation depuis la matrice position 2 de la caméra
