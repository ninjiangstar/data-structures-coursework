#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3){
		cerr << "Please provide an input and output file." << endl;
		return 1;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	if(!input.is_open()){
		cerr << "The input file is not valid." << endl;
		return 1;
	}

	int floors; // # of floors
	int *floorsizes; // # of people per floor
	string ***trojans; // 3D array of floor > trojan > posession
	string curr; // current command

	input >> floors;
	trojans = new string**[floors]();

	floorsizes = new int[floors]();

	for (int i = 0; i < floors; i++) {
		floorsizes[i] = 0;
		trojans[i] = NULL;
	}
	while(getline(input, curr)) {
		stringstream ss;
		ss << curr;
		ss >> curr;
		if (curr == "MOVEIN") {
			int i,k;
			ss >> i; // floor
			ss >> k; // students
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else {
				if(i > floors-1 || i < 0)
					output << "Error - floor " << i << " does not exist" << endl;
				else if(floorsizes[i] > 0) 
					output << "Error - floor " << i << " is not empty" << endl;
				else {
					if(k < 1)
						output << "Error — you can't move in less than 1 person into floor " << i << endl;
					else {
						floorsizes[i] = k;
						trojans[i] = new string*[k]();
					}
				}
			}
		}
		else if (curr == "MOVEOUT") {
			int i;
			ss >> i; // floor
			if (ss.fail()) output << "Error - incorrect command" << endl;
			else {
				if(i > floors-1 || i < 0)
					output << "Error - floor " << i << " does not exist" << endl;
				else if(floorsizes[i] == 0)
					output << "Error - floor " << i << " is already empty" << endl;
				else {
					for(int j=0; j<floorsizes[i]; j++){
						delete [] trojans[i][j];
					}
					delete [] trojans[i];
					trojans[i] = NULL; // remove traces of studenet
					floorsizes[i] = 0;
				}
			}

		}
		else if (curr == "OBTAIN") {
			int i, j, k;
			ss >> i >> j >> k; // floor, student, posessions
			if(ss.fail())  output << "Error - incorrect command" << endl;
			else {
				if(i > floors-1 || i < 0)
					output << "Error - floor " << i << " does not exist" << endl;
				else if(j > floorsizes[i]-1 || j < 0)
					output << "Error - student " << j << " on floor " << i << " does not exist" << endl;
				else if(trojans[i][j] != NULL)
					output << "Error - student " << j << " on floor " << i << " already has posessions" << endl;
				else {
					trojans[i][j] = new string[k+1]();
					for(int c = 0; c < k; c++){
						ss >> trojans[i][j][c];
					}
					trojans[i][j][k] = ""; // allow while loop to find end
				}
			}

		}
		else if (curr == "OUTPUT") {
			int i, j;
			ss >> i >> j; // floor, student
			if(ss.fail())  output << "Error - incorrect command" << endl;
			else {
				if(i > floors-1 || i < 0)
					output << "Error - floor " << i << " does not exist" << endl;
				else if(j > floorsizes[i]-1 || j < 0)
					output << "Error - student " << j << " on floor " << i << " does not exist" << endl;
				else {
					int k=0;
					while(trojans[i][j][k] != ""){
						output << trojans[i][j][k] << endl;
						k++;
					}
				}
			}
		}
		else {
			if(curr.length() > 0){
				output << "Error - incorrect command" << endl;
			}
		}
	}

	// DEALLOCATE EVERYTHING.

	for(int i=0; i<floors; i++){
		for(int j=0; j<floorsizes[i]; j++){
			delete [] trojans[i][j];
		}
		delete [] trojans[i];
	}
	delete [] trojans;
	trojans = NULL;


	delete [] floorsizes;
	floorsizes = NULL;

	input.close();
	output.close();

	return 0;
}
