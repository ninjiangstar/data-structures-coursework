#include "qt/load_window.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	LoadWindow mainWindow;

	mainWindow.show();

	return app.exec();
}