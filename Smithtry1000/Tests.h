#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tests.h"
#include "S2p.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TestsClass; };
QT_END_NAMESPACE

class Tests : public QMainWindow
{
    Q_OBJECT

public:
    Tests(QWidget *parent = nullptr);
    ~Tests();

private:
    Ui::TestsClass *ui;
};
