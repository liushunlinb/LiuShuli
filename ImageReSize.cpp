#include "ImageReSize.h"
#include <QMessageBox>
# pragma execution_character_set("UTF-8")

ImageReSize::ImageReSize(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void ImageReSize::Process(Mat inputImg) {
	image = inputImg.clone();
}

void ImageReSize::on_pushButton_clicked(){
	if (image.empty()) {
		QMessageBox::information(this, "title", "请先选择图片！");
		return;
	}
	if (ui.lineEdit->text().isEmpty() || ui.lineEdit_2->text().isEmpty()) {
		QMessageBox::information(this, "title", "请先输入转换尺寸！");
		return;
	}
	int width = ui.lineEdit->text().toInt();
	int hight = ui.lineEdit_2->text().toInt();
	cv::resize(image, image, Size2d(width, hight));
	imwrite("../transimage.jpg", image);
	QMessageBox::information(this, "title", "转换成功！");
}

ImageReSize::~ImageReSize()
{}
