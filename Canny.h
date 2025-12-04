#pragma once

#include <QWidget>
#include "ui_Canny.h"
#include<QPixmap>
#include<opencv2\opencv.hpp>

using namespace cv;

class Canny1 : public QWidget
{
	Q_OBJECT

public:
	Canny1(QWidget *parent = nullptr);
	~Canny1();
	void Process(Mat inputImg);

private:
	QPixmap* img;
	Ui::CannyClass ui;
};
