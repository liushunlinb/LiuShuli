#include "LSLFruitsRecognition.h"
#include<QMessageBox>
# pragma execution_character_set("UTF-8")

LSLFruitsRecognition::LSLFruitsRecognition(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
	//初始化mysql  
	con = mysql_init(NULL);
	//返回false则连接失败，返回true则连接成功  
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
	if (!(mysql_real_connect(con, "127.0.0.1", "root", "root", "username", 3306, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
	{
		QMessageBox::information(this, "title", mysql_error(con));
	}
	else {
		QMessageBox::information(this, "title", "数据库连接成功！");
	}

	stack = new QStackedWidget();
	//r = new Resigeter();
	stack->addWidget(this);
	//stack->addWidget(r);
	stack->setCurrentIndex(2);
}

LSLFruitsRecognition::~LSLFruitsRecognition()
{	
	delete stack;
}

void LSLFruitsRecognition::on_btnLogo_clicked() {

	string phone = ui.lineID->text().toStdString();
	string pwd = ui.lineEdit_pwd->text().toStdString();
	string username = ui.lineEdit_username->text().toStdString();
	if (phone.size() != 11) {
		QMessageBox::information(this, "title", "请输入正确电话号码！");
		return ;
	}
	if (pwd.empty()) {
		QMessageBox::information(this, "title", "请输入密码！");
		return;
	}
	if (username.empty()) {
		QMessageBox::information(this, "title", "请输入昵称！");
		return;
	}
	user now = get_user(phone);
	if (now.user_phone.empty()) {
		QMessageBox::information(this, "title", "请先注册！");
		return;
	}
	if (now.user_phone == phone && now.user_pwd == pwd && now.user_name == username) {
		emit sucess();
	}
	else if (now.user_pwd != pwd) {
		QMessageBox::information(this, "title", "请输入正确密码！");
		return;
	}
	else if (now.user_name != username) {
		QMessageBox::information(this, "title", "请输入正确昵称！");
		return;
	}
}

user LSLFruitsRecognition::get_user(string condition)
{
	user stu;
	char sql[1024];
	sprintf(sql, "select * from username where user_phone = %s", condition.c_str());
	if (mysql_query(con, sql)) {
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row==NULL) {
		return {};
	}
	stu.user_phone = row[0];
	stu.user_pwd = row[1];
	stu.user_name = row[2];
	return stu;
}

void LSLFruitsRecognition::on_btnresigter_clicked()
{
	emit sig_addIdx(1);
}
