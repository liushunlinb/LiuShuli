#include "QScrollArea.h"
#include<QScrollBar>
QScrollArea1::QScrollArea1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	ui.listWidget->setFocusPolicy(Qt::NoFocus);
	ui.listWidget->setFrameShape(QFrame::NoFrame);
	a = new myclass(this);
	b = new Binaryvalue(this);
	c = new Canny1(this);
	l = new laplace(this);
	s = new sebel(this);
	g = new Gaussianfilter(this);
	h = new Houghlineartransformation(this);
	hi = new HistogramEqualization(this);
	i = new ImageReSize(this);
	a->setFixedSize(1200, 750);
	ws.push_back(a);
	c->setFixedSize(1200, 750);
	ws.push_back(c);
	l->setFixedSize(1200, 750);
	ws.push_back(l);
	s->setFixedSize(1200, 750);
	ws.push_back(s);
	b->setFixedSize(1200, 750);
	ws.push_back(b);
	g->setFixedSize(1200, 750);
	ws.push_back(g);
	hi->setFixedSize(1200, 750);
	ws.push_back(hi);
	h->setFixedSize(1200, 750);
	ws.push_back(h);
	i->setFixedSize(1200, 200);
	ws.push_back(i);
	QWidget* widget = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(widget);
	for (auto w : ws) {
		layout->addWidget(w);
		layout->addSpacing(15);
	}
	ui.scrollArea->setWidget(widget);
	connect(ui.listWidget, &QListWidget::itemClicked, this, &QScrollArea1::slotItemClicked);
	connect(ui.scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this,&QScrollArea1::slotValueChanged);
	connect(a, &myclass::sig_addStr, [=](Mat sr){
		b->Process(sr);
		c->Process(sr);
		l->Process(sr);
		s->Process(sr);
		g->Process(sr);
		h->Process(sr);
		hi->Process(sr);
		i->Process(sr);
	});
}
void QScrollArea1::slotValueChanged(int value) {
	if (!signFlag) {
		int itemSize = ws.size();
		for (int i = 0; i < itemSize; ++i) {
			if (!ws[i]->visibleRegion().isEmpty()) {
				ui.listWidget->item(i)->setSelected(true);
				return;
			}
			else {
				ui.listWidget->item(i)->setSelected(false);
			}
		}
	}
	signFlag = false;
}
void QScrollArea1::slotItemClicked(QListWidgetItem* item) {
	signFlag = true;
	QString itemText = item->text();
	QPoint widgetPos;
	int size = ws.size();
	int currentrow = ui.listWidget->currentRow();
	widgetPos = ws[currentrow]->pos();
	ui.scrollArea->verticalScrollBar()->setValue(widgetPos.y());
}

QScrollArea1::~QScrollArea1()
{}
