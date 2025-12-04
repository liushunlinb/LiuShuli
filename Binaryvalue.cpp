#include "Binaryvalue.h"

Binaryvalue::Binaryvalue(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Binaryvalue::Process(Mat inputImg) {
	Mat dst;
	threshold(inputImg, dst, 125, 255, THRESH_BINARY);
	imwrite("../binary.jpg", dst);
	//imshow("../binary.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../binary.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}

Binaryvalue::~Binaryvalue()
{}
