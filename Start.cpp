#include "Start.h"

Start::Start(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
	L = new LSLFruitsRecognition(this);
	L->setWindowFlags(L->windowFlags()| Qt::FramelessWindowHint);
	r = new Resigeter(this);
	r->setWindowFlags(r->windowFlags() | Qt::FramelessWindowHint);
	stack = new QStackedWidget(this);
	//stack->setStyleSheet("QStackedWidget {border: none; padding: 0px;}");
	stack->setStyleSheet("QStackedWidget > QWidget { border: none; }");
	stack->setFixedSize(902, 702);
	//stack->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
	stack->addWidget(L);
	stack->addWidget(r);
	//stack->setCurrentIndex(0);
	connect(L, &LSLFruitsRecognition::sig_addIdx, this, [=](int idx) {
		stack->setCurrentIndex(idx);
	});
	connect(r, &Resigeter::sig_addIdx, this, [=](int idx) {
		stack->setCurrentIndex(idx);
	});
	connect(L, &LSLFruitsRecognition::sucess, this, [=]() {
		accept();
	});
}

Start::~Start()
{}
