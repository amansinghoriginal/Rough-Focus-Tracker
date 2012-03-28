#include <QCoreApplication>
#include "focus.h"

int main(int argc, char **args)
{
	QCoreApplication app(argc,args);
	Focus *focus = new Focus;
	return app.exec();
}
