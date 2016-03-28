#include <string>
#include <iostream>
#include <vector>
#include "Facile/lib/msort.h"

using namespace std;

class SortInt {
	public:
		bool operator()(int a, int b){
			return a < b;
		}
};

class SortString_Alphabet {
	public:
		bool operator()(string a, string b){
			return a < b;
		}
};

class SortString_Length {
	public:
		bool operator()(string a, string b){
			return a.size() < b.size();
		}
};

int main(){

	vector<string> a;
	a.push_back("Pearly");
	a.push_back("Apple");
	a.push_back("Sandwiches");
	a.push_back("Serendipity");
	a.push_back("Alligator");
	a.push_back("Indian");
	a.push_back("Pie");
	a.push_back("Insomnia");
	a.push_back("Cote");
	a.push_back("Shindler");
	a.push_back("CS104");
	a.push_back("Death");
	a.push_back("Homework");
	a.push_back("Studying");
	a.push_back("Midterms");
	a.push_back("Nosleep");
	a.push_back("Reignofterror");
	a.push_back("Schoolislife");
	a.push_back("Helpme");
	vector<string> b = a;

	cout << "UNSORTED LIST:" << endl;
	for(int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
	cout << endl;

	SortString_Alphabet abcSort;
	SortString_Length lengthSort;

	mergeSort(a, abcSort);
	mergeSort(b, lengthSort);

	cout << "LIST SORTED ALPHABETICALLY:" << endl;
	for(int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
	cout << endl;

	cout << "LIST SORTED BY LENGTH:" << endl;
	for(int j = 0; j < b.size(); j++)
		cout << b[j] << endl;

	return 0;
}