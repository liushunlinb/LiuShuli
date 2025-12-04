#include "Canny.h"

Canny1::Canny1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void Canny1::Process(Mat inputImg)
{
	Mat gray;
	cvtColor(inputImg, gray, cv::COLOR_BGR2GRAY);
	// 2. 高斯模糊（可选，但推荐用于降噪）
	GaussianBlur(gray, gray, cv::Size(5, 5), 1.4);
	// 3. 应用Canny边缘检测
	Mat edges;
	Canny(gray, edges, 50, 150);  // 低阈值50，高阈值150
	imwrite("../Canny.jpg", edges);
	//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../Canny.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}
Canny1::~Canny1()
{}
