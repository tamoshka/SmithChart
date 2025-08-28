#include "SDiagram2.h"
#include "ui_SDiagram2.h"
#include "S2p.h"
#include "math.h"
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <QtMath>
#include <QString>

SDiagram2::SDiagram2(ParameterType type, QWidget* parent)
    : QWidget(parent),
    mBackGroundColor(255, 255, 255),
    mShapeColor(0, 0, 0),
    currentType(type)
{
    setFixedSize(600, 600);
    setMinimumSize(450, 450);
    setMaximumSize(900, 900);
    m_cacheValid = false;
    m_scaleFactor = 2.0;
    scaleFactor = qMin(this->width(), this->height()) / 450.0f;
}

void SDiagram2::Load()
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());
    z.clear();
    x.clear();
    y.clear();
    angle.clear();
    max = 0;

    //Выбор для S11,S22
    const auto& sParam = [&]() -> const std::vector<complex_t>&
    {
        switch (currentType)
        {
            case S11: return s.S[0][0];
            case S22: return s.S[1][1];
            default: return s.S[0][0];
        }
    }();

    for (int i = 0; i < sParam.size(); i++)
    {
        z.append(sParam[i].real());
        if (z[i] > max)
        {
            max = z[i];
        }
    }

    for (int i = 0; i < sParam.size(); i++)
    {
        k = z[i] / max;
        z[i] = k;
        angle.append(sParam[i].imag());
        double cosin;
        if (angle[i] > 90)
        {
            cosin = cos((180 - angle[i]) * M_PI / 180);
        }
        else if (angle[i] > 0 && angle[i] <= 90)
        {
            cosin = cos(angle[i] * M_PI / 180);
        }
        else if (angle[i] > -90 && angle[i] <= 0)
        {
            cosin = cos(-angle[i] * M_PI / 180);
        }
        else
        {
            cosin = cos((abs(-180 - angle[i])) * M_PI / 180);
        }
        x.append(cosin * z[i]);
        if (abs(angle[i]) > 90)
        {
            x[i] *= -1;
        }
        y.append(sqrt(pow(z[i], 2) - pow(x[i], 2)));
        if (angle[i] < 0)
        {
            y[i] *= -1;
        }
        y[i] *= -1;
    }
}

QPointF SDiagram2::compute_real(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    float y = (1 / (r + 1)) * sin_t;
    return QPointF(x, y);
}

QPointF SDiagram2::compute_imaginary(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 1 + (1 / r) * cos_t;
    float y = (1 / r) + (1 / r) * sin_t;
    return QPointF(x, y);
}

