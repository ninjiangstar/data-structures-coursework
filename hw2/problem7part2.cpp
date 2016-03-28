#include "llistint.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// THIS FUNCTION HELPS TURN LIST INTO STRING, ALLOWING ME TO COUT.
string printlist( LListInt *& list){
	stringstream ss;
	for (int i=0; i<list->size(); i++){
		ss << list->get(i);
		if(i < list->size()-1) ss << ", ";
	}
	return ss.str();
}

int main(){
	LListInt* list = new LListInt();

	cout << "BEGINNING 15 TEST CASES..." << endl;

	// We can assume that the following will work if and only if get(), size() and empty() work
	// get() and set() will throw a core dump if given bad location

	// NOMINAL
	// 1. Check if the list is initially empty.
	if (list->empty()) cout << "SUCCESS: (1) List is empty initially." << endl;
	else cout << "FAIL: (1) List is not empty initially when it should be." << endl;

	// OFFNOMINAL
	// 2. Check: insert into empty list with bad location
	list->insert(1, 5);
	if(list->empty()) cout << "SUCCESS: (2) List is still empty." << endl;
	else cout << "FAIL: (2) List now has " << list->size() << " element(s)" << endl;

	// NOMINAL
	// 3. Check: insert into empty list with loc = 0
	list->insert(0,5); // 5
	if(list->size()==1){
		if(list->get(0)==5) cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (3) list is " << temp << endl;

	}
	else cout << "FAIL: (3) list has size " << list->size() << " instead of 1" << endl;

	// BOUNDARY
	// 4. Check: insert element to end of list. (loc == size)
	list->insert(1,8); // 5, 8
	if(list->size()==2){
		if(list->get(0)==5 && list->get(1)==8) cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (4) list is " << temp << endl;
	}
	else cout << "FAIL: (4) list has size " << list->size() << " instead of 2" << endl;

	// BOUNDARY
	// 5. Check: insert element to front of list
	list->insert(0,2); // 2, 5, 8
	if(list->size()==3){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==8) cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (5) list is " << temp << endl;
	}
	else cout << "FAIL: (5) list has size " << list->size() << " instead of 3" << endl;

	// NOMINAL
	// 6. Check: insert element to middle of list
	list->insert(2,3); // 2, 5, 3, 8
	if(list->size()==4){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==3 && list->get(3)==8)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (6) list is " << temp << endl;
	}
	else cout << "FAIL: (6) list has size " << list->size() << " instead of 4" << endl;

	// OFFNOMINAL
	// 7. Check: insert element in bad location
	list->insert(5,0); // 2, 5, 3, 8
	if(list->size()==4){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==3 && list->get(3)==8)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (7) list is " << temp << endl;
	}
	else if(list->size()==5) 
		cout << "FAIL: (7) the 5th element " << list->get(5) << " was incorrectly inserted" << endl;
	else cout << "FAIL: (7) list has size " << list->size() << " instead of 4" << endl;

	// OFFNOMINAL
	// 8. Check: remove element from loc == size (bad location)
	list->remove(4);
	if(list->size()==4){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==3 && list->get(3)==8)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (8) list is " << temp << endl;
	}
	else cout << "FAIL: (8) list has size " << list->size() << " instead of 4" << endl;

	// OFFNOMINAL
	// 9. Check: remove element from loc > size (bad location)
	list->remove(5);
	if(list->size()==4){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==3 && list->get(3)==8)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (9) list is " << temp << endl;
	}
	else cout << "FAIL: (9) list has size " << list->size() << " instead of 4" << endl;

	// BOUNDARY
	// 10. Check: remove element from end of list
	list->remove(3); // 2, 5, 3
	if(list->size()==3){
		if(list->get(0)==2 && list->get(1)==5 && list->get(2)==3)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (10) list is " << temp << endl;
	}
	else cout << "FAIL: (10) list has size " << list->size() << " instead of 3" << endl;

	// BOUNDARY
	// 11. Check: removing from beginning of list
	list->remove(0); // 5, 3
	if(list->size()==2){
		if(list->get(0)==5 && list->get(1)==3)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (11) list is " << temp << endl;
	}
	else cout << "FAIL: (11) list has size " << list->size() << " instead of 2" << endl;

	// NOMINAL
	// 12. Check: removing from middle of list
	list->insert(1,9); // 5, 9, 3
	list->remove(1); // 5, 3
	if(list->size()==2){
		if(list->get(0)==5 && list->get(1)==3)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (12) list is " << temp << endl;
	}
	else cout << "FAIL: (12) list has size " << list->size() << " instead of 2" << endl;

	// 13. Check: setting
	list->set(0, 3); // 3, 3
	list->set(1, 5); // 3, 5
	if(list->size()==2){
		if(list->get(1)==5 && list->get(0)==3)
			cout << "SUCCESS";
		else cout << "FAIL";
		string temp = printlist(list);
		cout << ": (13) list is " << temp << endl;
	}
	else cout << "FAIL: (13) list has size " << list->size() << " instead of 2" << endl;

	// NOMINAL
	// 14. Check: clear
	list->clear();
	string temp = printlist(list);
	if (list->empty()) cout << "SUCCESS: (14) List is emptied." << endl;
	else cout << "FAIL: (14) List is not empty: " << temp << endl;

	//OFFNOMINAL
	// 15. Check: remove
	list->remove(0);
	temp = printlist(list);
	if (list->empty()) cout << "SUCCESS: (15) List is empty and ok." << endl;
	else cout << "FAIL: (15) List is not empty: " << temp << endl;

	cout << "ALL TESTS ARE COMPLETE. NOW DELETING LIST." << endl;

	delete list;

	return 0;

}