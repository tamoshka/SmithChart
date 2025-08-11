#include "GrafOne.h"
#include "S2p.h"
#include <QString>

GrafOne::GrafOne(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::GrafOneClass())
{
	ui->setupUi(this);
}

void GrafOne::Load()
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

	TouchstoneFile t;
	spar_t s;
	ui->widget->clearGraphs();
	s = t.Load2P(fileName.toStdString().c_str());

	x = QVector<double>(s.f.begin(), s.f.end());
	y1 = QVector<double>(s.S11.begin(), s.S11.end());
	y2 = QVector<double>(s.S22.begin(), s.S22.end());
	double m1, m2;
	hX = s.f[s.f.size() - 1] / 4;

	xBegin = 0;
	xEnd = s.f[s.f.size() - 1];
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
		hY = m1 / 5;
		yBegin = m1 * 1.25;
		yEnd = 0;
	}
	else if (m2 < m1)
	{
		hY = m2 / 5;
		yBegin = m2 * 1.25;
		yEnd = 0;
	}
	else
	{
		hY = m1 / 5;
		yBegin = m1 * 1.25;
		yEnd = 0;
	}

	ui->widget->xAxis->setRange(xBegin, xEnd);
	ui->widget->xAxis->setLabel("f[Hz]");
	ui->widget->yAxis->setRange(yBegin, yEnd);
	ui->widget->yAxis->setLabel("[dB]");

	for (xBegin; xBegin <= xEnd; xBegin += hX)
	{
		if (xBegin <= xEnd)
		{
			x;
			y1;
		}
	}

	for (yEnd; yEnd <= yBegin; yEnd += yBegin / 5)
	{
		hY + hY;
		if (hY == yEnd)
		{
			x;
			y2;
		}
	}

	ui->widget->legend->setVisible(true);
	if (extension == "S1P" || extension == "s1p")
	{
		ui->widget->addGraph();
		ui->widget->graph(0)->addData(x, y1);
		ui->widget->graph(0)->setName("Return Loss S11");
	}
	else if (extension == "S2P" || extension == "s2p")
	{
		ui->widget->addGraph();
		ui->widget->graph(0)->addData(x, y1);
		ui->widget->graph(0)->setName("Return Loss S11");
		ui->widget->addGraph();
		ui->widget->graph(1)->setName("Return Loss S22");
		ui->widget->graph(1)->addData(x, y2);
		QPen pen(Qt::red);
		ui->widget->graph(1)->setPen(pen);
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

GrafOne::~GrafOne()
{
	delete ui;
}
