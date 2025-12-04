#pragma once

#include <QtWidgets/QDialog>
#include "ui_LSLFruitsRecognition.h"
#include "Resigeter.h"
#include <mysql.h>
#include<string>
#include <vector>
#include<QStackedWidget>


bool ConnectDatabase();
bool QueryDatabase1();

class LSLFruitsRecognition : public QDialog
{
    Q_OBJECT

public:
    LSLFruitsRecognition(QWidget *parent = nullptr);
    ~LSLFruitsRecognition();
	bool insert_user(user &t);
	user get_user(string condition = " ");

private slots:
	void on_btnLogo_clicked();
	void on_btnresigter_clicked();

signals:
	void sig_addIdx(int idx);
	void sucess();
private:
	MYSQL *con;
    Ui::LSLFruitsRecognitionClass ui;
	QStackedWidget* stack;
	Resigeter* r;
};
