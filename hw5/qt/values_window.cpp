#include "values_window.h"

using namespace std;

ValuesWindow::ValuesWindow() : QWidget(NULL)
{
	setWindowTitle("Facile Values");

	valuesLayout = new QGridLayout;

	valuesList = new QListWidget;

	hideButton = new QPushButton("Hide");
	updateButton = new QPushButton("Update");
	sortDropdown = new QComboBox;
	sortDropdown->addItem(tr("Value (Increasing)"));
	sortDropdown->addItem(tr("Value (Decreasing)"));
	sortDropdown->addItem(tr("Name (Ascending)"));
	sortDropdown->addItem(tr("Name (Descending)"));

	valuesLayout->addWidget(sortDropdown, 0, 0, 1, 4);
	valuesLayout->addWidget(updateButton, 0, 4, 1, 1);
	valuesLayout->addWidget(valuesList, 1, 0, 5, 5);
	valuesLayout->addWidget(hideButton, 6, 4, 1, 1);

	setLayout(valuesLayout);

	QObject::connect(hideButton, SIGNAL(clicked()), this, SLOT(hideButtonClicked()));
	QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
}

ValuesWindow::~ValuesWindow()
{
	delete valuesLayout;
	delete valuesList;
	delete hideButton;
	delete updateButton;
	delete sortDropdown;
}

void ValuesWindow::hideButtonClicked()
{
	this->hide();
}

void ValuesWindow::updateButtonClicked()
{
	this->update();
}

void ValuesWindow::setState(ProgramState * m_state){
	this->state = m_state;
	this->update();
}

void ValuesWindow::update()
{
	valuesList->clear(); // CLEAN SLATE
	
	map<string, int> vars = state->getMap();
	vector<pair<string, int> > vecVars;

	// CONVERT MAP TO VECTOR
	for(map<string, int>::iterator it = vars.begin(); it != vars.end(); ++it)
		vecVars.push_back(make_pair(it->first, it->second));

	// MERGE SORT
	if(sortDropdown->currentIndex() == 0) mergeSort(vecVars, sort_valueIncreasing);
	else if(sortDropdown->currentIndex() == 1) mergeSort(vecVars, sort_valueDecreasing);
	else if(sortDropdown->currentIndex() == 2) mergeSort(vecVars, sort_nameAscending);
	else if(sortDropdown->currentIndex() == 3) mergeSort(vecVars, sort_nameDescending);

	// OUTPUT
	for(vector<pair<string, int> >::iterator it = vecVars.begin(); it != vecVars.end(); ++it){
		stringstream ss; string itoa; ss << it->second; ss >> itoa; // converts int to string
		valuesList->addItem(QString::fromStdString(it->first + ": " + itoa));
	}
}