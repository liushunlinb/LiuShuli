#include "myclass.h"
#include<QSettings>
#include<QStandardPaths>
#include<QMessageBox>
#include<QComboBox>
#include<QFileDialog>
# pragma execution_character_set("UTF-8")

myclass::myclass(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label_2->setText("识别结果");
	ui.plainTextEdit->appendHtml("<h1>请先选择模型和标签</h1>");
	ui.textEdit->setText("输入图片名");
	ui.pushButton_4->setText("打开图片");
	//this->setStyleSheet("background-color:rgb(125,125,50)");
	//connect(ui->button, &QPushButton::clicked, this, &Widget::on_button_clicked);
	//connect(ui.pushButton, &QPushButton::clicked, this, &myclass::choiceModel);
	//connect(ui.pushButton_3, &QPushButton::clicked, this, &myclass::Tagselection);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &myclass::openImg);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(choiceModel(int)));
	connect(ui.comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(Tagselection(int)));
}

myclass::~myclass()
{

}

///标签选择
void myclass::Tagselection(int idx)
{
	QString config_path = qApp->applicationDirPath() + "/config/path/Setting.ini";
	//ui.plainTextEdit->appendHtml(config_path);
	unique_ptr<QSettings> qIniSet(new QSettings(config_path, QSettings::IniFormat));
	QString LastPath = qIniSet->value("/LabelLastPath/path").toString();
	if (LastPath.isEmpty()) {
		ui.plainTextEdit->appendHtml("空的");
		LastPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
	}
	QString fileName;// = QFileDialog::getOpenFileName(this, "请打开图片", LastPath, "图片(*.txt);;");
	if (idx == 1) {
		fileName = LastPath + "/fruits_lables_chinese.txt";
	}
	else if(idx == 2){
		fileName = LastPath + "/fruits_lables.txt";
	}
	else {
		return ;
	}
	ifstream file(fileName.toStdString());
	if (!file.is_open()) {
		cout << "请确认分类种类名称是否正确" << endl;
		return;
	}
	String type;
	int a = 0;
	while (getline(file, type)) {
		if (!type.empty()) {
			typeList.push_back(type);
			a++;
			ui.plainTextEdit->appendPlainText(QString(type.c_str()));
		}
	}
	file.close();
	ui.plainTextEdit->appendHtml(QString("标签路径: ") + LastPath);
	ui.plainTextEdit->appendPlainText(QString("标签已经加载完成，总共可识别") + QString().number(a) + QString("种类型"));
	layerNames = net.getLayerNames();
	int end = fileName.lastIndexOf("/");
	qIniSet->setValue("/LabelLastPath/path", fileName.left(end));
}

//图片打开功能
void myclass::openImg()
{
	if (net.empty()) {
		QMessageBox::information(this, "title", "请先选择模型和标签！");
		return;
	}
	else if (typeList.empty()) {
		QMessageBox::information(this, "title", "请先选择模型对应标签！");
		return;
	}
	QString config_path = qApp->applicationDirPath() + "/config/path/Setting.ini";
	//ui.plainTextEdit->appendHtml(config_path);
	unique_ptr<QSettings> qIniSet(new QSettings(config_path, QSettings::IniFormat));
	QString LastPath = qIniSet->value("/LastPath/path").toString();
	if (LastPath.isEmpty()) {
		ui.plainTextEdit->appendHtml("空的");
		LastPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
	}
	//ui.plainTextEdit->appendHtml(LastPath);
	QString fileName = QFileDialog::getOpenFileName(this, "请打开图片", LastPath, "图片(*.png *.jpg);;");
	ui.textEdit->setText(fileName);
	String imgSrc = ui.textEdit->toPlainText().toStdString();
	srcImage = imread(fileName.toStdString());
	if (srcImage.empty()) {
		cout << "图像加载失败！！" << endl;
		return;
	}
	img = new QPixmap(fileName);
	img->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*img);
	int end = fileName.lastIndexOf("/");
	qIniSet->setValue("/LastPath/path", fileName.left(end));
	Mat judgeimg = srcImage;
	judgeOnnx(judgeimg);
	emit sig_addStr(srcImage);
}

//选择模型
void myclass::choiceModel(int idx)
{
	QString config_path = qApp->applicationDirPath() + "/config/path/Setting.ini";
	//ui.plainTextEdit->appendHtml(config_path);
	unique_ptr<QSettings> qIniSet(new QSettings(config_path, QSettings::IniFormat));
	QString LastPath = qIniSet->value("/ModelLastPath/path").toString();
	if (LastPath.isEmpty()) {
		ui.plainTextEdit->appendHtml("空的");
		LastPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
	}
	//QString fileName;//= QFileDialog::getOpenFileName(this, "请打开图片", LastPath, "图片(*.onnx);;");
	//ui.textEdit->setText(fileName);
	QString fileName;// = QFileDialog::getOpenFileName(this, "请打开图片", LastPath, "图片(*.txt);;");
	if (idx == 1) {
		fileName = LastPath + "/fruits_19.onnx";
	}
	else if(idx == 2){
		fileName = LastPath + "/fruits1_8.onnx";
	}
	else {
		this->net = dnn::Net();
		return ;
	}
	this->net = dnn::readNetFromONNX(fileName.toStdString());
	if (net.empty()) {
		cout << "网络加载失败！！" << endl;
	}
	typeList.clear();
	layerNames = net.getLayerNames();
	ui.plainTextEdit->appendHtml(QString("模型路径: ") + LastPath);
	int end = fileName.lastIndexOf("/");
	qIniSet->setValue("/ModelLastPath/path", fileName.left(end));
}

Mat imageToTensor(const Mat& imageRGB) {
	// 1. 转换颜色空间 BGR → RGB
	Mat image;
	cv::cvtColor(imageRGB, image, cv::COLOR_BGR2RGB);
	// 2. 转换为浮点型并归一化到 [0, 1]
	image.convertTo(image, CV_32FC3, 1.0 / 255.0);
	// 定义均值和标准差
	cv::Scalar mean(0.485, 0.456, 0.406); // RGB通道的均值
	cv::Scalar std(0.229, 0.224, 0.225);  // RGB通道的标准差
	// 3. 减去均值
	cv::subtract(image, mean, image);
	// 4. 除以标准差
	cv::divide(image, std, image);
	return image;
}

void myclass::judgeOnnx(Mat img)
{
	Mat img1 = imageToTensor(img);
	//Mat img2 = convertToTensor(img);
	Mat blob = blobFromImage(img1, 1.0f, Size(224, 224), Scalar(), false, false);
	net.setInput(blob);  // 确保输入层名称正确
	Mat prob = net.forward();  // 确保输出层名称正确
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;
	double classProb;
	minMaxLoc(probMat, nullptr, &classProb, nullptr, &classNumber);
	if (classNumber.x >= 0 && classNumber.x < typeList.size()) {
		string typeName = typeList[classNumber.x];
		ui.label_2->setText(QString(typeName.c_str()));
		ui.label_2->setScaledContents(true);
	}
}
