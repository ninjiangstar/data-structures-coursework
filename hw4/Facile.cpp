// Facile.cpp
#include "Statement.h"
#include "Statements.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter Facile program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement = NULL;	
	stringstream ss;
	string type;
	string var;
	string var2;
	int val;

	ss << line;
	ss >> type;
	
	// each of these IF statements dynamically defines a new Statement
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		statement = new LetStatement(var, val);
	}
	else if ( type == "PRINT")
	{
		ss >> var;
		statement = new PrintStatement(var);
	}
	else if( type == "PRINTALL")
	{
		statement = new PrintAllStatement();
	}
	else if( type == "ADD" )
	{
		ss >> var;
		char o;
		ss >> o;
		ss.unget();
		if((o >= '0' && o <= '9') || o == '-'){
			ss >> val;
			statement = new AddStatement(var, val);
		}
		else {
			ss >> var2;
			statement = new AddStatement(var, var2);
		}
	}
	else if( type == "SUB" )
	{
		ss >> var;
		char o;
		ss >> o;
		ss.unget();
		if((o >= '0' && o <= '9') || o == '-'){
			ss >> val;
			statement = new SubStatement(var, val);
		}
		else {
			ss >> var2;
			statement = new SubStatement(var, var2);
		}
	}
	else if( type == "MULT" )
	{
		ss >> var;
		char o;
		ss >> o;
		ss.unget();
		if((o >= '0' && o <= '9') || o == '-'){
			ss >> val;
			statement = new MultStatement(var, val);
		}
		else {
			ss >> var2;
			statement = new MultStatement(var, var2);
		}
	}
	else if( type == "DIV" )
	{
		ss >> var;
		char o;
		ss >> o;
		ss.unget();
		if((o >= '0' && o <= '9') || o == '-'){
			ss >> val;
			statement = new DivStatement(var, val);
		}
		else {
			ss >> var2;
			statement = new DivStatement(var, var2);
		}
	}
	else if( type == "GOTO")
	{
		ss >> val; // linenum
		statement = new GoToStatement(val);
	}
	else if( type == "IF" )
	{
		string op;
		string checkTHEN;
		int linenum;
		ss >> var;
		ss >> op;
		ss >> val;
		ss >> checkTHEN;
		if(checkTHEN == "THEN"){
			ss >> linenum;
			statement = new IfThenStatement(var, op, val, linenum);
		}

	}
	else if( type == "GOSUB" )
	{
		ss >> val;
		statement = new GoSubStatement(val);
	}
	else if( type == "RETURN" )
	{
		statement = new ReturnStatement();
	}
	else if( type == "END" || type == "." )
	{
		statement = new EndStatement();
	}
		
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );
	
	/*if(program.size() > 1000){
		outf << "ERR: Program has too many lines." << endl;
		return;
	}*/

	// create program state
	ProgramState state(program.size());

	while(!state.isEnd()) // run program until termination
	    program[state.currLine()]->execute(&state, outf);

	// deallocate everything
	for(std::vector<Statement *>::iterator it = program.begin(); it != program.end(); ++it)
		delete *it;

}

