#pragma once

#include <QWidget>
#include "ui_ImageReSize.h"
#include<opencv2\opencv.hpp>
using namespace cv;

class ImageReSize : public QWidget
{
	Q_OBJECT

public:
	ImageReSize(QWidget *parent = nullptr);
	~ImageReSize();
	void Process(Mat inputImg);

private slots:
	void on_pushButton_clicked();

private:
	Ui::ImageReSizeClass ui;
	Mat image;
};
