#include "Smithtry1000.h"

Smithtry1000::Smithtry1000(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class()),
    trackingEnabled(false)
{
    ui->setupUi(this);
    this->resize(1600, 900);
    this->setMaximumSize(1600, 900);

    connect(ui->button, &QPushButton::clicked, this, &Smithtry1000::onButtonClicked);
    // ������� ������ ��� ������������ ��������� �������
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10); // ���������� ������ 50 �����������


    /*scene = new QGraphicsScene;
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
    QPen blackPen;
    blackPen.setColor(Qt::black);
    QPen bluePen;
    bluePen.setColor(Qt::blue);
    QPen redPen;
    redPen.setColor(Qt::red);
    scene->addPath(mainCircle, blackPen);
    scene->addPath(resistance, bluePen);
    scene->addPath(impendance, redPen);*/
}

Smithtry1000::~Smithtry1000()
{
    delete ui;
}


void Smithtry1000::onButtonClicked()
{
    // ����������� ��������� ������������
    trackingEnabled = !trackingEnabled;

    // ��������� ����� ������ � ����������� �� ���������
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (trackingEnabled) {
        button->setText("Stop");
    }
    else {
        button->setText("Start");
    }
}


void Smithtry1000::onTimeout()
{
    if (!trackingEnabled) return;  // ���� ������������ ���������, ������ �� ������

    // �������� ������� ������� �������
    QPoint currentPos = QCursor::pos();

    // ������������ �������� ���� �� ����������
    QPoint newPos = getPointOnTrajectory(currentPos);

    // �������� ������� ����
    QRect windowRect = ui->renderArea->rect();

    // �������� ���������� ���������� �������� ������ ���� ����
    QPoint windowGlobalPos = ui->renderArea->mapToGlobal(QPoint(0, 0));

    // ��������� ����� ���������� � ��������� ��� ����
    int newX = newPos.x() - windowGlobalPos.x();
    int newY = newPos.y() - windowGlobalPos.y();

    // ������������ ����� ���������� ������� � �������� ����
    newX = std::max(0, std::min(newX, windowRect.width() - 1));
    newY = std::max(0, std::min(newY, windowRect.height() - 1));

    // ��������� ������� � ���������� ���������� ��� ��������� ������� �������
    QCursor::setPos(windowGlobalPos + QPoint(newX, newY));
}

QPoint Smithtry1000::getPointOnTrajectory(const QPoint& currentPos)
{
    // ������ ����������: ���������, ������������ �������� �� ��� Y
    int x = currentPos.x();
    int y = 200 + 100 * std::sin(x * 0.05);  // �������� �� ������ �������

    // ������������ �������� �� ��� Y
    if (y < 100) y = 100;  // ������ ������� ����������
    if (y > 400) y = 400;  // ������� ������� ����������

    return QPoint(x, y);
}

