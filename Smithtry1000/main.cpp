#include "Smithtry1000.h"
#include <QtWidgets/QApplication>
#include "general.h"
#include <QThread>
class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
};

QVector<QPointF> points(4);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Smithtry1000 w;
    w.show();
    return a.exec();
}
