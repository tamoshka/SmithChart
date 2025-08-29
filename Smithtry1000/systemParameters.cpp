#include "systemParameters.h"

QColor SystemParameters::MainCircleColor = QColor(Qt::black);
QColor SystemParameters::ImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::AdmitanceColor = QColor(Qt::red);
QColor SystemParameters::DataPointsColor = QColor(Qt::magenta);
QColor SystemParameters::RootColor = QColor(Qt::green);
QColor SystemParameters::ElementsColor = QColor(Qt::black);
QColor SystemParameters::BackgroundColor = QColor(Qt::white);
QColor SystemParameters::ampS11Color = QColor(Qt::blue);
QColor SystemParameters::ampS21Color = QColor(Qt::red);
QColor SystemParameters::s11GrafColor = QColor(Qt::blue);
QColor SystemParameters::s22GrafColor = QColor(Qt::red);
QColor SystemParameters::magGrafColor = QColor(Qt::blue);
QColor SystemParameters::msgGrafColor = QColor(Qt::red);
QColor SystemParameters::kGrafColor = QColor(Qt::green);
QColor SystemParameters::muGrafColor = QColor(Qt::black);
QColor SystemParameters::circleS12 = QColor(Qt::blue);
QColor SystemParameters::circleS21 = QColor(Qt::blue);

QList<double> SystemParameters::linesWidth = { 2, 0.5, 0.5, 2, 2, 2, 1 };
bool SystemParameters::circuitHover = false;
bool SystemParameters::tune = false;
bool SystemParameters::tuned = false;
bool SystemParameters::tuneBlock = false;
bool SystemParameters::colorChanged = false;
QList<Element*> SystemParameters::tunedElements = {};
double SystemParameters::er = 1;
double SystemParameters::z0line = 50;
double SystemParameters::alpha = 0;
double SystemParameters::lambda = 0.25;
bool SystemParameters::sizeChanged = false;