// Facile.cpp
#include "Facile.h"

using namespace std;

void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(parseLine("NULL"));
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		Statement * linePtr = parseLine( line );
		if(linePtr == NULL) continue;
		program.push_back(linePtr);
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
	if ( type == "NULL")
	{
		statement = new NullStatement();
	}
	else if ( type == "LET" )
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
		statement = (type == ".") ? new EndStatement(true) : new EndStatement();
	}
		
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );

	// create program state
	ProgramState state(program.size());

	while(!state.isEnd()) // run program until termination
	    program[state.currLine()]->execute(&state, outf);

	// deallocate everything
	for(std::vector<Statement *>::iterator it = program.begin(); it != program.end(); ++it)
		delete *it;

}