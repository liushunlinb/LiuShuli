#include "sebel.h"

sebel::sebel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void sebel::Process(Mat inputImg) {
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat grad_sebel;
	/// 求 X方向梯度
	Sobel(inputImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	/// 求Y方向梯度
	Sobel(inputImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	/// 合并梯度(近似)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad_sebel);
	imwrite("../sebel.jpg", grad_sebel);
	//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../sebel.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}

sebel::~sebel()
{}
