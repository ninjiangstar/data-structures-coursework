#include "debug_window.h"
#include <iostream>

using namespace std;

DebugWindow::DebugWindow() : QWidget(NULL)
{

	setWindowTitle("Facile Debugger");


	// load window
	debugLayout = new QGridLayout;

	programList = new QListWidget;
	resultsList = new QListWidget;

	breakpointButton = new QPushButton("Toggle Break");
	continueButton = new QPushButton("Continue");
	stepButton = new QPushButton("Step");
	nextButton = new QPushButton("Next");
	inspectButton = new QPushButton("Inspect");
	resetButton = new QPushButton("Reset");
	unloadButton = new QPushButton("Unload");
	quitButton = new QPushButton("Quit");

	programListLabel = new QLabel("Facile program");
	resultListLabel = new QLabel("Output");

	// add everything to visible layout
	debugLayout->addWidget(programListLabel, 0, 0, 1, 4);
	debugLayout->addWidget(resultListLabel, 0, 6, 1, 2);
	debugLayout->addWidget(programList, 1, 0, 9, 4);
	debugLayout->addWidget(breakpointButton, 1, 4, 1, 2);
	debugLayout->addWidget(continueButton, 3, 4, 1, 2);
	debugLayout->addWidget(stepButton, 4, 4, 1, 2);
	debugLayout->addWidget(nextButton, 5, 4, 1, 2);
	debugLayout->addWidget(inspectButton, 7, 4, 1, 2);
	debugLayout->addWidget(resetButton, 9, 4, 1, 1);
	debugLayout->addWidget(unloadButton, 9, 5, 1, 1);
	debugLayout->addWidget(quitButton, 10, 7, 1, 1);
	debugLayout->addWidget(resultsList, 1, 6, 9, 2);

	setLayout(debugLayout);

	QObject::connect(breakpointButton, SIGNAL(clicked()), this, SLOT(breakpointButtonClicked()));
	QObject::connect(continueButton, SIGNAL(clicked()), this, SLOT(continueButtonClicked()));
	QObject::connect(stepButton, SIGNAL(clicked()), this, SLOT(stepButtonClicked()));
	QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
	QObject::connect(inspectButton, SIGNAL(clicked()), this, SLOT(inspectButtonClicked()));
	QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
	QObject::connect(unloadButton, SIGNAL(clicked()), this, SLOT(unloadButtonClicked()));
	QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));

	// setup
	state = new ProgramState(0);
	valuesWindow = new ValuesWindow();

}

DebugWindow::~DebugWindow()
{
	for(std::vector<Statement *>::iterator it = this->program.begin(); it != this->program.end(); ++it)
		delete *it;

	delete state;
	delete debugLayout;
	delete programListLabel;
	delete resultListLabel;
	delete programList;
	delete breakpointButton;
	delete continueButton;
	delete stepButton;
	delete nextButton;
	delete inspectButton;
	delete resetButton;
	delete unloadButton;
	delete quitButton;
	delete valuesWindow;
}

int DebugWindow::programLoader(ifstream & infile, QWidget * loadWindow)
{
	this->loadWindow = loadWindow;
	this->_infile = &infile;
	::parseProgram( infile, this->program ); // IMPORTANT

	delete this->state; // don't lose pointer!

	try {
		this->state = new ProgramState(this->program.size());
		this->valuesWindow->setState(this->state);
		cout << "There are " << this->program.size()-1 << " lines in this program." << endl;

		for(unsigned int i = 1; i < this->program.size(); i++){ // 0th is NullStatement
			stringstream ss; string itoa; ss << i; ss >> itoa; // converts int to string
			this->programList->addItem(QString::fromStdString(itoa + ": " + this->program[i]->print()));
		}

		state->setBegin();
		return 0;
	}
	catch (const exception& exe) { // FACILE PROGRAM OVER 1000 LINES
		QMessageBox::warning(this, "Error", QString::fromStdString(exe.what()));
		this->state = new ProgramState(0);
		valuesWindow->setState(this->state);
		return 1;
	}
}

