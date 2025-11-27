#include "GrafTwo.h"
#include <QMessageBox>
#include <QtMath>
#include <QThread>
#include <cmath>
#include <exception>
#include "ui_GrafTwo.h"
#include <QString>
#include "S2p.h"
#include "ColourSetting.h"
#include "systemParameters.h"
/// <summary>
/// Конструктор класса GrafTwo.
/// </summary>
/// <param name="parent"></param>
GrafTwo::GrafTwo(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::GrafTwoClass())
{
	ui->setupUi(this);
}


/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void GrafTwo::Load()
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";
	connect(ui->SaveGrafTwo, &QPushButton::clicked, this, &GrafTwo::SaveGrafTwo);
	TouchstoneFile t;
	spar_t s;
	s = t.Load2P(fileName.toStdString().c_str());
	ui->widget->clearGraphs();
	
	x.resize(s.f.size());
	for (int i = 0; i < s.f.size(); i++) {
		x[i] = s.f[i];
	}
	y1.resize(s.Mg.size());
	for (int i = 0; i < s.Mg.size(); i++) {
		y1[i] = s.Mg[i];
	}
	y2.resize(s.Ms.size());
	for (int i = 0; i < s.Ms.size(); i++) {
		y2[i] = s.Ms[i];
	}
	y3.resize(s.Mk.size());
	for (int i = 0; i < s.Mk.size(); i++) {
		y3[i] = s.Mk[i];
	}
	y4.resize(s.Mu.size());
	for (int i = 0; i < s.Mu.size(); i++) {
		y4[i] = s.Mu[i];
	}

	double m1, m2, m3, m4;
	m1 = y1[0];
	m2 = y2[0];
	m3 = y3[0];
	m4 = y4[0];
	double yBegin, yEnd;
	for (int j = 0; j < s.Mg.size() - 1; j++)
	{
		if (y1[j + 1] > m1)
		{
			m1 = y1[j + 1];
		}
	}
	for (int j = 0; j < s.Ms.size() - 1; j++)
	{
		if (y2[j + 1] > m2)
		{
			m2 = y2[j + 1];
		}
	}

	if (m2 < m1)
	{
		yBegin = m1;
		yEnd = 0;
	}
	else
	{
		yBegin = m2;
		yEnd = 0;
	}


	ui->widget->xAxis->setRange(0, s.f[s.f.size() - 1]);
	ui->widget->xAxis->setLabel("f[Hz]");
	ui->widget->yAxis->setRange(yBegin, yEnd);
	ui->widget->yAxis->setLabel("[dB]");
	ui->widget->yAxis2->setRange(yBegin / 10, yEnd / 10);
	ui->widget->yAxis2->setLabel("[K,μ]");

	for (int i = 0; i < x.size() - 1; i++)
	{
		if (y1[i] == 0)
		{
			y1[i] = qQNaN();
		}
		if (y2[i] == 0)
		{
			y2[i] = qQNaN();
		}
	}
	Paint();
}

void GrafTwo::Paint()
{
	ui->widget->legend->setVisible(true);
	QPen pen1(SystemParameters::magGrafColor, SystemParameters::sPlotline[2]);
	QPen penGid(SystemParameters::gridGrafTwoColor, SystemParameters::sPlotline[8], Qt::DotLine);
	ui->widget->xAxis->grid()->setPen(penGid);
	ui->widget->yAxis->grid()->setPen(penGid);
	ui->widget->yAxis2->grid()->setPen(penGid);
	ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
	ui->widget->graph(0)->setPen(pen1);
	ui->widget->graph(0)->setName("MAG");
	ui->widget->graph(0)->addData(x, y1);
	QPen pen2(SystemParameters::msgGrafColor, SystemParameters::sPlotline[3]);
	ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
	ui->widget->graph(1)->setPen(pen2);
	ui->widget->graph(1)->setName("MSG");
	ui->widget->graph(1)->addData(x, y2);
	QPen pen3(SystemParameters::kGrafColor, SystemParameters::sPlotline[4]);
	ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis2);
	ui->widget->graph(2)->setPen(pen3);
	ui->widget->graph(2)->setName("K");
	ui->widget->graph(2)->addData(x, y3);
	QPen pen4(SystemParameters::muGrafColor, SystemParameters::sPlotline[5]);
	ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis2);
	ui->widget->graph(3)->setPen(pen4);
	ui->widget->graph(3)->setName("μ");
	ui->widget->graph(3)->addData(x, y4);
	ui->widget->yAxis2->setVisible(true);

	ui->widget->replot();


	ui->widget->setInteraction(QCP::iRangeZoom, true);
	ui->widget->setInteraction(QCP::iRangeDrag, true);
	QList<QCPAxis*> axises;
	axises.append(ui->widget->xAxis);
	axises.append(ui->widget->yAxis);
	axises.append(ui->widget->yAxis2);
	ui->widget->axisRect()->setRangeDragAxes(axises);
	ui->widget->axisRect()->setRangeZoomAxes(axises);

	GraphK = ui->widget->addGraph();
	GraphK->setLineStyle(QCPGraph::lsNone);
	GraphK->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	GraphK->removeFromLegend();

	Graphu = ui->widget->addGraph();
	Graphu->setLineStyle(QCPGraph::lsNone);
	Graphu->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	Graphu->removeFromLegend();

	GraphMAG = ui->widget->addGraph();
	GraphMAG->setLineStyle(QCPGraph::lsNone);
	GraphMAG->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	GraphMAG->removeFromLegend();

	GraphMSG = ui->widget->addGraph();
	GraphMSG->setLineStyle(QCPGraph::lsNone);
	GraphMSG->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
	GraphMSG->removeFromLegend();

	GraphMAG->setValueAxis(ui->widget->yAxis);
	GraphMSG->setValueAxis(ui->widget->yAxis);
	GraphK->setValueAxis(ui->widget->yAxis2);
	Graphu->setValueAxis(ui->widget->yAxis2);
}

/// <summary>
/// Изменение цвета на виджете.
/// </summary>
void GrafTwo::updateGrafTwoColor()
{
	if (fileName != "")
	{
		this->Load();
		this->update();
	}
}

/// <summary>
/// Сохранение виджета в изображение.
/// </summary>
void GrafTwo::SaveGrafTwo()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save the graph", QDir::homePath() + "/graph.png", "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)");

	if (!fileName.isEmpty())
	{
		bool success = false;

		if (fileName.endsWith(".png", Qt::CaseInsensitive))
		{
			success = ui->widget->savePng(fileName, ui->widget->width() * 2, ui->widget->height() * 2, 2.0);
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
			QMessageBox::information(this, "Success", QString("The graph is saved to a file:\n%1").arg(fileName));
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
void GrafTwo::highlightPoint(int index)
{
	if (index >= 0 && index < x.size())
	{
		QVector<double> highlightX = { x[index] };

		GraphMAG->setData(highlightX, QVector<double>{y1[index]});
		GraphMSG->setData(highlightX, QVector<double>{y2[index]});
		GraphK->setData(highlightX, QVector<double>{y3[index]});
		Graphu->setData(highlightX, QVector<double>{y4[index]});

		ui->widget->replot();
	}
}

/// <summary>
/// Деструктор класса GrafTwo.
/// </summary>
GrafTwo::~GrafTwo()
{
	delete ui;
}