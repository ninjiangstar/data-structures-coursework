#ifndef VALUESWINDOW_H
#define VALUESWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QFileDialog>

#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QList>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

#include <QBrush>
#include <QColor>
#include <QFont>

#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "./../Facile/Facile.h"
#include "./../Facile/lib/msort_facile.h"

class ValuesWindow : public QWidget
{
	Q_OBJECT
public:
	ValuesWindow(); // sets up values window layout
	~ValuesWindow();
	void setState(ProgramState * m_state);
	void update();

public slots:
	void hideButtonClicked(); // hide values window
	void updateButtonClicked(); // update values list

private:
	ProgramState * state;

	// values window layout
	QGridLayout* valuesLayout;
	QListWidget* valuesList;
	QPushButton* hideButton;
	QPushButton* updateButton;
	QComboBox* sortDropdown;

	// sorting comparisons
	SortPairName_Ascending sort_nameAscending;
	SortPairName_Descending sort_nameDescending;
	SortPairValue_Increasing sort_valueIncreasing;
	SortPairValue_Decreasing sort_valueDecreasing;
};

#endif