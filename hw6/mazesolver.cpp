#include "mazesolver.h"
#include "mazedisplay.h"
#include "visitedtracker.h"
#include "heap.h"
#include <QMessageBox>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>

MazeSolver::MazeSolver(Maze * m, MazeDisplay * md)
    : maze(m), display(md)
{}

void MazeSolver::solveByDFSRecursive()
{
    // set up DFS
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());
    std::vector<Direction> parent(numSquares);
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    solveByDFSRecursiveCall(q, numExplored, vt, parent); // make recursive call
}

void MazeSolver::solveByDFSRecursiveCall(std::stack<std::pair<int, int>> & q, int & numExplored, VisitedTracker & vt, std::vector<Direction> & parent)
{
    if(q.empty()) return; // base: hit the goal

    // setup and find current step
    int r, c;
    std::pair<int, int> v = q.top();
    q.pop();
    numExplored++;

    r = v.first;
    c = v.second;

    // check if C is in the goal
    if( r == maze->getGoalRow() && c == maze->getGoalCol() )
    {
        reconstructPath(r, c, numExplored, vt, parent);
        return;
    }

    // visit each neighbor
    if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
    {
        parent[squareNumber(r-1, c)] = UP;
        vt.setVisited(r-1,c);
        q.push(std::pair<int,int>(r-1, c));
    }
    
    if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
    {
        parent[squareNumber(r+1, c)] = DOWN;
        vt.setVisited(r+1, c);
        q.push(std::pair<int,int>(r+1, c));
    }
    if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
    {
        parent[squareNumber(r, c-1)] = LEFT;
        vt.setVisited(r, c-1);
        q.push(std::pair<int,int>(r, c-1));
    }
    if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
    {
        parent[squareNumber(r, c+1)] = RIGHT;
        vt.setVisited(r, c+1);
        q.push(std::pair<int,int>(r, c+1));
    }

    // make recursive call
    solveByDFSRecursiveCall(q, numExplored, vt, parent);
}

void MazeSolver::solveByAStar(int choice)
{
    // setup
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();

    // set of nodes already evaluated:
    VisitedTracker vt(maze->numRows(), maze->numCols());
    // came from:
    std::vector<Direction> parent( numSquares );
    // keep gscore: (distance from start)
    std::vector<double> score( numSquares);
    // set of currently discovered nodes still to be evaluated:
    MinHeap<std::pair<int, int>> q(4, make_pair(NULL, NULL));

    // initialize each with zero
    std::vector<bool> numExplored( numSquares, false );
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    score[squareNumber(maze->getStartRow(), maze->getStartCol())] = 0;
    q.add(make_pair(maze->getStartRow(), maze->getStartCol()), getHeuristic(choice, maze->getStartRow(), maze->getStartCol()));

    // iterate priority queue until goal is met
    while( ! q.isEmpty() )
    {
        // set current node in open set having lowest heuristic score
        std::pair<int, int> v = q.peek();
        q.remove();
        r = v.first;
        c = v.second;
        numExplored[squareNumber(r,c)] = true;

        // if current node is goal, reconstruct path.
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            reconstructPath(r, c, std::count(numExplored.begin(), numExplored.end(), true), vt, parent);
            return;
        }

        double newScore = score[squareNumber(r,c)] + 1; // new distance

        // visit each neighbor, but attach heuristic to each neighbor... allow revisiting if score can be improved
        if ( maze->canTravel(UP, r, c) && (! vt.isVisited(r-1,c) || (vt.isVisited(r-1,c) && newScore < score[squareNumber(r-1,c)])))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1, c);
            score[squareNumber(r-1, c)] = newScore;
            q.add(make_pair(r-1, c), newScore + getHeuristic(choice, r-1, c));
        }

        if ( maze->canTravel(DOWN, r, c) && (! vt.isVisited(r+1,c) || (vt.isVisited(r+1,c) && newScore < score[squareNumber(r+1,c)])))
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            score[squareNumber(r+1, c)] = newScore;
            q.add(make_pair(r+1, c), newScore + getHeuristic(choice, r+1, c));
        }

        if ( maze->canTravel(LEFT, r, c) && (! vt.isVisited(r,c-1) || (vt.isVisited(r,c-1) && newScore < score[squareNumber(r,c-1)])))
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            score[squareNumber(r, c-1)] = newScore;
            q.add(make_pair(r, c-1), newScore + getHeuristic(choice, r, c-1));
        }

        if ( maze->canTravel(RIGHT, r, c) && (! vt.isVisited(r,c+1) || (vt.isVisited(r,c+1) && newScore < score[squareNumber(r,c+1)])))
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            score[squareNumber(r, c+1)] = newScore;
            q.add(make_pair(r, c+1), newScore + getHeuristic(choice, r, c+1));
        }
    }
}

void MazeSolver::solveByDFSIterative()
{
    // setup
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    // iterate stack until goal is met
    while( ! q.empty() )
    {
        std::pair<int, int> v = q.top();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        // check if C is in the goal
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            reconstructPath(r, c, numExplored, vt, parent);
            return;
        }

        // visit each neighbor
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }

        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }

        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }

        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::solveByBFS()
{
    // to assign each a unique number [0, maze->numRows() * maze->numCols() -1]
    // we will say maze square (r,c) = r * maze->numCols() + c

    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    // iterate until queue is empty
    while( ! q.empty() )
    {
        std::pair<int, int> v = q.front();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        // check if reached goal
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            reconstructPath(r, c, numExplored, vt, parent);
            return;
        }

        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }

        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }

        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }

        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::reconstructPath(int & r, int & c, int numExplored, VisitedTracker & vt, std::vector<Direction> & parent)
{
    std::vector<Direction> path;
    std::stack<Direction> st;

    // reconstruct path
    while( r != maze->getStartRow() || c != maze->getStartCol())
    {
        st.push( parent[ squareNumber(r,c) ]);
        switch( st.top() )
        {
        case UP: r++; break; // yes, r++.  I went up to get here...
        case DOWN: r--; break;
        case LEFT: c++; break;
        case RIGHT: c--; break;
        }
    }
    while ( ! st.empty() )
    {
        path.push_back(st.top());
        st.pop();
    }
    std::cerr << path.size() << endl;
    display->reportSolution(path, vt, numExplored);
}

double MazeSolver::getHeuristic(int choice, int r, int c) const
{
    if(choice == 1) return 0.0;
    else if(choice == 2) // manhattan
        return std::abs((double)(maze->getGoalRow() - r)) + std::abs((double)(maze->getGoalCol() - c));
    else if(choice == 3) // euclidean
        return sqrt(pow(maze->getGoalRow() - r, 2) + pow(maze->getGoalCol() - c, 2));

    return 0.0;
}


int MazeSolver::squareNumber(int r, int c) const
{
    return maze->numCols() * r + c;
}


