#include "systemParameters.h"

QColor SystemParameters::MainCircleColor = QColor(Qt::black);
QColor SystemParameters::ImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::AdmitanceColor = QColor(Qt::red);
QColor SystemParameters::DataPointsColor = QColor(Qt::magenta);
QColor SystemParameters::RootColor = QColor(Qt::green);
QColor SystemParameters::ElementsColor = QColor(Qt::black);
QColor SystemParameters::BackgroundColor = QColor(Qt::white);
QList<double> SystemParameters::linesWidth = { 2, 0.5, 0.5, 2, 2, 2, 1 };
bool SystemParameters::circuitHover = false;
bool SystemParameters::tune = false;
bool SystemParameters::tuned = false;
bool SystemParameters::tuneBlock = false;
QList<Element*> SystemParameters::tunedElements = {};
double SystemParameters::er = 1;
double SystemParameters::z0line = 50;