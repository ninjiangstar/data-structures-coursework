#include "Statements.h"
using namespace std;

// LET var int
LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}

void LetStatement::execute(ProgramState * state, ostream &outf)
{
	state->insertVars(this->m_variableName, this->m_value);
	state->incrementLine();
}

// PRINT var
PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}

void PrintStatement::execute(ProgramState * state, ostream &outf)
{
	outf << state->getVars(this->m_variableName) << endl;

	state->incrementLine();
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

// ADD var val
AddStatement::AddStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

AddStatement::AddStatement(std::string variableName, std::string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void AddStatement::execute(ProgramState * state, ostream &outf)
{
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) + val);

	state->incrementLine();
}

// SUB var val
SubStatement::SubStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

SubStatement::SubStatement(std::string variableName, std::string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void SubStatement::execute(ProgramState * state, ostream &outf)
{
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) - val);

	state->incrementLine();
}

// MULT var val
MultStatement::MultStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

MultStatement::MultStatement(std::string variableName, std::string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void MultStatement::execute(ProgramState * state, ostream &outf)
{
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) * val);
	
	state->incrementLine();
}

// DIV var val
DivStatement::DivStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value ), m_valisint( true )
{}

DivStatement::DivStatement(std::string variableName, std::string value)
	: m_variableName( variableName ), m_value_var( value ), m_valisint( false )
{}

void DivStatement::execute(ProgramState * state, ostream &outf)
{
	int val = (this->m_valisint) ? this->m_value : state->getVars(this->m_value_var);

	if(val == 0){
		outf << "ERR: Cannot divide by zero." << endl;
		state->makeEnd();
		return;
	}
	state->insertVars(this->m_variableName, state->getVars(this->m_variableName) / val);
	
	state->incrementLine();
}

// GOTO linenum
GoToStatement::GoToStatement(int linenum)
	: m_linenum( linenum )
{}

void GoToStatement::execute(ProgramState * state, ostream &outf)
{
	if(this->m_linenum < 0 || this->m_linenum >= state->numLines()){
		outf << "ERR: illegal jump instruction." << endl;
		state->makeEnd();
		return;
	}

	state->setLine(this->m_linenum);
}

IfThenStatement::IfThenStatement(std::string variableName, std::string operation, int val, int linenum)
	: m_variableName( variableName ), m_op( operation ), m_value( val ), m_linenum( linenum )
{}

void IfThenStatement::execute(ProgramState * state, ostream &outf)
{

	bool checkStatement = false;

	if(m_op == "<>") checkStatement = (state->getVars(this->m_variableName) != this->m_value);
	else if(m_op == "<") checkStatement = (state->getVars(this->m_variableName) < this->m_value);
	else if(m_op == "<=") checkStatement = (state->getVars(this->m_variableName) <= this->m_value);
	else if(m_op == ">") checkStatement = (state->getVars(this->m_variableName) > this->m_value);
	else if(m_op == ">=") checkStatement = (state->getVars(this->m_variableName) >= this->m_value);
	else if(m_op == "=") checkStatement = (state->getVars(this->m_variableName) == this->m_value);

	if(checkStatement){
		if(this->m_linenum < 0 || this->m_linenum >= state->numLines()){
			outf << "ERR: illegal jump instruction." << endl;
			state->makeEnd();
			return;
		}

		state->setLine(this->m_linenum);
		return;
	}

	state->incrementLine();

}

GoSubStatement::GoSubStatement(int linenum)
	: m_linenum( linenum )
{}

void GoSubStatement::execute(ProgramState * state, ostream &outf)
{
	state->stackPush(state->currLine()+1);
	state->setLine(this->m_linenum);
}

ReturnStatement::ReturnStatement()
{}

void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
	if(!state->stackIsEmpty()){
		state->setLine(state->stackTop());
		state->stackPop();
	}
	else {
		state->makeEnd();
		//state->incrementLine();
	}
}

EndStatement::EndStatement()
{}

void EndStatement::execute(ProgramState * state, ostream &outf)
{
	state->makeEnd();
}