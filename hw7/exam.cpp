#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include "avlbst.h"

using namespace std;

// 0 = successfully added
// 1 = repeated occurrance
// 2 = repeated occurrance but with wrong slot
int add(AVLTree<int, int> & tree, int exam, int slot)
{
	try
	{
		tree.insert(make_pair(exam, slot));
	}
	catch (...)
	{
		AVLNode<int, int> * node = tree.find(exam);
		if(node->getValue() != slot) return 2;
		return 1;
	}
	return 0;
}

void remove(AVLTree<int, int> & tree, int exam)
{
	try
	{
		tree.remove(exam);
	}
	catch (...) {}
}

/*
PROBLEM 4 BACKTRACKING ALGORITHM:
func bt()
{
	if end: return path = true;
	else
	{
		class = get next class for same student
		for each potential slot
		{
			if slot already used by student, do not add. continue.
			add() current class to AVL tree w/ current slot #
			if class already accounted for but wrong slot, break.
			bt() with next class;
			remove() current class from tree, continue. (but don't remove if repeat)
		}
	}
}
*/

void backtrack(const vector<vector<int> > & courses, AVLTree<int, int> & tree, const int & timeslots, bool ** slots, int student, int course, bool & end)
{
	if(student >= (int)courses.size())
	{
		end = true;
		return;
	}

	// get next class
	int newClass = 0;
	if(course < (int)courses[student].size())
	{
		newClass = courses[student][course];
	}
	else return backtrack(courses, tree, timeslots, slots, student + 1, 0, end);

	for(int i=1; i <= timeslots; i++)
	{
		if(slots[student][i]) continue;

		int checkAdd = add(tree, newClass, i);

		if(checkAdd == 2) continue;
		else slots[student][i] = true;

		backtrack(courses, tree, timeslots, slots, student, course + 1, end);
		if(end) return; // already found a path.

		if(checkAdd == 0)
		{
			remove(tree, newClass);
		}
		slots[student][i] = false;
	}
}

void storeEverything(istream & inf, vector<vector<int> > & courses, int student)
{
	if(inf.eof()) return;
	int newClass;
	inf >> newClass;
	if(inf.fail())
	{
		inf.clear();
		string studentName;
		inf >> studentName; // don't save
		return storeEverything(inf, courses, student + 1);
	}

	courses[student-1].push_back(newClass);
	return storeEverything(inf, courses, student);
}

int main()
{
	string fileName;
	cout << "Input a file: ";
	cin >> fileName;
	ifstream infile(fileName.c_str());

	if(!infile)
	{
		cerr << "Couldn't open file." << endl;
		return 1;
	}

	int exams, students, timeslots;
	AVLTree<int, int> courseTree;
	bool end = false, ** slots;
	infile >> exams >> students >> timeslots;
	vector<vector<int> > courses(students);
	storeEverything(infile, courses, 0);

	slots = new bool*[students]();
	for(int i = 0; i < students; i++)
	{
		slots[i] = new bool[timeslots + 1]();
		for(int j = 1; j < timeslots + 1; j++) slots[i][j] = false;
	}

	backtrack(courses, courseTree, timeslots, slots, 0, 0, end);
	infile.close();

	if(end) // print
	{
		for(AVLTree<int, int>::iterator it = courseTree.begin(); it != courseTree.end(); ++it)
		{
			cout << it->first << " " << it->second << endl;
		}
	}
	else
	{
		cout << "No valid solution." << endl;
	}

	for(int i = 0; i < students; i++) delete [] slots[i];
	delete [] slots; // deallocate

	return 0;
}
