#include "load_window.h"

using namespace std;

LoadWindow::LoadWindow() : QWidget(NULL)
{

	setWindowTitle("Facile Loader");


	// load window
	loadLayout = new QGridLayout;
	loadLabel = new QLabel("Facile filename:");
	fileInput = new QLineEdit;
	browseButton = new QPushButton("Browse");
	loadButton = new QPushButton("Load File");
	quitButton = new QPushButton("Quit");
	loadLayout->addWidget(loadLabel, 0, 0, 1, 2);
	loadLayout->addWidget(fileInput, 0, 2, 1, 4);
	loadLayout->addWidget(browseButton, 0, 6, 1, 1);
	loadLayout->addWidget(loadButton, 0, 7, 1, 1);
	loadLayout->addWidget(quitButton, 1, 7, 1, 1);
	setLayout(loadLayout);

	// debug window
	debugWindow = new DebugWindow;

	// button actions
	QObject::connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
	QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
	QObject::connect(browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
	QObject::connect(fileInput, SIGNAL(returnPressed()), this, SLOT(loadButtonClicked()));
}

LoadWindow::~LoadWindow()
{
	delete loadLayout;
	delete loadLabel;
	delete fileInput;
	delete browseButton;
	delete loadButton;
	delete quitButton;
	delete fileLoader;
	delete debugWindow;
}

void LoadWindow::loadButtonClicked()
{
	if(fileInput->text().isEmpty()) return; // nothing entered

	string fileName = fileInput->text().toStdString(); // get filename

	ifstream infile(fileName.c_str()); // open file

	if(!infile) { // throw error if incorrect file
		QMessageBox::warning(this, "Error", QString::fromStdString("\"" + fileName + "\" could not be opened."));
		return;
	}

	if(debugWindow->programLoader(infile, this) == 1) return;

	this->hide();
	debugWindow->show(); // swap windows
}

void LoadWindow::quitButtonClicked()
{
	QApplication::exit();
}

void LoadWindow::browseButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "./",
                                                tr("Any Files (*)"));
	this->fileInput->setText(fileName);
}