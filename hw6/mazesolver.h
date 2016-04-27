#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "maze.h"
#include "visitedtracker.h"
#include <stack>
#include <vector>

class MazeDisplay;
class Maze;

class MazeSolver
{
public:
    MazeSolver(Maze * m, MazeDisplay * md);

    void solveByBFS();

    void solveByDFSIterative();

    void solveByDFSRecursive();

    void solveByAStar(int heuristicChoice);

    void setMaze(Maze* m) { maze = m; }

private:

    int squareNumber(int r, int c) const;

    void solveByDFSRecursiveCall(std::stack<std::pair<int, int>> & q, int & numExplored, VisitedTracker & vt, std::vector<Direction> & parent);
    void reconstructPath(int & r, int & c, int numExplored, VisitedTracker & vt, std::vector<Direction> & parent);
    double getHeuristic(int choice, int r, int c) const;

    Maze * maze;
    MazeDisplay * display;

};

#endif // MAZESOLVER_H
