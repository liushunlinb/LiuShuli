#pragma once

#include <QWidget>
#include "ui_Gaussianfilter.h"
#include<QPixmap>
#include<opencv2\opencv.hpp>

using namespace cv;

class Gaussianfilter : public QWidget
{
	Q_OBJECT

public:
	Gaussianfilter(QWidget *parent = nullptr);
	~Gaussianfilter();
	void Process(Mat inputImg);

private:
	Ui::GaussianfilterClass ui;
	QPixmap* img;
};
