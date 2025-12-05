#include "SDiagram2.h"
#include "S2p.h"
#include "math.h"
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <QtMath>
#include <QString>
#include "systemParameters.h"
/// <summary>
/// Конструктор класса SDiagram2.
/// </summary>
/// <param name="type">Тип, S11/S22.</param>
/// <param name="parent"></param>
SDiagram2::SDiagram2(ParameterType type, QWidget* parent)
    : QWidget(parent),
    currentType(type)
{
    m_cacheValid = false;
    scaleFactorX = this->width() / 450.0f;
    scaleFactorY = this->height() / 450.0f;
}

/// <summary>
/// Получение параметров из SnP файла.
/// </summary>
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

/// <summary>
/// Расчёт действительной части сопротивления.
/// </summary>
/// <param name="t">Угол отклонения в радианах.</param>
/// <returns>Точка.</returns>
QPointF SDiagram2::compute_real(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x, y;
    if (r + 1 == 0)
    {
        x = 0;
        y = 0;
    }
    else
    {
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        y = (1 / (r + 1)) * sin_t;
    }
    return QPointF(x, y);
}

/// <summary>
/// Расчёт мнимой части сопротивления.
/// </summary>
/// <param name="t">Угол отклонения в радианах.</param>
/// <returns>Точка.</returns>
QPointF SDiagram2::compute_imaginary(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x, y;
    if (r == 0)
    {
        x = 0;
        y = 0;
    }
    else
    {
        x = 1 + (1 / r) * cos_t;
        y = (1 / r) + (1 / r) * sin_t;
    }
    return QPointF(x, y);
}

/// <summary>
/// Отрисовка статических объектов.
/// </summary>
/// <param name="painter"></param>
void SDiagram2::drawStaticObjects(QPainter& painter)
{
    scale = defaultScale * min(scaleFactorX, scaleFactorY);
    center = this->rect().center();
    painter.setBrush(SystemParameters::BackgroundColor);
    painter.setPen(QPen((QColor(0, 0, 0), 20)));
    painter.drawRect(this->rect());
    painter.drawLine(QPointF(center.x(), -1000 + center.y()), QPointF(center.x(), 1000 + center.y()));
    painter.drawLine(QPointF(-1000 + center.x(), center.y()), QPointF(1000 + center.x(), center.y()));
    painter.setPen(QColor(0, 0, 0));
    painter.setPen(Qt::blue);
    float intervalLength = 2 * M_PI;
    int stepCount = 2000;
    float step;
    QPointF iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(Qt::blue);
    ImpedanceImagLines(step, intervalLength, painter);
    ImpedanceRealLines(step, intervalLength, painter);
    painter.setPen(Qt::red);
    AdmitanceImagLines(step, intervalLength, painter);
    AdmitanceRealLines(step, intervalLength, painter);
    
}

/// <summary>
/// Отрисовка линий мнимого сопротивления.
/// </summary>
/// <param name="step">Шаг.</param>
/// <param name="intervalLength">Интервал.</param>
/// <param name="painter">Объект для рисования.</param>
void SDiagram2::ImpedanceImagLines(long double step, long double intervalLength, QPainter& painter)
{
    QPointF iPoint;
    QPointF iPixel;
    long double m = 0;
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
                QString s1 = QString::number((double)(r * SystemParameters::z0));
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
}

/// <summary>
/// Отрисовка линий реального сопротивления.
/// </summary>
/// <param name="step">Шаг.</param>
/// <param name="intervalLength">Интервал.</param>
/// <param name="painter">Объект для рисования.</param>
void SDiagram2::ImpedanceRealLines(long double step, long double intervalLength, QPainter& painter)
{
    QPointF iPoint;
    QPointF iPixel;
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
                QString s1 = QString::number((double)(r * SystemParameters::z0));
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                painter.setPen(Qt::blue);
                flagi = true;
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
        }
        k *= 2;
        r = k;
    }
}

/// <summary>
/// Отрисовка линий мнимой проводимости.
/// </summary>
/// <param name="step">Шаг.</param>
/// <param name="intervalLength">Интервал.</param>
/// <param name="painter">Объект для рисования.</param>
void SDiagram2::AdmitanceImagLines(long double step, long double intervalLength, QPainter& painter)
{
    QPointF iPoint;
    QPointF iPixel;
    painter.setPen(QPen(SystemParameters::AdmitanceColor, SystemParameters::linesWidth[2] * 0.5));
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
        (-iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step)
        {
            QPointF point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(-point.x() * scale + center.x());
            pixel.setY(-point.y() * scale + center.y());
            if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                flagi == false &&
                r < 0 &&
                (
                    (point.y() * scale + center.y() > iPixel.y() + 1) ||
                    (point.y() * scale + center.y() < iPixel.y() - 1)
                    )
                )
            {
                painter.setPen(QPen(Qt::green, 2));
                QString s1 = QString::number((double)(r * 1000 / -SystemParameters::z0));
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x() + 10, -point.y() * scale + center.y() - 10, s1);
                painter.setPen(Qt::red);
                flagi = true;
            }
            painter.setPen(Qt::red);
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
}

