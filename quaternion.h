#ifndef QUATERNION_H
#define QUATERNION_H

#include <QMatrix4x4>
#include <iostream>
#include <cmath>


class quaternion
{
public:
    quaternion();
    static void printQuat(QVector4D quat);
    static QVector4D normalizeQuaternion(QVector4D quat);
    static double getDot(QVector4D qLeft, QVector4D qRight);
    static double getAngle(QVector4D qLeft, QVector4D qRight);
    static QMatrix4x4 quaternionToRotationMatrix(double a, double b, double c, double d);
    static QVector4D rotationMatrixToQuaternion(QMatrix4x4 matrix);
    static void quaternionToAxesAngle(double &angle, double &axeX, double &axeY, double &axeZ, QVector4D quat);
    static QVector4D slerp(QVector4D quat1, QVector4D quat2, double t);
};

#endif // QUATERNION_H
