#pragma once

#include <QWidget>
#include "ui_Houghlineartransformation.h"
#include<QPixmap>
#include<opencv2\opencv.hpp>
using namespace cv;

class Houghlineartransformation : public QWidget
{
	Q_OBJECT

public:
	Houghlineartransformation(QWidget *parent = nullptr);
	~Houghlineartransformation();
	void Process(Mat inputImg);

private:
	Ui::HoughlineartransformationClass ui;
	QPixmap* img;
};