/// <summary>
/// Отрисовка линий реальной проводимости.
/// </summary>
/// <param name="step">Шаг.</param>
/// <param name="intervalLength">Интервал.</param>
/// <param name="painter">Объект для рисования.</param>
void SDiagram2::AdmitanceRealLines(long double step, long double intervalLength, QPainter& painter)
{
    QPointF iPoint;
    QPointF iPixel;
    double k = 0.25;
    for (SDiagram2::r = 0.25; SDiagram2::r < 10; SDiagram2::r += 0) {
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_real(0);
        iPixel.setX(-iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = 0; t < intervalLength; t += step)
        {
            QPointF point = compute_real(t);
            QPointF pixel;
            pixel.setX(-point.x() * scale + center.x());
            pixel.setY(point.y() * scale + center.y());

            if ((floor(point.y() * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(Qt::green, 2));
                QString s1 = QString::number((double)(r * 1000 / SystemParameters::z0));
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x(), center.y() + 10, s1);
                painter.setPen(Qt::red);
                flagi = true;
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
        }
        k *= 2;
        r = k;
    }
}

/// <summary>
/// Генерация кэша статических объектов.
/// </summary>
void SDiagram2::generateCache()
{
    QSize scaledSize = size() * 2;
    QImage image(scaledSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter cachePainter(&image);
    cachePainter.setRenderHint(QPainter::Antialiasing, true);
    cachePainter.setRenderHint(QPainter::TextAntialiasing, true);
    cachePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    cachePainter.scale(2, 2);
    drawStaticObjects(cachePainter);
    m_cache = QPixmap::fromImage(image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_cacheValid = true;
}

/// <summary>
/// Отрисовка виджета.
/// </summary>
/// <param name="event"></param>
void SDiagram2::paintEvent(QPaintEvent* event)
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

    scaleFactorX = this->width() / 450.0f;
    scaleFactorY = this->height() / 450.0f;
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

    float maxCircleRadius = 200 * min(scaleFactorX, scaleFactorY);
    QVector<float> radii = { 50, 100, 150, 200 };
    QFont font = painter.font();
    font.setPointSize(8 * min(scaleFactorX, scaleFactorY));
    painter.setFont(font);

    float pointScale = 3.0f * min(scaleFactorX, scaleFactorY);
    float lineWidth = 2.0f * min(scaleFactorX, scaleFactorY);

    painter.setPen(QPen(Qt::red, lineWidth));
    for (int i = 0; i < x.size(); i++) 
    {
        QPointF point = center + QPointF(x[i] * 200 * scaleFactorX, y[i] * 200 * scaleFactorY);
        painter.drawEllipse(point, pointScale, pointScale);

        if (i > 0) 
        {
            QPointF prevPoint = center + QPointF(x[i - 1] * 200 * scaleFactorX, y[i - 1] * 200 * scaleFactorY);
            painter.setPen(QPen(Qt::black, lineWidth));
            painter.drawLine(prevPoint, point);
            painter.setPen(QPen(Qt::red, lineWidth));
        }
    }

    if (highlightedPoint >= 0 && highlightedPoint < x.size()) 
    {
        QPointF highlightPoint = center + QPointF(x[highlightedPoint] * 200 * scaleFactorX,
            y[highlightedPoint] * 200 * scaleFactorY);
        painter.setPen(QPen(Qt::black, lineWidth));
        painter.setBrush(Qt::black);
        painter.drawEllipse(highlightPoint, 3 * scaleFactorX, 3 * scaleFactorY);

        complex_t sPoint = sParam[highlightedPoint];
        double magnitude = abs(sPoint);
        double phase = arg(sPoint) * 180 / M_PI;

        QString highlightLabel = QString("[%1] S: %2∠%3°")
            .arg(highlightedPoint + 1)
            .arg(sPoint.real(), 0, 'f', 3)
            .arg(sPoint.imag(), 0, 'f', 2);

        QPointF textPos = highlightPoint + QPointF(10 * scaleFactorX, -10 * scaleFactorY);
        painter.drawText(textPos, highlightLabel);
    }
}

/// <summary>
/// Отображение подсвечиваемой точки.
/// </summary>
/// <param name="index">Номер точки.</param>
void SDiagram2::highlightPoint(int index)
{
    highlightedPoint = index;
    update();
}

/// <summary>
/// Деструктор класса SDiagram2.
/// </summary>
SDiagram2::~SDiagram2()
{
}