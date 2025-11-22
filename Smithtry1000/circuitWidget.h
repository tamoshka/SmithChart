#pragma once

#include <qpainterpath.h>
#include <QtSvg>
#include <QSvgWidget>
#include "general.h"
#include <QWidget>
#include <QScrollArea>
#include "circuitElements.h"

/// <summary>
/// Класс отображения цепи.
/// </summary>
class CircuitWidget : public QWidget
{
    Q_OBJECT

public:
    CircuitWidget(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
    ~CircuitWidget();
    void addSvg(QString, int, int);
    void removeLastSvg();
private:
    QList<int> tuned;
    QList<QString> paths;
    CircuitElements* circuitElements;
    CircuitElements* tuneElements;
    bool left;
signals:
    void clicked(Element* tuned, QString path);
    void Edit(Element* edit);

public slots:
    void getLeft();
    void RemoveElement(Element*);
    void RemoveAll();
    void Reverse();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
};