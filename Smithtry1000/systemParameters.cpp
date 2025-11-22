#include "systemParameters.h"

QColor SystemParameters::MainCircleColor = QColor(Qt::black);
QColor SystemParameters::ImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::AdmitanceColor = QColor(Qt::red);
QColor SystemParameters::MainImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::MainAdmitanceColor = QColor(Qt::red);
QColor SystemParameters::DataPointsColor = QColor(Qt::magenta);
QColor SystemParameters::RootColor = QColor(Qt::green);
QColor SystemParameters::ElementsColor = QColor(Qt::black);
QColor SystemParameters::BackgroundColor = QColor(Qt::white);
QColor SystemParameters::VSWRColor = QColor(137, 81, 41);
QColor SystemParameters::QCirclesColor = QColor(0, 255, 255);
QColor SystemParameters::ampS11Color = QColor(Qt::blue);
QColor SystemParameters::ampS21Color = QColor(Qt::red);
QColor SystemParameters::s11GrafColor = QColor(Qt::blue);
QColor SystemParameters::s22GrafColor = QColor(Qt::red);
QColor SystemParameters::magGrafColor = QColor(Qt::blue);
QColor SystemParameters::msgGrafColor = QColor(Qt::red);
QColor SystemParameters::kGrafColor = QColor(Qt::green);
QColor SystemParameters::muGrafColor = QColor(Qt::black);
QColor SystemParameters::circleS12 = QColor(Qt::blue);
QColor SystemParameters::circleS21 = QColor(Qt::blue);
QColor SystemParameters::gridGrafOneColor = QColor(Qt::black);
QColor SystemParameters::gridGrafTwoColor = QColor(Qt::black);
QColor SystemParameters::gridAmpFrColor = QColor(Qt::black);
/// <summary>
/// 
/// </summary>
QList<int> SystemParameters::sPlotline = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
/// <summary>
/// 
/// </summary>
QList<int> SystemParameters::ampFrline = { 1,1 };
/// <summary>
/// 0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor, 7 - MainImpedanceColor, 8 - MainAdmitanceColor
/// 9 - VSWRColor, 10 - QCirclesColor
/// </summary>
QList<double> SystemParameters::linesWidth = { 2, 1, 1, 2, 2, 2, 1, 3, 3, 2, 2};
QColor SystemParameters::MainCircleColorDefault = QColor(Qt::black);
QColor SystemParameters::ImpedanceColorDefault = QColor(Qt::blue);
QColor SystemParameters::AdmitanceColorDefault = QColor(Qt::red);
QColor SystemParameters::MainImpedanceColorDefault = QColor(Qt::blue);
QColor SystemParameters::MainAdmitanceColorDefault = QColor(Qt::red);
QColor SystemParameters::DataPointsColorDefault = QColor(Qt::magenta);
QColor SystemParameters::RootColorDefault = QColor(Qt::green);
QColor SystemParameters::ElementsColorDefault = QColor(Qt::black);
QColor SystemParameters::BackgroundColorDefault = QColor(Qt::white);
QColor SystemParameters::VSWRColorDefault = QColor(137, 81, 41);
QColor SystemParameters::QCirclesColorDefault = QColor(0, 255, 255);
QColor SystemParameters::ampS11ColorDefault = QColor(Qt::blue);
QColor SystemParameters::ampS21ColorDefault = QColor(Qt::red);
QColor SystemParameters::s11GrafColorDefault = QColor(Qt::blue);
QColor SystemParameters::s22GrafColorDefault = QColor(Qt::red);
QColor SystemParameters::magGrafColorDefault = QColor(Qt::blue);
QColor SystemParameters::msgGrafColorDefault = QColor(Qt::red);
QColor SystemParameters::kGrafColorDefault = QColor(Qt::green);
QColor SystemParameters::muGrafColorDefault = QColor(Qt::black);
QColor SystemParameters::circleS12Default = QColor(Qt::blue);
QColor SystemParameters::circleS21Default = QColor(Qt::blue);
QColor SystemParameters::gridGrafOneColorDefault = QColor(Qt::black);
QColor SystemParameters::gridGrafTwoColorDefault = QColor(Qt::black);
QColor SystemParameters::gridAmpFrColorDefault = QColor(Qt::black);
/// <summary>
/// 
/// </summary>
QList<int> SystemParameters::sPlotlineDefault = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
/// <summary>
/// 
/// </summary>
QList<int> SystemParameters::ampFrlineDefault = { 1,1,1 };
/// <summary>
/// 0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor, 7 - MainImpedanceColor, 8 - MainAdmitanceColor
/// 9 - VSWRColor, 10 - QCirclesColor
/// </summary>
QList<double> SystemParameters::linesWidthDefault = { 2, 1, 1, 2, 2, 2, 1, 3, 3, 2, 2 };
bool SystemParameters::circuitHover = false;
bool SystemParameters::tune = false;
bool SystemParameters::tuned = false;
bool SystemParameters::tuneBlock = false;
bool SystemParameters::edit = false;
bool SystemParameters::edited = false;
bool SystemParameters::colorChanged = false;
bool SystemParameters::resistorLinear = false;
QList<Element*> SystemParameters::tunedElements = {};
double SystemParameters::er = 1;
long double SystemParameters::z0line = 50;
long double SystemParameters::z0 = 50;
long double SystemParameters::prevz0 = 50;
double SystemParameters::alpha = 0;
double SystemParameters::lambda = 0.25;
bool SystemParameters::sizeChanged = false;
long double SystemParameters::frequency = 500000000;
long double SystemParameters::defaultFrequency = 500000000;
long double SystemParameters::Re = 50;
long double SystemParameters::Im = 0;
systemMode SystemParameters::sys = Impedance;
valueMode SystemParameters::val = Cartesian;
long double SystemParameters::impedanceRealR = 0;
long double SystemParameters::impedanceImagR = 0;
long double SystemParameters::admitanceImagR = 0;
long double SystemParameters::admitanceRealR = 0;
int SystemParameters::saved = 0;
bool SystemParameters::exc = false;
bool SystemParameters::rotate = false;
mode SystemParameters::Model = Default;
long double SystemParameters::scale=200;
long double SystemParameters::lastPointX = 0;
long double SystemParameters::lastPointY = 0;
int SystemParameters::index = 0;
int SystemParameters::allpointindex = 0;
int SystemParameters::dpIndex = 0;

