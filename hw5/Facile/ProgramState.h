// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// I've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <string>
#include <map>
#include <stdexcept>
#include "lib/stackint.h"

class ProgramState
{
	friend class Statement;
	friend class NullStatement;
	friend class LetStatement;
	friend class PrintStatement;
	friend class PrintAllStatement;
	friend class AddStatement;
	friend class SubStatement;
	friend class MultStatement;
	friend class DivStatement;
	friend class GoToStatement;
	friend class IfThenStatement;
	friend class GoSubStatement;
	friend class ReturnStatement;
	friend class EndStatement;

public:
	ProgramState(int numLines); // construct

	int getVars(std::string name) const; // get the value of a var
	std::map<std::string, int> const & getMap() const; // return an unchangable reference to the map

	int const & numLines() const; // return size of program
	int const & currLine() const; // return current line

	bool stackIsEmpty() const; // stacksss
	int stackTop() const;

	bool isEnd() const; // check if program should be terminated

	void setBegin(); // set m_curr = 0


private:
	void insertVars(std::string name, int val); // insert (or replace) a value into a var
	void removeVars(std::string name); // remove a var from the map

	void incrementLine(); // add 1 to currline
	void setLine(int numLine); // set the currline to somehwere else

	void stackPush(const int& val);
	void stackPop();

	void makeEnd(); // reached END, change status to terminate

	int m_numLines; // new lines
	int m_curr; // current line state
	std::map<std::string, int> vars; // map
	StackInt holder; // stack of int
	bool end;

};

#endif



