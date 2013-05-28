#include "aeciumo.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Aeciumo aeciumo;
	aeciumo.show();
	return app.exec();
}