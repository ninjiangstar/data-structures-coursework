#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include "splay.h" // includes Map, BST (nodes)
#include "hash.h" // include Map

using namespace std;

int main()
{
	// handle test #
	int test;
	cout << "Enter a test: ";
	cin >> test;

	Map * structure;
	if(test == 4) structure = new Splay();
	else if(test == 5) structure = new Hash();
	else
	{
		cerr << "Test " << test << " doesn't exist." << endl;
		return 1;
	}

	// handle fileName
	string fileName;
	cout << "Enter a file: ";
	cin >> fileName;
	ifstream file(fileName.c_str());
	if(!file)
	{
		cerr << "Couldn't open file \"" << fileName << "\"" << endl;
		return 1;
	}

	// begin clock
	clock_t start;
	double duration;
	start = clock();

	// add every word to Map.
	while(!file.eof())
	{
		string word;
		file >> word;
		structure->add(word);
	}

	duration = ( clock() - start ) / (double)CLOCKS_PER_SEC;

	// print everything in Map
	stringstream ss;
	structure->reportAll(ss);
	cout << endl;
	while(!ss.eof())
	{
		string line;
		getline(ss, line);
		cout << line << endl;
	}

	// end clock, return duration
	cout << "Duration: " << duration << endl;

	delete structure; // deallocate !important

	file.close();

	return 0;
}