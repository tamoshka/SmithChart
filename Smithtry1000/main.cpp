#include "Smithtry1000.h"
#include <QtWidgets/QApplication>
#include "general.h"
#include <QThread>
QList<QPoint> morePoints;
int index = 0;
map<int, tuple<QPoint, float, float>> points;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Smithtry1000 w;
    w.show();
    return a.exec();
}