void SDiagram2::drawStaticObjects(QPainter& painter)
{
    scale = defaultScale * scaleFactor;
    center = this->rect().center();
    painter.setBrush(mBackGroundColor);
    painter.setPen(QPen((mShapeColor, 20)));
    painter.drawRect(this->rect());
    painter.drawLine(QPointF(center.x(), -1000 + center.y()), QPointF(center.x(), 1000 + center.y()));
    painter.drawLine(QPointF(-1000 + center.x(), center.y()), QPointF(1000 + center.x(), center.y()));
    painter.setPen(mShapeColor);
    painter.setPen(Qt::blue);
    float intervalLength = 2 * M_PI;
    int stepCount = 2000;
    float step;
    QPointF iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(Qt::blue);
    double m = 0;
    for (SDiagram2::r = -10; SDiagram2::r <= 10; SDiagram2::r += 0) {
        if (r == -10)
        {
            m = -8;
        }
        if (r == -0.25)
        {
            r = -0.2;
        }
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_imaginary(0);
        iPixel.setX
        (iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step)
        {
            QPointF point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(point.x() * scale + center.x());
            pixel.setY(-point.y() * scale + center.y());
            if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                flagi == false &&
                (
                    (point.y() * scale + center.y() > iPixel.y() + 1) ||
                    (point.y() * scale + center.y() < iPixel.y() - 1)
                    )
                && r > 0
                )
            {
                painter.setPen(QPen(Qt::magenta, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), -point.y() * scale + center.y(), s1);
                painter.setPen(Qt::blue);
                flagi = true;
            }
            painter.setPen(Qt::blue);
            if (pow(point.x(), 2) + pow(point.y(), 2) < 1)
            {
                painter.drawLine(iPixel, pixel);
            }
            iPixel = pixel;
        }
        if (m < 0 && m < -0.25)
        {
            m /= 2;
        }
        else if (m > 0)
        {
            m *= 2;
        }
        else if (m < 0)
        {
            m *= -1;
        }
        r = m;
    }
    double k = 0.125;
    for (SDiagram2::r = 0; SDiagram2::r < 10; SDiagram2::r += 0) {
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_real(0);
        iPixel.setX(iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = 0; t < intervalLength; t += step)
        {
            QPointF point = compute_real(t);
            QPointF pixel;
            pixel.setX(point.x() * scale + center.x());
            pixel.setY(point.y() * scale + center.y());
            if ((floor(point.y() * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(Qt::magenta, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                painter.setPen(Qt::blue);
                flagi == true;
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
        }
        k *= 2;
        r = k;
    }
}

void SDiagram2::generateCache()
{
    QSize scaledSize = size() * m_scaleFactor;
    QImage image(scaledSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter cachePainter(&image);
    cachePainter.setRenderHint(QPainter::Antialiasing, true);
    cachePainter.setRenderHint(QPainter::TextAntialiasing, true);
    cachePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    cachePainter.scale(m_scaleFactor, m_scaleFactor);
    drawStaticObjects(cachePainter);
    m_cache = QPixmap::fromImage(image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_cacheValid = true;
}

void SDiagram2::paintEvent(QPaintEvent* event)
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

    scaleFactor = qMin(this->width(), this->height()) / 450.0f;
    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());

    //Выбор для S11,S22
    const auto& sParam = [&]() -> const std::vector<complex_t>&
    {
        switch (currentType)
        {
            case S11: return s.S[0][0];
            case S22: return s.S[1][1];
            default: return s.S[0][0];
        }
    }();

    QPainter painter(this);
    if (!m_cacheValid || defaultScale != scale) 
    {
        generateCache();
        defaultScale = scale;
    }
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_cache);

    QRectF widgetRect = this->rect();
    QPointF center = widgetRect.center();

    float maxCircleRadius = 200 * scaleFactor;
    QVector<float> radii = { 50, 100, 150, 200 };
    QFont font = painter.font();
    font.setPointSize(8 * scaleFactor);
    painter.setFont(font);

    float pointScale = 3.0f * scaleFactor;
    float lineWidth = 2.0f * scaleFactor;

    painter.setPen(QPen(Qt::red, lineWidth));
    for (int i = 0; i < x.size(); i++) 
    {
        QPointF point = center + QPointF(x[i] * 200 * scaleFactor, y[i] * 200 * scaleFactor);
        painter.drawEllipse(point, pointScale, pointScale);

        if (i > 0) 
        {
            QPointF prevPoint = center + QPointF(x[i - 1] * 200 * scaleFactor, y[i - 1] * 200 * scaleFactor);
            painter.setPen(QPen(Qt::black, lineWidth));
            painter.drawLine(prevPoint, point);
            painter.setPen(QPen(Qt::red, lineWidth));
        }
    }

    if (highlightedPoint >= 0 && highlightedPoint < x.size()) 
    {
        QPointF highlightPoint = center + QPointF(x[highlightedPoint] * 200 * scaleFactor,
            y[highlightedPoint] * 200 * scaleFactor);
        painter.setPen(QPen(Qt::black, lineWidth));
        painter.setBrush(Qt::black);
        painter.drawEllipse(highlightPoint, 3 * scaleFactor, 3 * scaleFactor);

        complex_t sPoint = sParam[highlightedPoint];
        double magnitude = abs(sPoint);
        double phase = arg(sPoint) * 180 / M_PI;

        QString highlightLabel = QString("[%1] S: %2∠%3°")
            .arg(highlightedPoint + 1)
            .arg(sPoint.real(), 0, 'f', 3)
            .arg(sPoint.imag(), 0, 'f', 2);

        QPointF textPos = highlightPoint + QPointF(10 * scaleFactor, -10 * scaleFactor);
        painter.drawText(textPos, highlightLabel);
    }
}


void SDiagram2::highlightPoint(int index)
{
    highlightedPoint = index;
    update();
}


SDiagram2::~SDiagram2()
{
}