QList<QSvgWidget*> SystemParameters::svgWidgets = {};
/// <summary>
/// Расчёт действительной части сопротивления.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
void SystemParameters::rImpedanceRealCalculation(long double x, long double y)
{
    long double tempy=pow(y,2);
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
        tempy = 0.00000001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
        tempy = 0.00000001;
    }
    long double circleRadius = 1 - ((pow(x, 2) + tempy - 1) / (2 * (x - 1)));
    long double xCenter = 1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    long double sin_t = dy;
    long double cos_t = dx;
    long double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        impedanceRealR = abs((cos(t1) - x) / (x - 1));
    }
    else
    {
        impedanceRealR = 1e9;
    }
    impedanceRealR *= SystemParameters::z0;
}

/// <summary>
/// Расчёт действительной части проводимости.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
void SystemParameters::rAdmitanceRealCalculation(long double x, long double y)
{
    long double tempy = pow(y, 2);
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
        tempy = 0.00000001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
        tempy = 0.00000001;
    }
    long double circleRadius = -1 - ((pow(x, 2) + tempy - 1) / (2 + 2 * x));
    long double xCenter = -1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    dy *= -1;
    long double sin_t = dy;
    long double cos_t = dx;
    long double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x + 1 != 0)
    {
        admitanceRealR = abs((cos(t1) - x) / (x + 1));
    }
    else
    {
        admitanceRealR = 1e9;
    }
    admitanceRealR *= 1000/ SystemParameters::z0;
}

