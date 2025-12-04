#pragma once
#include <QMainWindow>
#include <stdio.h>
#include <fstream>
#include<opencv2\opencv.hpp>
#include "ui_myclass.h"
using namespace cv;
using namespace std;
using namespace dnn;
class myclass : public QMainWindow
{
	Q_OBJECT
public:
	myclass(QWidget *parent = nullptr);
	~myclass();
private:
	Ui::myclassClass ui;
private:
	void judgeOnnx(Mat img);

private slots:
	void Tagselection(int idx);

private slots:
	void choiceModel(int idx);

private slots:
	void openImg();

signals:
	void sig_addStr(Mat srcImage);
private:
	const char *path = "D:\\log.txt";
	bool vidoOpened = false;
	Net net;
	vector<String> layerNames;
	Mat srcImage, srcVadio;
	vector<String> typeList;
	String selectModel;
	QPixmap *img;
};

