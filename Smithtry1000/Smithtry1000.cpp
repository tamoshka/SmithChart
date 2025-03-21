#include "Smithtry1000.h"

Smithtry1000::Smithtry1000(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class())
{
    ui->setupUi(this);
    this->resize(1600, 900);
    this->setMaximumSize(1600, 900);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    QPainterPath mainCircle;

    mainCircle.moveTo(200, 200);
    mainCircle.arcTo(-200, 0, 400, 400, 0, 360);

    QPainterPath resistance;
    QPainterPath impendance;
    for (double i = 0; i < 6; i += 1)
    {
        resistance.moveTo(200, 200);
        resistance.arcTo(150 - i * 50, 175 - i * 25, 50 + 50 * i, 50 + 50 * i, 0, 360);
        resistance.arcTo(200 - 25 * pow(2, i), 200 - 50 * pow(2, i), 0 + 50 * pow(2, i), 0 + 50 * pow(2, i), -90, -75.07 * cos(0.5 * i + 0.1) - 92.23);
        resistance.moveTo(200, 200);
        resistance.arcTo(200 - 25 * pow(2, i), 200, 0 + 50 * pow(2, i), 0 + 50 * pow(2, i), 90, 75.07 * cos(0.5 * i + 0.1) + 92.23);
        impendance.moveTo(-150 + 50 * i, 200);
        impendance.arcTo(-200, 175 - 25 * i, 50 + 50 * i, 50 + 50 * i, 0, 360);
        impendance.moveTo(-200, 200);
        impendance.arcTo(-200 - 25 * pow(2, i), 200 - 50 * pow(2, i), 0 + 50 * pow(2, i), 0 + 50 * pow(2, i), 270, 75.07 * cos(0.5 * i + 0.1) + 92.23);
        impendance.moveTo(-200, 200);
        impendance.arcTo(-200 - 25 * pow(2, i), 200, 0 + 50 * pow(2, i), 0 + 50 * pow(2, i), -270, -75.07 * cos(0.5 * i + 0.1) - 92.23);
    }
    resistance.moveTo(200, 200);
    resistance.lineTo(-200, 200);
    /*resistance.arcTo(175, 150, 50, 50, -90, -167.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(175, 200, 50, 50, 90, 167.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(150, 100, 100, 100, -90, -152.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(150, 200, 100, 100, 90, 152.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(100, 0, 200, 200, -90, -127.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(100, 200, 200, 200, 90, 127.5);
    resistance.moveTo(200, 200);
    resistance.arcTo(0, -200, 400, 400, -90, -90);
    resistance.moveTo(200, 200);
    resistance.arcTo(0, 200, 400, 400, 90, 90);
    resistance.moveTo(200, 200);
    resistance.arcTo(-200, -600, 800, 800, -90, -53);
    resistance.moveTo(200, 200);
    resistance.arcTo(-200, 200, 800, 800, 90, 53);
    resistance.moveTo(200, 200);
    resistance.arcTo(-600, -1400, 1600, 1600, -90, -28);
    resistance.moveTo(200, 200);
    resistance.arcTo(-600, 200, 1600, 1600, 90, 28);
    resistance.moveTo(200, 200);
    resistance.lineTo(-200, 200);*/
    /// QPainterPath impendance;
     ///impendance.moveTo(-150, 200);
     ///impendance.arcTo(-200, 175, 50, 50, 0, 360);
     /*impendance.arcTo(-200, 150, 100, 100, 0, 360);
     impendance.arcTo(-200, 125, 150, 150, 0, 360);
     impendance.arcTo(-200, 100, 200, 200, 0, 360);
     impendance.arcTo(-200, 75, 250, 250, 0, 360);
     impendance.arcTo(-200, 50, 300, 300, 0, 360);
     impendance.arcTo(-200, 25, 350, 350, 0, 360);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-225, 150, 50, 50, 270, 167.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-225, 200, 50, 50, -270, -167.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-250, 100, 100, 100, 270, 152.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-250, 200, 100, 100, -270, -152.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-300, 0, 200, 200, 270, 127.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-300, 200, 200, 200, -270, -127.5);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-400, -200, 400, 400, 270, 90);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-400, 200, 400, 400, -270, -90);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-600, -600, 800, 800, 270, 53);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-600, 200, 800, 800, -270, -53);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-1000, -1400, 1600, 1600, 270, 28);
     impendance.moveTo(-200, 200);
     impendance.arcTo(-1000, 200, 1600, 1600, -270, -28);*/
    QPen blackPen;
    blackPen.setColor(Qt::black);
    QPen bluePen;
    bluePen.setColor(Qt::blue);
    QPen redPen;
    redPen.setColor(Qt::red);
    scene->addPath(mainCircle, blackPen);
    scene->addPath(resistance, bluePen);
    scene->addPath(impendance, redPen);
}

Smithtry1000::~Smithtry1000()
{
    delete ui;
}
