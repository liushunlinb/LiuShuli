#pragma once

#include <QDialog>
#include "LSLFruitsRecognition.h"
#include "Resigeter.h"
#include<QStackedWidget>

class Start : public QDialog
{
	Q_OBJECT

public:
	Start(QWidget *parent = nullptr);
	~Start();

private:
	LSLFruitsRecognition* L;
	Resigeter* r;
	QStackedWidget* stack;
};
