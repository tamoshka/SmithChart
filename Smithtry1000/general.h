#pragma once
#include <QList>
#include <QMap>
#include <QPointF>
#include <tuple>
extern enum mode
{
    CapacitorParallel,
    CapacitorShunt,
    ResistorParallel,
    ResistorShunt,
    InductionParallel,
    InductionShunt,
    AddPoint,
    Default
};
extern mode Model;
extern map<int, tuple<QPoint, float, float, mode>> points;
extern QList<QPoint> morePoints;
extern QList<float> qCircles;
extern int index;
extern float impedanceRealR;
extern float impedanceImagR;
extern float admitanceRealR;
extern float admitanceImagR;