void DebugWindow::breakpointButtonClicked()
{
	QFont bold; bold.setBold(true);
	QFont unbold; unbold.setBold(false);

	QListWidgetItem * item = this->programList->currentItem();
	
	if(item == NULL) return;

	if(this->isBreakPoint(item)){ // REMOVE BREAKPOINT
		item->setForeground(Qt::black);
		item->setFont(unbold);
	} else { // ADD BREAKPOINT
		item->setForeground(Qt::blue);
		item->setFont(bold);
	}
}

void DebugWindow::continueButtonClicked()
{
	while(!this->state->isEnd()){
		if(this->step() == 1) break;
		if(this->isBreakPoint(this->programList->item(this->state->currLine() - 1))) break;
	}
}

void DebugWindow::stepButtonClicked()
{
	if(this->state->isEnd()) return;

	this->step();
}

void DebugWindow::nextButtonClicked()
{
	if(this->state->isEnd()) return;

	if(this->program[this->state->currLine()]->print().substr(0,5) == "GOSUB"){
		int nextLine = this->state->currLine()+1;
		while(!this->state->isEnd()){
			if(this->step() == 1) break;
			if(this->program[this->state->currLine()]->print() == "RETURN")
				if(this->state->stackTop() == nextLine) break;
		}
	}
	else this->step();
}

void DebugWindow::inspectButtonClicked()
{
	valuesWindow->show();
	valuesWindow->update();
}

void DebugWindow::resetButtonClicked()
{
	this->program.clear();

	QFont unbold; unbold.setBold(false);

	for(int i=0; i<programList->count(); i++){ // RESET ALL COLOR INDICATORS
		programList->item(i)->setBackground(Qt::white);
		if(!this->isBreakPoint(programList->item(i))){
			programList->item(i)->setForeground(Qt::black);
			programList->item(i)->setFont(unbold);
		}
	}

	resultsList->clear();
	state->setBegin();
}

void DebugWindow::unloadButtonClicked()
{
	this->program.clear(); // clear program vector
	this->programList->clear();
	resultsList->clear();
	
	this->hide();
	loadWindow->show(); // swap windows
}

void DebugWindow::quitButtonClicked()
{
	QApplication::exit();
}

bool DebugWindow::isBreakPoint(QListWidgetItem * item) const
{
	QColor blue(0,0,255); QBrush blueBrush(blue);
	return (item->foreground() == blueBrush);
}

int DebugWindow::step()
{
	if(this->state->currLine() != 0 && this->state->currLine() < this->programList->count())
		unsetRed(this->state->currLine() - 1);

	stringstream ss;

	// perform step, catch error message, if error display dialogue

	try {
		this->program[state->currLine()]->execute(this->state, ss); // STEP EXECUTION STAGE
	}
	catch(const exception& exe) {
		QMessageBox::warning(this, "Error", QString::fromStdString(exe.what()));
		return 1;
	}

	if(this->state->currLine() != 0 && this->state->currLine() <= this->programList->count())
		setRed(this->state->currLine() - 1);

	if(this->state->isEnd())
		programList->item(this->state->currLine() - 1)->setBackground(Qt::green);

	string curr;
	while(getline(ss, curr)){
		if(curr == "") continue;
		resultsList->addItem(QString::fromStdString(curr));
	}

	return 0;
}

void DebugWindow::setRed(int linenum){
	QFont bold; bold.setBold(true);

	programList->item(linenum)->setBackground(Qt::red);
	programList->item(linenum)->setFont(bold);
	if(!this->isBreakPoint(programList->item(linenum)))
		programList->item(linenum)->setForeground(Qt::white);
}

void DebugWindow::unsetRed(int linenum){
	QFont unbold; unbold.setBold(false);

	programList->item(linenum)->setBackground(Qt::white);
	if(!this->isBreakPoint(programList->item(linenum))){
		programList->item(linenum)->setForeground(Qt::black);
		programList->item(linenum)->setFont(unbold);
	}
}