#include "GrafOne.h"
#include "newgeneral.h"
#include "S2p.h"

string get_extension3(string path) {

	size_t last_slash = path.find_last_of("/\\");
	string filename;
	if (last_slash != string::npos) {
		filename = path.substr(last_slash + 1);
	}
	else {
		filename = path;
	}

	size_t last_dot = filename.find_last_of('.');

	if (last_dot != string::npos && last_dot != 0) {
		return filename.substr(last_dot + 1);
	}

	return "";
}

GrafOne::GrafOne(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GrafOneClass())
{
	ui->setupUi(this);
	TouchstoneFile t;
	spar_t s;
	
	s = t.Load2P(fileName.toStdString().c_str());

	x = QVector<double>(s.f.begin(), s.f.end());
	y1 = QVector<double>(s.S11.begin(), s.S11.end());
	y2 = QVector<double>(s.S22.begin(), s.S22.end());
	double m1,m2;
	hX = s.f[s.f.size() - 1] /4;
	
	xBegin = 0;
	xEnd = s.f[s.f.size() - 1];
	m1 = y1[0];
	m2 = y2[0];
	for (int j = 0;j < s.S11.size()-1;j++)
	{
		if (y1[j+1] < m1)
		{
			m1 = y1[j+1];
		}
	}
	for (int j = 0;j < s.S22.size()-1;j++)
	{
		if (y2[j+1] < m2)
		{
			m2 = y2[j+1];
		}
	}
	if ( get_extension3(fileName.toStdString()) == "S1P" || get_extension3(fileName.toStdString()) == "s1p")
	{
		hY = m1 / 5;
		yBegin = m1 * 1.25;
		yEnd = 0;
	}
	else if (m2<m1)
	{
		hY = m2 / 5;
		yBegin = m2*1.25;
		yEnd = 0;
	}
	else
	{
		hY = m1 / 5;
		yBegin = m1*1.25;
		yEnd = 0;
	}

	ui->widget->xAxis->setRange(xBegin, xEnd);
	ui->widget->xAxis->setLabel("f[Hz]");
	ui->widget->yAxis->setRange(yBegin, yEnd);
	ui->widget->yAxis->setLabel("[dB]");
	
	for (xBegin; xBegin <= xEnd;xBegin += hX)
	{
		if (xBegin <= xEnd)
		{
			x;
			y1;
		}
	}

	for (yEnd; yEnd <= yBegin;yEnd += yBegin / 5)
	{
		hY+ hY;
		if (hY== yEnd)
		{
			x;
			y2;
		}
	}
	
	ui->widget->legend->setVisible(true);
	ui->widget->addGraph();
	ui->widget->graph(0)->addData(x, y1);
	ui->widget->graph(0)->setName("Return Loss S11");
	ui->widget->addGraph();
	ui->widget->graph(1)->setName("Return Loss S22");
	ui->widget->graph(1)->addData(x, y2);
	QPen pen(Qt::red);
	ui->widget->graph(1)->setPen(pen);

	ui->widget->replot();
	ui->widget->setInteraction(QCP::iRangeZoom, true);
	ui->widget->setInteraction(QCP::iRangeDrag, true);


}

GrafOne::~GrafOne()
{
	delete ui;
}
