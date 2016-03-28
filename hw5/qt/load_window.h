#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include "debug_window.h"

class LoadWindow : public QWidget
{
	Q_OBJECT
public:
	LoadWindow(); // sets up load window interface
	~LoadWindow();
public slots:
	void loadButtonClicked(); // opens file, pass to debug window
	void quitButtonClicked(); // quit program gracefully
	void browseButtonClicked();
private:
	// load layout
	QGridLayout* loadLayout;
	QLabel* loadLabel;
	QLineEdit* fileInput;
	QPushButton* browseButton;
	QPushButton* loadButton;
	QPushButton* quitButton;
	QFileDialog* fileLoader;
	DebugWindow* debugWindow;
};

#endif