/// <summary>
/// Расчёт мнимой части сопротивления.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
void SystemParameters::rImpedanceImagCalculation(long double x, long double y)
{
    long double cos_t;
    long double sin_t;
    long double tempy = pow(y, 2);
    if (abs(y) >= 0 && abs(y) < 0.0001)
    {
        double denominator = (1 - x) * (1 - x) + y * y;
        impedanceImagR = 2 * y / denominator;
        if (y < 0)
        {
            impedanceImagR = abs(impedanceImagR);
        }
        else if (y>0)
        {
            impedanceImagR = abs(impedanceImagR) * -1;
        }
    }
    else
    {
        long double circleRadius = 1 - ((pow(x, 2) + tempy - 1) / (2 * (x - 1)));
        long double xCenter = 1 - circleRadius;
        long double dx = x - xCenter;
        long double dy = y;
        sin_t = dy;
        cos_t = dx;
        long double t1;
        t1 = atan(cos_t / sin_t);
        if (y < 0)
        {
            t1 += M_PI;
        }
        else
        {
            t1 += 2 * M_PI;
        }
        if (x - 1 != 0)
        {
            impedanceImagR = cos(t1) / (x - 1);
        }
        else
        {
            impedanceImagR = (1 + sin(t1)) / y;
        }
        if (y < 0)
        {
            impedanceImagR = abs(impedanceImagR);
        }
        else
        {
            impedanceImagR = abs(impedanceImagR) * (-1);
        }
        impedanceImagR *= SystemParameters::z0;
    }
}

/// <summary>
/// Расчёт мнимой части проводимости.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
void SystemParameters::rAdmitanceImagCalculation(long double x, long double y)
{
    long double tempy = pow(y, 2);

    if (abs(y)>0&&abs(y)<0.01)
    {
        double denominator = (1 + x) * (1 + x) + y * y;
        admitanceImagR = (-2 * y) / denominator;
    }
    else
    {
        long double cos_t;
        long double sin_t;
        long double circleRadius = (pow(x, 2) + 2 * x + 1 + tempy) / (-2 * y);
        long double yCenter = -circleRadius;
        long double dx = x + 1;
        long double dy = y - yCenter;
        sin_t = -dy;
        cos_t = dx;
        long double t1;
        t1 = atan(sin_t / cos_t);
        if (x + 1 != 0)
        {
            admitanceImagR = cos(t1) / (x + 1);
        }
        else
        {
            admitanceImagR = (1 + sin(t1)) / y;
        }
        if (y > 0)
        {
            admitanceImagR *= -1;
        }
        admitanceImagR *= 1000/-SystemParameters::z0;
    }
    
}

/// <summary>
/// Расчёт Z-параметра.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Z complex.</returns>
Complex SystemParameters::zCalculation(long double x, long double y)
{
    rImpedanceRealCalculation(x, y);
    rImpedanceImagCalculation(x, y);
    return Complex(impedanceRealR, impedanceImagR);
}

/// <summary>
/// Расчёт Y-параметра.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Y complex.</returns>
Complex SystemParameters::yCalculation(long double x, long double y)
{
    rAdmitanceRealCalculation(x, y);
    rAdmitanceImagCalculation(x, y);
    return Complex(admitanceRealR, admitanceImagR);
}

/// <summary>
/// Расчёт параметров действительной части сопротивления для диаграммы.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Параметры для диаграммы.</returns>
Complex SystemParameters::impedanceRealChartParameters(long double x, long double y)
{
    long double tempy = pow(y, 2);
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
        tempy = 0.00000001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
        tempy = 0.00000001;
    }
    long double circleRadius = 1 - ((pow(x, 2) + tempy - 1) / (2 * (x - 1)));
    long double xCenter = 1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    long double sin_t = dy;
    long double cos_t = dx;
    long double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        r1 = (cos(t1) - x) / (x - 1);
    }
    else
    {
        r1 = 1e9;
    }
    return Complex(r1, t1);
}

/// <summary>
/// Расчёт параметров действительной части проводимости для диаграммы.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Параметры для диаграммы.</returns>
Complex SystemParameters::admitanceRealChartParameters(long double x, long double y)
{
    long double tempy = pow(y, 2);
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
        tempy = 0.00000001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
        tempy = 0.00000001;
    }
    long double circleRadius = -1 - ((pow(x, 2) + tempy - 1) / (2 + 2 * x));
    long double xCenter = -1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    dy *= -1;
    long double sin_t = dy;
    long double cos_t = dx;
    long double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x + 1 != 0)
    {
        r1 = abs((cos(t1) - x) / (x + 1));
    }
    else
    {
        r1 = 1e9;
    }
    return Complex(r1, t1);
}

