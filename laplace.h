#pragma once

#include <QWidget>
#include "ui_laplace.h"
#include<QPixmap>
#include<opencv2\opencv.hpp>

using namespace cv;

class laplace : public QWidget
{
	Q_OBJECT

public:
	laplace(QWidget *parent = nullptr);
	~laplace();
	void Process(Mat inputImg);

private:
	Ui::laplaceClass ui;
	QPixmap* img;
};
