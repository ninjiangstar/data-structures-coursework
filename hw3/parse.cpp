#include "stackint.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// define special characters
#define OPEN  -1 // (
#define CLOSE -2 // )
#define RIGHT -3 // >
#define LEFT  -4 // <
#define TIMES -5 // *
#define PLUS  -6 // +
#define MAL   -7 // bad input

// PROTOTYPES
int parse(string s); // calculates for each character in expression
int parseShift(StackInt & stack); // do all the shift operations, then push the result
int parseExp(StackInt & stack); // do all the operations within (parenthesis)

// RUN FIRST
int main(int argc, char* argv[]){
	
	if(argc != 2){
		cerr << "Incorrect syntax: should be ./SAP filename.txt" << endl;
		return 1;
	}

	ifstream file(argv[1]); // open file

	if(!file.is_open()){
		cerr << "Could not read file " << argv[1] << endl;
		return 1;
	}

	string curr;

	while(getline(file,curr)){ // one expression per line
		if(curr == "") continue; // if line is blank, ignore and go to next
		int result = parse(curr); // parse
		if(result == MAL) cout << "Malformed" << endl;
		else cout << result << endl;
	}

	file.close();
	return 0;
}


int parse(string s){

	StackInt stack;

	// for each character in the array
	for(unsigned int i=0; i < s.length(); i++)
	{
		if(s[i] == ' '){ 
			if(!stack.empty()) // make sure theres no space between integers
				if(stack.top() >= 0)
					if(s[i+1] >= '0' && s[i+1] <= '9')
						return MAL;
			continue; // don't do anything on white space
		}
		else if(s[i] >= '0' && s[i] <= '9'){ // is int, add to stack
			int num = (int)s[i] - 48;
			if(!stack.empty()){
				if(stack.top() >= 0){ // the previous int is the tens of current int
					num = num + stack.top()*10;
					stack.pop();
				}
			}
			stack.push(num);
		}
		else if(s[i] == '>'){ // is >, add to stack
			if(stack.empty()) stack.push(RIGHT);
			else { // avoid throw exception
				if(stack.top() != CLOSE && stack.top() < 0) stack.push(RIGHT);
				else return MAL; // may not be preceeded by int or )
			}
		}
		else if(s[i] == '<'){ // is <, add to stack
			if(stack.empty()) stack.push(LEFT);
			else { // avoid throw exception
				if (stack.top() != CLOSE && stack.top() < 0) stack.push(LEFT);
				else return MAL; // may not be preceeded by int or )
			}
		}
		else if(s[i] == '*' || s[i] == '+'){
			if(parseShift(stack) == 1) return MAL; // parseShift
			if(stack.empty()) return MAL;
			if(stack.top() < 0 && stack.top() != CLOSE) return MAL;
			
			if(s[i] == '*') stack.push(TIMES);
			else if(s[i] == '+') stack.push(PLUS);
		}
		else if(s[i] == '('){
			if(!stack.empty() && (stack.top() >= 0 || stack.top() == CLOSE)) return MAL;
			stack.push(OPEN);
		}
		else if(s[i] == ')'){
			if(parseShift(stack) == 1) return MAL; // parseShift
			if(parseExp(stack) == 1) return MAL; // parseExp
		}
		else return MAL;

	}

	if(parseShift(stack) == 1) return MAL; // parseShift, outside of ()

	// last check for syntaxical errors
	int final;
	if(stack.top() >= 0) final = stack.top();
	else return MAL;

	stack.pop();
	if(!stack.empty()) return MAL;

	return final; // output final calculation
}


int parseShift(StackInt & stack){
	// base case: nothing to shift
	if(stack.empty()) return 0;
	int num = stack.top();
	stack.pop();
	// shift for each > or < operation
	while(!stack.empty() && (stack.top() == RIGHT || stack.top() == LEFT)){
		if(stack.top() == RIGHT) num = num/2;
		else if(stack.top() == LEFT) num = num*2;
		stack.pop();
	}

	stack.push(num);
	return 0;
}


int parseExp(StackInt & stack){
	if(stack.empty()) return 1;
	if(stack.top() < 0) return 1;

	int num = stack.top();
	if(num >= 0) stack.pop();
	else return 1; // first term in stack must be number


	if(stack.empty()) return 1;
	
	int op = stack.top();

	if(stack.top() == OPEN){
		stack.pop();
		stack.push(num);
		return 0; // if second term is OPEN, then no operations, output
	}
	else if(op == TIMES || op == PLUS) stack.pop();
	else return 1; // if second term is not an operation, error

	// perform operation on each term until reach OPEN
	while(!stack.empty()){
		if(stack.top() == OPEN) break;
		if(stack.top() >= 0){
			if(op == TIMES) num *= stack.top();
			else if(op == PLUS) num += stack.top();
			stack.pop();
		}
		else if(stack.top() == op) stack.pop();
		else return 1;
	}

	if(!stack.empty()){
		if(stack.top() == OPEN) stack.pop();
		else return 1;
	}
	else return 1; // check if there is an extra closing bracket

	stack.push(num);

	return 0;
}
