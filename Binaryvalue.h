#pragma once

#include <QWidget>
#include "ui_Binaryvalue.h"
#include<opencv2\opencv.hpp>
#include<QPixmap>

using namespace cv;

class Binaryvalue : public QWidget
{
	Q_OBJECT

public:
	Binaryvalue(QWidget *parent = nullptr);
	void Process(Mat inputImg);
	~Binaryvalue();

private:
	Ui::BinaryvalueClass ui;
	QPixmap* img;
};
