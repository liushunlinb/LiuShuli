#include "Gaussianfilter.h"

Gaussianfilter::Gaussianfilter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void Gaussianfilter::Process(Mat inputImg) {
	Size s = Size(3, 3);
	Mat lvbo_gaosi;
	GaussianBlur(inputImg, lvbo_gaosi, s, 0, 0);
	imwrite("../Gaussianfilter.jpg", lvbo_gaosi);
	//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../Gaussianfilter.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}
Gaussianfilter::~Gaussianfilter()
{}
