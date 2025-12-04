#pragma once

#include <QWidget>
#include "ui_HistogramEqualization.h"
#include<QPixmap>
#include<opencv2\opencv.hpp>
using namespace cv;


class HistogramEqualization : public QWidget
{
	Q_OBJECT

public:
	HistogramEqualization(QWidget *parent = nullptr);
	~HistogramEqualization();
	void Process(Mat inputImg);

private:
	Ui::HistogramEqualizationClass ui;
	QPixmap* img;
};
