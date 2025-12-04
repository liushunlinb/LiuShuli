#pragma once

#include <QWidget>
#include "ui_sebel.h"
#include <opencv2\opencv.hpp>
#include <QPixmap>
using namespace cv;

class sebel : public QWidget
{
	Q_OBJECT

public:
	sebel(QWidget *parent = nullptr);
	~sebel();
	void Process(Mat inputImg);



private:
	Ui::sebelClass ui;
	QPixmap* img;
};
