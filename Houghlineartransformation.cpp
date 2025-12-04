#include "Houghlineartransformation.h"
#include <vector>
using namespace std;

Houghlineartransformation::Houghlineartransformation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void Houghlineartransformation::Process(Mat inputImg) {
	Mat dst, transform_huofu;
	Canny(inputImg, dst, 50, 200, 3);
	cvtColor(dst, transform_huofu, COLOR_GRAY2BGR);
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(transform_huofu, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	imwrite("../HoughLine.jpg", transform_huofu);
	//imshow("../Canny.jpg", cv::IMREAD_COLOR);
	img = new QPixmap("../HoughLine.jpg");
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
}
Houghlineartransformation::~Houghlineartransformation()
{}
