#pragma once

#include <QDialog>
#include "ui_Resigeter.h"
#include<string>
#include<mysql.h>
using namespace std;

typedef struct user {
	string user_phone;
	string user_pwd;
	string user_name;
	string user_email;
};

class Resigeter : public QDialog
{
	Q_OBJECT

public:
	Resigeter(QWidget *parent = nullptr);
	~Resigeter();
	bool insert_user(user &t);
	user get_user(string condition = " ");
	bool ok = false;
private slots:
	void on_btnresigter_clicked();
	void on_pushButton_clicked();
signals:
	void sig_addIdx(int idx);
private:
	Ui::ResigeterClass ui;
	MYSQL* con;
};
