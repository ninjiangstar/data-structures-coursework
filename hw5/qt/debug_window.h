#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include "values_window.h"

class DebugWindow : public QWidget
{
	Q_OBJECT
public:
	DebugWindow(); // sets up debug window layout only
	~DebugWindow();
	int programLoader(std::ifstream & infile, QWidget * loadWindow);

public slots:
	void breakpointButtonClicked(); // toggle breakpoint
	void continueButtonClicked(); // jumps to next breakpoint or program's end
	void stepButtonClicked(); // goes to next step
	void nextButtonClicked(); // goes to next step, skips steps for GOSUB
	void inspectButtonClicked(); // opens values window
	void resetButtonClicked(); // restarts program interpretator
	void unloadButtonClicked();
	void quitButtonClicked(); // quits program gracefully

private:

	bool isBreakPoint(QListWidgetItem * item) const;
	int step();

	void setRed(int linenum);
	void unsetRed(int linenum);

	std::vector<Statement *> program;
	ProgramState* state;

	// save pointer of ifstream, allow for reset
	std::ifstream * _infile;

	QWidget* loadWindow;

	// values window
	ValuesWindow* valuesWindow;

	// debug window layout
	QGridLayout* debugLayout;
	QLabel* programListLabel;
	QLabel* resultListLabel;
	QListWidget* programList;
	QListWidget* resultsList;
	QPushButton* breakpointButton;
	QPushButton* continueButton;
	QPushButton* stepButton;
	QPushButton* nextButton;
	QPushButton* inspectButton;
	QPushButton* resetButton;
	QPushButton* unloadButton;
	QPushButton* quitButton;

};

#endif