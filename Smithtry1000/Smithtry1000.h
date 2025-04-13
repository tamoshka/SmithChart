#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Smithtry1000.h"
#include <qgraphicsscene.h>
#include <qpainterpath.h>
#include <QtSvg>

QT_BEGIN_NAMESPACE
namespace Ui { class Smithtry1000Class; };
QT_END_NAMESPACE

class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public:
    bool trackingEnabled;
    Smithtry1000(QWidget* parent = nullptr);
    ~Smithtry1000();

private:

    QPoint getPointOnTrajectory(const QPoint& currentPos);
    void onTimeout();
    Ui::Smithtry1000Class* ui;
    QGraphicsScene* scene;
private slots:
    void onButtonClicked();  // Обработчик нажатия кнопки
};
