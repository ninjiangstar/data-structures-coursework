#include "ProgramState.h"
#include <string>
#include <map>

ProgramState::ProgramState(int numLines) : m_numLines( numLines )
{
	m_curr = 1;
	end = false;
}

void ProgramState::insertVars(std::string name, int val)
{
	std::map<std::string,int>::iterator iter;
	iter = this->vars.find(name);

	if (iter != this->vars.end()) // will update vars if exists
		this->vars.at(name) = val;
	else
		this->vars.insert(std::pair<std::string, int>(name, val));
}

int ProgramState::getVars(std::string name)
{
	std::map<std::string,int>::iterator iter;
	iter = this->vars.find(name);

	if (iter != this->vars.end())
		return this->vars.at(name);
	else return 0; // return 0 if var doesn't exist
}

std::map<std::string, int> const & ProgramState::getMap() const
{
	return this->vars;
}

void ProgramState::removeVars(std::string name)
{
	this->vars.erase(name);
}

int const & ProgramState::numLines() const
{
	return this->m_numLines;
}

int const & ProgramState::currLine() const
{
	return this->m_curr;
}

void ProgramState::incrementLine()
{
	this->m_curr++;
}

void ProgramState::setLine(int numLine)
{
	this->m_curr = numLine;
}

bool ProgramState::stackIsEmpty() const
{
	return this->holder.empty();
}

int ProgramState::stackTop() const
{
	return this->holder.top();
}

void ProgramState::stackPush(const int& val)
{
	this->holder.push(val);
}

void ProgramState::stackPop()
{
	this->holder.pop();
}

bool ProgramState::isEnd()
{
	return this->end;
}

void ProgramState::makeEnd()
{
	this->end = true;
}