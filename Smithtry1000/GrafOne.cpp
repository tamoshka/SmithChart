#include "GrafOne.h"
#include "S2p.h"
#include <QString>
#include "systemParameters.h"
/// <summary>
/// Конструктор класса GrafOne.
/// </summary>
/// <param name="parent"></param>
GrafOne::GrafOne(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::GrafOneClass())
{
	ui->setupUi(this);
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void GrafOne::Load()
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";
	connect(ui->SaveGrafOne,&QPushButton::clicked, this, &GrafOne::SaveGrafOne);
	TouchstoneFile t;
	spar_t s;
	ui->widget->clearGraphs();
	s = t.Load2P(fileName.toStdString().c_str());

	x.resize(s.f.size());
	for (int i = 0; i < s.f.size(); i++) {
		x[i] = s.f[i];
	}
	y1.resize(s.S11.size());
	for (int i = 0; i < s.S11.size(); i++) {
		y1[i] = s.S11[i];
	}
	y2.resize(s.S22.size());
	for (int i = 0; i < s.S22.size(); i++) {
		y2[i] = s.S22[i];
	}
	double m1, m2;
	double yBegin, yEnd;
	m1 = y1[0];
	m2 = y2[0];
	for (int j = 0; j < s.S11.size() - 1; j++)
	{
		if (y1[j + 1] < m1)
		{
			m1 = y1[j + 1];
		}
	}
	for (int j = 0; j < s.S22.size() - 1; j++)
	{
		if (y2[j + 1] < m2)
		{
			m2 = y2[j + 1];
		}
	}
	if (extension == "S1P" || extension == "s1p")
	{
		yBegin = m1 * 1.25;
		yEnd = 0;
	}
	else if (m2 < m1)
	{
		yBegin = m2 * 1.25;
		yEnd = 0;
	}
	else
	{
		yBegin = m1 * 1.25;
		yEnd = 0;
	}
	Paint(extension, yBegin, yEnd, s);
}

void GrafOne::Paint(string extension, double yBegin, double yEnd, spar_t s)
{

	ui->widget->xAxis->setRange(0, s.f[s.f.size() - 1]);
	ui->widget->xAxis->setLabel("f[Hz]");
	ui->widget->yAxis->setRange(yBegin, yEnd);
	ui->widget->yAxis->setLabel("[dB]");

	ui->widget->legend->setVisible(true);
	if (extension == "S1P" || extension == "s1p")
	{

		ui->widget->addGraph();
		QPen penGid(SystemParameters::gridGrafOneColor, SystemParameters::sPlotline[9], Qt::DotLine);
		QPen pen1(SystemParameters::s11GrafColor, SystemParameters::sPlotline[6]);
		ui->widget->graph(0)->setPen(pen1);
		ui->widget->xAxis->grid()->setPen(penGid);
		ui->widget->yAxis->grid()->setPen(penGid);
		ui->widget->graph(0)->addData(x, y1);
		ui->widget->graph(0)->setName("Return Loss S11");
	}
	else if (extension == "S2P" || extension == "s2p")
	{
		ui->widget->addGraph();
		QPen penGid(SystemParameters::gridGrafOneColor, SystemParameters::sPlotline[9], Qt::DotLine);
		QPen pen1(SystemParameters::s11GrafColor, SystemParameters::sPlotline[6]);
		ui->widget->graph(0)->setPen(pen1);
		ui->widget->xAxis->grid()->setPen(penGid);
		ui->widget->yAxis->grid()->setPen(penGid);
		ui->widget->graph(0)->addData(x, y1);
		ui->widget->graph(0)->setName("Return Loss S11");
		ui->widget->addGraph();
		ui->widget->graph(1)->setName("Return Loss S22");
		ui->widget->graph(1)->addData(x, y2);
		QPen pen2(SystemParameters::s22GrafColor, SystemParameters::sPlotline[7]);
		ui->widget->graph(1)->setPen(pen2);
	}

	ui->widget->replot();
	ui->widget->setInteraction(QCP::iRangeZoom, true);
	ui->widget->setInteraction(QCP::iRangeDrag, true);

	GraphS11 = ui->widget->addGraph();
	GraphS11->setLineStyle(QCPGraph::lsNone);
	GraphS11->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	GraphS11->removeFromLegend();

	GraphS22 = ui->widget->addGraph();
	GraphS22->setLineStyle(QCPGraph::lsNone);
	GraphS22->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	GraphS22->removeFromLegend();
}

/// <summary>
/// Обновление цвета на виджете.
/// </summary>
void GrafOne::updateGrafOneColor()
{
	if (fileName != "")
	{
		this->Load();
		this->update();
	}
}

/// <summary>
/// Сохранение изображения виджета.
/// </summary>
void GrafOne::SaveGrafOne()
{
	QString fileName = QFileDialog::getSaveFileName(this,"Save the graph",QDir::homePath() + "/graph.png","PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)");

	if (!fileName.isEmpty()) 
	{
		bool success = false;

		if (fileName.endsWith(".png", Qt::CaseInsensitive)) 
		{
			success = ui->widget->savePng(fileName,ui->widget->width() * 2,ui->widget->height() * 2,2.0);
		}
		else if (fileName.endsWith(".jpg", Qt::CaseInsensitive)) 
		{
			success = ui->widget->saveJpg(fileName, ui->widget->width(), ui->widget->height());
		}
		else if (fileName.endsWith(".pdf", Qt::CaseInsensitive))
		{
			success = ui->widget->savePdf(fileName);
		}

		if (success) 
		{
			QMessageBox::information(this, "Success",QString("The graph is saved to a file:\n%1").arg(fileName));
		}
		else 
		{
			QMessageBox::warning(this, "Error", "Couldn't save graph!");
		}
	}
}

/// <summary>
/// Выбор подсвечиваемой точки.
/// </summary>
/// <param name="index">Номер точки.</param>
void GrafOne::highlightPoint(int index)
{
	if (index >= 0 && index < x.size())
	{
		QVector<double> highlightX = { x[index] };
		QVector<double> highlightY1 = { y1[index] };
		QVector<double> highlightY2 = { y2[index] };

		GraphS11->setData(highlightX, highlightY1);
		GraphS22->setData(highlightX, highlightY2);

		ui->widget->replot();
	}
}

/// <summary>
/// Деструктор класса GrafOne.
/// </summary>
GrafOne::~GrafOne()
{
	delete ui;
}