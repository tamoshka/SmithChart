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
    AddPoint
};
extern mode Model;
extern map<int, tuple<QPoint, float, float, mode>> points;
extern QList<QPoint> morePoints;
extern int index;