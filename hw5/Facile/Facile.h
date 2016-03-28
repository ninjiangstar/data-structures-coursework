#ifndef FACILE_H
#define FACILE_H

#include "Statement.h"
#include "Statements.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(std::istream& inf, std::vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(std::string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(std::istream& inf, std::ostream& outf);

// executes 1 step
// returns error as string
// returns "" if no error
std::string interpretStep(ProgramState * state, const std::vector<Statement *>& program, std::ostream& outf);

#endif