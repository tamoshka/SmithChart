#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Smithtry1000.h"
#include <qgraphicsscene.h>
#include <qpainterpath.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Smithtry1000Class; };
QT_END_NAMESPACE

class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public:
    Smithtry1000(QWidget* parent = nullptr);
    ~Smithtry1000();

private:
    Ui::Smithtry1000Class* ui;
    QGraphicsScene* scene;
};
