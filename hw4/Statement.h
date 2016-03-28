// Statement.h
//
// This is the abstract Statement class, from which your various statement
// classes will need to extend.  There is only one method in the Statement
// class, an execute() method that executes the statement, making any
// necessary changes to the given ProgramState.

#ifndef STATEMENT_INCLUDED
#define STATEMENT_INCLUDED

#include "ProgramState.h"
#include <fstream>

class Statement
{
public:
   virtual ~Statement(){};
	virtual void execute(ProgramState*  state, std::ostream &outf) = 0;
};

#endif

