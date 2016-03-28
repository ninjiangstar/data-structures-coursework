#include "Statements.h"
using namespace std;

// NULL statement is empty
NullStatement::NullStatement()
{}

void NullStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	state->incrementLine();
}

string NullStatement::print()
{
	return "";
}

// LET var int
LetStatement::LetStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}

void LetStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	state->insertVars(this->m_variableName, this->m_value);
	state->incrementLine();
}

string LetStatement::print()
{
	stringstream ss; string itoa; ss << this->m_value; ss >> itoa; // converts int to string
	return "LET " + this->m_variableName + " " + itoa;
}

// PRINT var
PrintStatement::PrintStatement(string variableName)
	: m_variableName( variableName )
{}

void PrintStatement::execute(ProgramState * state, ostream &outf)
{
	outf << state->getVars(this->m_variableName) << endl;

	state->incrementLine();
}

string PrintStatement::print()
{
	return "PRINT " + this->m_variableName;
}

// PRINTALL
PrintAllStatement::PrintAllStatement()
{}

void PrintAllStatement::execute(ProgramState * state, ostream &outf)
{
	map<string,int> varMap = state->getMap();

	if(varMap.size() > 0)
		for (map<string,int>::iterator it=varMap.begin(); it!=varMap.end(); ++it)
			outf << it->first << " " << it->second << endl;

	state->incrementLine();
}

string PrintAllStatement::print()
{
	return "PRINTALL";
}

// ADD var val
AddStatement::AddStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

AddStatement::AddStatement(string variableName, string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void AddStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) + val);

	state->incrementLine();
}

string AddStatement::print()
{
	stringstream ss; string itoa; ss << this->m_value; ss >> itoa; // converts int to string
	string append = (this->m_valisint) ? itoa : this->m_value_var;
	return "ADD " + this->m_variableName + " " + append;
}

// SUB var val
SubStatement::SubStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

SubStatement::SubStatement(string variableName, string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void SubStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) - val);

	state->incrementLine();
}

string SubStatement::print()
{
	stringstream ss; string itoa; ss << this->m_value; ss >> itoa; // converts int to string
	string append = (this->m_valisint) ? itoa : this->m_value_var;
	return "SUB " + this->m_variableName + " " + append;
}

// MULT var val
MultStatement::MultStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

MultStatement::MultStatement(string variableName, string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void MultStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) * val);
	
	state->incrementLine();
}

string MultStatement::print()
{
	stringstream ss; string itoa; ss << this->m_value; ss >> itoa; // converts int to string
	string append = (this->m_valisint) ? itoa : this->m_value_var;
	return "MULT " + this->m_variableName + " " + append;
}

// DIV var val
DivStatement::DivStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

DivStatement::DivStatement(string variableName, string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void DivStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);

	if(val == 0){
		//state->makeEnd();
		throw overflow_error("ERR: Cannot divide by zero.");
		return;
	}
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) / val);
	
	state->incrementLine();
}

string DivStatement::print()
{
	stringstream ss; string itoa; ss << this->m_value; ss >> itoa; // converts int to string
	string append = (this->m_valisint) ? itoa : this->m_value_var;
	return "DIV " + this->m_variableName + " " + append;
}

// GOTO linenum
GoToStatement::GoToStatement(int linenum)
	: m_linenum( linenum )
{}

void GoToStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	if(this->m_linenum < 0 || this->m_linenum >= state->numLines()){
		//state->makeEnd();
		throw out_of_range("ERR: illegal jump instruction.");
		return;
	}

	state->setLine(this->m_linenum);
}

string GoToStatement::print()
{
	stringstream ss; string itoa; ss << this->m_linenum; ss >> itoa; // converts int to string
	return "GOTO " + itoa;
}

// IF var op int THEN linenum
IfThenStatement::IfThenStatement(string variableName, string operation, int val, int linenum)
	: m_variableName( variableName ), m_op( operation ), m_value( val ), m_linenum( linenum )
{}

void IfThenStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;

	bool checkStatement = false;

	if(m_op == "<>") checkStatement = (state->getVars(this->m_variableName) != this->m_value);
	else if(m_op == "<") checkStatement = (state->getVars(this->m_variableName) < this->m_value);
	else if(m_op == "<=") checkStatement = (state->getVars(this->m_variableName) <= this->m_value);
	else if(m_op == ">") checkStatement = (state->getVars(this->m_variableName) > this->m_value);
	else if(m_op == ">=") checkStatement = (state->getVars(this->m_variableName) >= this->m_value);
	else if(m_op == "=") checkStatement = (state->getVars(this->m_variableName) == this->m_value);

	if(checkStatement){
		if(this->m_linenum < 0 || this->m_linenum >= state->numLines()){
			//state->makeEnd();
			throw out_of_range("ERR: illegal jump instruction.");
			return;
		}

		state->setLine(this->m_linenum);
		return;
	}

	state->incrementLine();

}

string IfThenStatement::print()
{ // ************************************************************************
	stringstream ss; string itoa, itoa2; 
	ss << this->m_value; ss >> itoa; 
	ss.str(""); ss.clear(); 
	ss << this->m_linenum; ss >> itoa2; // converts int to string
	return "IF " + this->m_variableName + " " + this->m_op + " " + itoa + " THEN " + itoa2;
}

// GOSUB linenum
GoSubStatement::GoSubStatement(int linenum)
	: m_linenum( linenum )
{}

void GoSubStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	if(this->m_linenum < 0 || this->m_linenum >= state->numLines()){
		//state->makeEnd();
		throw out_of_range("ERR: illegal jump instruction.");
		return;
	}

	state->stackPush(state->currLine()+1);
	state->setLine(this->m_linenum);
}

string GoSubStatement::print()
{
	stringstream ss; string itoa; ss << this->m_linenum; ss >> itoa; // converts int to string
	return "GOSUB " + itoa;
}

// RETURN
ReturnStatement::ReturnStatement()
{}

void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	if(!state->stackIsEmpty()){
		state->setLine(state->stackTop());
		state->stackPop();
	}
	else {
		state->makeEnd();
		//state->incrementLine();
	}
}

string ReturnStatement::print()
{
	return "RETURN";
}

// END (or) .
EndStatement::EndStatement()
	: isDot( false )
{}

EndStatement::EndStatement(bool dotbool)
	: isDot( dotbool )
{}

void EndStatement::execute(ProgramState * state, ostream &outf)
{
	(void) outf;
	state->makeEnd();
}

string EndStatement::print()
{
	return (isDot) ? "." : "END";
}