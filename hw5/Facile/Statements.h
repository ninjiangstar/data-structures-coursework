#ifndef LET_STATEMENT_INCLUDED
#define LET_STATEMENT_INCLUDED

#include "Statement.h"
#include <sstream>

class NullStatement: public Statement
{
public:
	NullStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// LET *var* *int*  | Change the value of variable *var* to the integer *int*
class LetStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;
public:
	LetStatement(std::string variableName, int value);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// PRINT *var*      | Print the value of variable *var* to output
class PrintStatement: public Statement
{
private:
	std::string m_variableName;
public:
	PrintStatement(std::string variableName);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// PRINTALL         | Prints the value of all used variables to output, one per line.
class PrintAllStatement: public Statement
{
public:
	PrintAllStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// ADD *var* *p*    | Adds *p* to the value of the variable *var*, where *p* is an int or variable.
class AddStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;
	std::string m_value_var;
	bool m_valisint;
public:
	AddStatement(std::string variableName, int value);
	AddStatement(std::string variableName, std::string value);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// SUB *var* *p*    | Subtracts *p* from  the value of the variable *var*, where *p* is an int or variable.
class SubStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;
	std::string m_value_var;
	bool m_valisint;
public:
	SubStatement(std::string variableName, int value);
	SubStatement(std::string variableName, std::string value);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// MULT *var* *p*   | Multiplies the value of the variable *var* by the integer or variable *p*
class MultStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;
	std::string m_value_var;
	bool m_valisint;
public:
	MultStatement(std::string variableName, int value);
	MultStatement(std::string variableName, std::string value);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// DIV *var* *p*    | Divides the value of the variable *var* by the integer or variable *p*
class DivStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;
	std::string m_value_var;
	bool m_valisint;
public:
	DivStatement(std::string variableName, int value);
	DivStatement(std::string variableName, std::string value);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// GOTO *linenum*   | Jumps execution of the program to the line numbered *linenum*
class GoToStatement: public Statement
{
private:
	int m_linenum;
public:
	GoToStatement(int linenum);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// IF *var* *op*    | Compares the value of the variable *var* to the integer *int*
// *int* THEN       | via the operator *op* (<, <=, >, >=, =, <>), and jumps
// *linenum*        | execution of the program to line *linenum* if true.
class IfThenStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_op;
	int m_value;
	int m_linenum;
public:
	IfThenStatement(std::string variableName, std::string op, int value, int linenum);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// GOSUB *linenum*  | Temporarily jumps to line *linenum*, and jumps back after a RETURN
class GoSubStatement: public Statement
{
private:
	int m_linenum;
public:
	GoSubStatement(int linenum);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// RETURN           | Jumps execution of the program back to the most recently executed GOSUB.
class ReturnStatement: public Statement
{
public:
	ReturnStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

// END              | Immediately terminates the program.
class EndStatement: public Statement
{
private:
	bool isDot;
public:
	EndStatement();
	EndStatement(bool dotbool);
	virtual void execute(ProgramState * state, std::ostream &outf);
	virtual std::string print();
};

#endif
