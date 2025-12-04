#include "HistogramEqualization.h"

HistogramEqualization::HistogramEqualization(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void HistogramEqualization::Process(Mat inputImg)
{
	Mat avg, dst;
	cvtColor(inputImg, dst, cv::COLOR_BGR2GRAY);
	equalizeHist(dst, avg);
	imwrite("../Hist.jpg", avg);
		//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../Hist.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}

HistogramEqualization::~HistogramEqualization()
{}
