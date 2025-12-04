#pragma once

#include <QWidget>
#include "ui_QScrollArea.h"
#include <QListWidget>
#include "myclass.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QScrollArea>
#include "Binaryvalue.h"
#include "Canny.h"
#include"laplace.h"
#include "sebel.h"
#include "Gaussianfilter.h"
#include "Houghlineartransformation.h"
#include "HistogramEqualization.h"
#include "ImageReSize.h"
#include<vector>


class QScrollArea1 : public QWidget
{
	Q_OBJECT

public:
	QScrollArea1(QWidget *parent = nullptr);
	~QScrollArea1();

private:
	QListWidget * m_pListWidget = nullptr;
	QScrollArea * m_pLScrollArea = nullptr;
	myclass* a;
	Binaryvalue* b;
	Canny1* c;
	laplace* l;
	sebel* s;
	Gaussianfilter* g;
	Houghlineartransformation* h;
	HistogramEqualization* hi;
	ImageReSize* i;
	vector<QWidget*> ws;
	bool signFlag;
private slots:
	void slotItemClicked(QListWidgetItem* item);
	void slotValueChanged(int value);
private:
	Ui::QScrollAreaClass ui;
};
