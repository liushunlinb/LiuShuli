#include "LSLFruitsRecognition.h"
#include "Resigeter.h"
#include <QtWidgets/QApplication>
#include "myclass.h"
#include "QScrollArea.h"
#include"Start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
	//Resigeter r;
	if (w.exec() == QDialog::Accepted) {
		QScrollArea1 mainw;
		mainw.show();
		return a.exec();
	}
    return a.exec();
}
