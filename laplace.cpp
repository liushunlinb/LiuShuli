#include "laplace.h"

laplace::laplace(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

laplace::~laplace()
{}

void laplace::Process(Mat inputImg)
{
	Mat grad_laplace, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Laplacian(inputImg, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, grad_laplace);
	imwrite("../laplace.jpg", grad_laplace);
	//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../laplace.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}
