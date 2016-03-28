#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// filestream into string each word
// use head recursion to output words backwards
void yoda(ifstream &file, int count){
	string word;

	if(count > 0){
		file >> word;
		yoda(file, count-1);
		cout << word << endl;
	}
}

int main(int argc, char* argv[]){

	if(argc < 2){
		cerr << "Please provide a .txt file." << endl;
		return 1;
	}

	ifstream file;
	int count;

	file.open(argv[1]);

	if(!file.is_open()){
		cerr << "The .txt file is not valid." << endl;
		return 1;
	}

	file >> count;

	yoda(file, count); // call recursive function "yoda"

	file.close();

	return 0;
}