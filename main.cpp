#include "aeciumo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Aeciumo aeciumo;
	aeciumo.show();
	return app.exec();
}
