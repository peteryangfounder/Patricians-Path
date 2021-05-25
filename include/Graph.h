#ifndef GRAPH_H
#define GRAPH_H

// Built-in header files
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>

// Class representing individual cells of maze
#include "Cell.h"

class Graph {
    // Public behaviours
    public:
        Graph(char theTreasure, int theTreasureColour, int theWallColour); // Constructor
        virtual ~Graph(); // Destructor
        void loadGraph(const std::string &FILE_NAME);
        void displayGraph();
        bool depthFirstSearch(int row, int col);
        void delayFrame(int millisec);
        void moveCursor(int x, int y);
        std::vector<COORD> getSolutionSet();
        double getCellsVisited();
        int getVisitableCells();
        void animatePath(int animationSpeed);

    // Private attributes
    private:
        int height; // Number of rows in maze
        int width; // Number of columns in maze
        int visitableCells; // Number of possible visitable cells
        char buffer; // Stores chars from maze.txt
        char wall, treasure, path; // Symbols of maze
        int wallColour, treasureColour; // SetConsoleTextAttribute values for wall and treasure
        double cellsVisited; // Number of unique cells visited

        // 2D vector representing maze
        std::vector<std::vector<Cell*>> maze;

        // Individual row of cells (element of 2D vector)
        std::vector<Cell*> rowOfCells;

        // Vector storing solution set (sequence of positions)
        std::vector<COORD> sequenceOfPositions;
};

#endif // GRAPH_H