/// <summary>
/// Расчёт параметров мнимой части сопротивления для диаграммы.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Параметры для диаграммы.</returns>
Complex SystemParameters::impedanceImagChartParameters(long double x, long double y)
{
    long double t1, r1;
    long double cos_t;
    long double sin_t;
    long double tempy = pow(y, 2);
    if (abs(y) > 0 && abs(y) < 0.0001)
    {
        double denominator = (1 - x) * (1 - x) + y * y;
        r1 = 2 * y / denominator;
        return Complex(r1, 0);
    }
    long double circleRadius = 1 - ((pow(x, 2) + tempy - 1) / (2 * (x - 1)));
    long double xCenter = 1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    sin_t = dy;
    cos_t = dx;
    t1 = atan(cos_t / sin_t);
    if (y < 0)
    {
        t1 += M_PI;
    }
    else
    {
        t1 += 2 * M_PI;
    }
    if (x - 1 != 0)
    {
        r1 = cos(t1) / (x - 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y < 0)
    {
        r1 = abs(r1);
    }
    else
    {
        r1 = abs(r1) * (-1);
    }
    return Complex(r1, t1);
}

/// <summary>
/// Расчёт параметров мнимой части проводимости для диаграммы.
/// </summary>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
/// <returns>Параметры для диаграммы.</returns>
Complex SystemParameters::admitanceImagChartParameters(long double x, long double y)
{
    long double t1, r1;
    long double cos_t;
    long double sin_t;
    long double tempy = pow(y, 2);
    if (abs(y) > 0 && abs(y) < 0.0001)
    {
        double denominator = (1 + x) * (1 + x) + y * y;
        r1 = (-2 * y) / denominator;
        return Complex(r1, 0);
    }
    long double circleRadius = (pow(x, 2) + 2 * x + 1 + tempy) / (-2 * y);
    long double yCenter = -circleRadius;
    long double dx = x + 1;
    long double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    t1 = atan(sin_t / cos_t);
    if (x + 1 != 0)
    {
        r1 = cos(t1) / (x + 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y > 0)
    {
        r1 *= -1;
    }
    return Complex(r1, t1);
}

/// <summary>
/// Сохранение в JSON параметров цветов и толщины линий.
/// </summary>
void SystemParameters::SaveToJSON()
{
    QJsonObject json;
    QJsonObject colors;
    colors["MainCircleColor"] = colorToString(SystemParameters::MainCircleColor);
    colors["ImpedanceColor"] = colorToString(SystemParameters::ImpedanceColor);
    colors["AdmitanceColor"] = colorToString(SystemParameters::AdmitanceColor);
    colors["MainImpedanceColor"] = colorToString(SystemParameters::MainImpedanceColor);
    colors["MainAdmitanceColor"] = colorToString(SystemParameters::MainAdmitanceColor);
    colors["DataPointsColor"] = colorToString(SystemParameters::DataPointsColor);
    colors["RootColor"] = colorToString(SystemParameters::RootColor);
    colors["ElementsColor"] = colorToString(SystemParameters::ElementsColor);
    colors["BackgroundColor"] = colorToString(SystemParameters::BackgroundColor);
    colors["s11GrafColor"] = colorToString(SystemParameters::s11GrafColor);
    colors["s22GrafColor"] = colorToString(SystemParameters::s22GrafColor);
    colors["magGrafColor"] = colorToString(SystemParameters::magGrafColor);
    colors["msgGrafColor"] = colorToString(SystemParameters::msgGrafColor);
    colors["kGrafColor"] = colorToString(SystemParameters::kGrafColor);
    colors["muGrafColor"] = colorToString(SystemParameters::muGrafColor);
    colors["ampS11Color"] = colorToString(SystemParameters::ampS11Color);
    colors["ampS21Color"] = colorToString(SystemParameters::ampS21Color);
    colors["circleS12"] = colorToString(SystemParameters::circleS12);
    colors["circleS21"] = colorToString(SystemParameters::circleS21);
    colors["gridGrafOneColor"] = colorToString(SystemParameters::gridGrafOneColor);
    colors["gridGrafTwoColor"] = colorToString(SystemParameters::gridGrafTwoColor);
    colors["gridAmpFrColor"] = colorToString(SystemParameters::gridAmpFrColor);
    colors["QCirclesColor"] = colorToString(SystemParameters::QCirclesColor);
    colors["VSWRColor"] = colorToString(SystemParameters::VSWRColor);

    json["colors"] = colors;

    // Сериализация толщины линий
    QJsonArray linesWidthArray;
    for (double width : SystemParameters::linesWidth) {
        linesWidthArray.append(width);
    }
    json["linesWidth"] = linesWidthArray;

    // Сериализация параметров линий графиков
    QJsonArray sPlotlineArray;
    for (int line : SystemParameters::sPlotline) {
        sPlotlineArray.append(line);
    }
    json["sPlotline"] = sPlotlineArray;

    QJsonArray ampFrlineArray;
    for (int line : SystemParameters::ampFrline) {
        ampFrlineArray.append(line);
    }
    json["ampFrline"] = ampFrlineArray;

    json["z0"] = (double)SystemParameters::z0;
    json["rotate"] = SystemParameters::rotate;
    json["defaultFrequency"] = (double)SystemParameters::defaultFrequency;
    QJsonDocument doc(json);
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    dir.mkpath(appDataPath); // Создаем папку если не существует
    QFile file(appDataPath+"/app_settings.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не удалось открыть файл для записи:" << fileName;
    }
    file.write(doc.toJson());
    file.close();
}

/// <summary>
/// Десериализация из JSON параметров цветов и толщин линий.
/// </summary>
void SystemParameters::deserializeFromJson()
{
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    dir.mkpath(appDataPath); // Создаем папку если не существует
    QFile file(appDataPath + "/app_settings.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Не удалось открыть файл для чтения:" << fileName;
    }
    QFileInfo fileInfo(appDataPath + "app_settings.json");
    qDebug() << "Файл существует:" << fileInfo.exists();
    qDebug() << "Размер файла:" << fileInfo.size() << "байт";
    qDebug() << "Можно читать:" << fileInfo.isReadable();
    qDebug() << "Можно писать:" << fileInfo.isWritable();
    qDebug() << "Абсолютный путь:" << fileInfo.absoluteFilePath();
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Ошибка парсинга JSON:" << error.errorString();
    }
    const QJsonObject& json = doc.object();
    try {
        // Десериализация цветов
        if (json.contains("colors") && json["colors"].isObject()) {
            QJsonObject colors = json["colors"].toObject();

            if (colors.contains("MainCircleColor"))
                SystemParameters::MainCircleColor = stringToColor(colors["MainCircleColor"].toString());
            if (colors.contains("ImpedanceColor"))
                SystemParameters::ImpedanceColor = stringToColor(colors["ImpedanceColor"].toString());
            if (colors.contains("AdmitanceColor"))
                SystemParameters::AdmitanceColor = stringToColor(colors["AdmitanceColor"].toString());
            if (colors.contains("MainImpedanceColor"))
                SystemParameters::MainImpedanceColor = stringToColor(colors["MainImpedanceColor"].toString());
            if (colors.contains("MainAdmitanceColor"))
                SystemParameters::MainAdmitanceColor = stringToColor(colors["MainAdmitanceColor"].toString());
            if (colors.contains("DataPointsColor"))
                SystemParameters::DataPointsColor = stringToColor(colors["DataPointsColor"].toString());
            if (colors.contains("RootColor"))
                SystemParameters::RootColor = stringToColor(colors["RootColor"].toString());
            if (colors.contains("ElementsColor"))
                SystemParameters::ElementsColor = stringToColor(colors["ElementsColor"].toString());
            if (colors.contains("BackgroundColor"))
                SystemParameters::BackgroundColor = stringToColor(colors["BackgroundColor"].toString());
            if (colors.contains("s11GrafColor"))
                SystemParameters::s11GrafColor = stringToColor(colors["s11GrafColor"].toString());
            if (colors.contains("s22GrafColor"))
                SystemParameters::s22GrafColor = stringToColor(colors["s22GrafColor"].toString());
            if (colors.contains("magGrafColor"))
                SystemParameters::magGrafColor = stringToColor(colors["magGrafColor"].toString());
            if (colors.contains("msgGrafColor"))
                SystemParameters::msgGrafColor = stringToColor(colors["msgGrafColor"].toString());
            if (colors.contains("kGrafColor"))
                SystemParameters::kGrafColor = stringToColor(colors["kGrafColor"].toString());
            if (colors.contains("muGrafColor"))
                SystemParameters::muGrafColor = stringToColor(colors["muGrafColor"].toString());
            if (colors.contains("ampS11Color"))
                SystemParameters::ampS11Color = stringToColor(colors["ampS11Color"].toString());
            if (colors.contains("ampS21Color"))
                SystemParameters::ampS21Color = stringToColor(colors["ampS21Color"].toString());
            if (colors.contains("circleS12"))
                SystemParameters::circleS12 = stringToColor(colors["circleS12"].toString());
            if (colors.contains("circleS21"))
                SystemParameters::circleS21 = stringToColor(colors["circleS21"].toString());
            if (colors.contains("gridGrafOneColor"))
                SystemParameters::gridGrafOneColor = stringToColor(colors["gridGrafOneColor"].toString());
            if (colors.contains("gridGrafTwoColor"))
                SystemParameters::gridGrafTwoColor = stringToColor(colors["gridGrafTwoColor"].toString());
            if (colors.contains("gridAmpFrColor"))
                SystemParameters::gridAmpFrColor = stringToColor(colors["gridAmpFrColor"].toString());
            if (colors.contains("QCirclesColor"))
                SystemParameters::QCirclesColor = stringToColor(colors["QCirclesColor"].toString());
            if (colors.contains("VSWRColor"))
                SystemParameters::VSWRColor = stringToColor(colors["VSWRColor"].toString());
        }

        // Десериализация толщины линий
        if (json.contains("linesWidth") && json["linesWidth"].isArray()) {
            QJsonArray linesWidthArray = json["linesWidth"].toArray();
            SystemParameters::linesWidth.clear();
            for (const auto& value : linesWidthArray) {
                SystemParameters::linesWidth.append(value.toDouble());
            }
        }

        // Десериализация параметров линий графиков
        if (json.contains("sPlotline") && json["sPlotline"].isArray()) {
            QJsonArray sPlotlineArray = json["sPlotline"].toArray();
            SystemParameters::sPlotline.clear();
            for (const auto& value : sPlotlineArray) {
                SystemParameters::sPlotline.append(value.toInt());
            }
        }

        if (json.contains("ampFrline") && json["ampFrline"].isArray()) {
            QJsonArray ampFrlineArray = json["ampFrline"].toArray();
            SystemParameters::ampFrline.clear();
            for (const auto& value : ampFrlineArray) {
                SystemParameters::ampFrline.append(value.toInt());
            }
        }

        if (json.contains("z0"))
        {
            SystemParameters::z0 = json["z0"].toDouble();
        }

        if (json.contains("defaultFrequency"))
        {
            SystemParameters::defaultFrequency = json["defaultFrequency"].toDouble();
        }

        if (json.contains("rotate"))
        {
            SystemParameters::rotate = json["rotate"].toBool();
        }
    }
    catch (...) {
        qDebug() << "Ошибка при десериализации параметров";
    }
}

/// <summary>
/// Преобразование цвета в String.
/// </summary>
/// <param name="color">Цвет.</param>
/// <returns>Строка.</returns>
QString SystemParameters::colorToString(const QColor& color)
{
    if (color.alpha() == 255) {
        return color.name(); // #RRGGBB
    }
    else {
        return color.name(QColor::HexArgb); // #AARRGGBB
    }
}

/// <summary>
/// Преобразование строки в цвет.
/// </summary>
/// <param name="colorString">Строка.</param>
/// <returns>Цвет.</returns>
QColor SystemParameters::stringToColor(const QString& colorString)
{
    return QColor(colorString);
}