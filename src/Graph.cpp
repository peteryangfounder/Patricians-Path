// Include Graph header file to flesh out member functions
#include "Graph.h"

Graph::Graph(char theTreasure, int theTreasureColour, int theWallColour) {
    // Description: Initializes Graph object
    treasure = theTreasure;
    treasureColour = theTreasureColour;
    wallColour = theWallColour;
    wall = 'X';
    path = ' ';
    cellsVisited = 0;
    visitableCells = 0;
}

void Graph::moveCursor(int x, int y) {
    // Description: Moves position of cursor on console window

    // Create coordinate pair
    COORD coord = {x, y};

    // Set position!
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Graph::delayFrame(int millisec) {
    // Description: Pauses for a given number of milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
}

void Graph::loadGraph(const std::string &FILE_NAME) {
    // Description: Loads maze from external text file and translates to 2D vector

    // Read from text file...
    std::ifstream mazeFile(FILE_NAME);

    // Number of rows equals height
    mazeFile >> height;

    // Number of columns equals width
    mazeFile >> width;

    // Ensure blank spaces are read
    mazeFile >> std::noskipws;

    // Construct 2D vector row by row, where each row is a vector of pointers to cells
    for (int row = 0; row < height; row++) {

        // Iterate through all the columns of each row
        for (int col = 0; col < width; col++) {

            // Pass cell symbol to temporary buffer
            mazeFile >> buffer;

            // Skip new line character
            if (buffer == '\n')
                mazeFile >> buffer; // Replaces new line with the next character

            // Use custom treasure symbol set by user
            else if (buffer == '$')
                buffer = treasure;

            // Push cell pointer to row vector
            rowOfCells.push_back(new Cell(buffer));

            // Increment counter whenever a new visitable cell is encountered
            if (buffer == path || buffer == treasure)
                visitableCells++;
        }

        // Push row to maze 2D vector
        maze.push_back(rowOfCells);
        rowOfCells.clear();
    }

    // Close file
    mazeFile.close();
}

void Graph::displayGraph() {
    // Description: Displays current state of maze according to 2D vector

    // Handle in order to colour text (Windows-only)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Iterate through maze...
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // Output char symbol at each unit with appropriate colour
            if (maze[row][col] -> getSymbol() == '.')
                SetConsoleTextAttribute(hConsole, 15);  // Breadcrumbs are always white
            else if (maze[row][col] -> getSymbol() == wall)
                SetConsoleTextAttribute(hConsole, wallColour);
            else if (maze[row][col] -> getSymbol() == treasure)
                SetConsoleTextAttribute(hConsole, treasureColour);

            std::cout<<maze[row][col] -> getSymbol();
        }
        // End line to separate rows
        std::cout<<std::endl;
    }
}

bool Graph::depthFirstSearch(int row, int col) {
    // Description: Performs depth first search algorithm

    bool foundTreasure;

    // Mark current cell as visited
    maze[row][col] -> markVisited();

    // Increment cellsVisited counter
    cellsVisited++;

    // If current cell is goal, push coordinates to sequenceOfPositions and return true
    if (maze[row][col] -> getSymbol() == treasure) {
        sequenceOfPositions.push_back({row,col});
        return true;
    }

    // Check directions for availability
    // If direction available, call function recursively with new coordinates

    // Up
    if (maze[row-1][col] -> getSymbol() != wall && !(maze[row-1][col] -> getVisitedStatus()))
        foundTreasure = depthFirstSearch(row-1, col);

    // Right
    if (!foundTreasure && (maze[row][col+1] -> getSymbol() != wall && !(maze[row][col+1] -> getVisitedStatus())))
        foundTreasure = depthFirstSearch(row, col+1);

    // Down
    if (!foundTreasure && (maze[row+1][col] -> getSymbol() != wall && !(maze[row+1][col] -> getVisitedStatus())))
        foundTreasure = depthFirstSearch(row+1, col);

    // Left
    if (!foundTreasure && (maze[row][col-1] -> getSymbol() != wall && !(maze[row][col-1] -> getVisitedStatus())))
        foundTreasure = depthFirstSearch(row, col-1);

    // If treasure has been found, push coordinates to sequenceOfPositions and return true
    if (foundTreasure) {
        sequenceOfPositions.push_back({row,col});
        return true;
    }

    // No available directions left, so we return false
    return false;
}

std::vector<COORD> Graph::getSolutionSet() {
    // Description: Returns sequence of positions
    return sequenceOfPositions;
}

double Graph::getCellsVisited() {
    // Description: Returns number of cells visited
    return cellsVisited;
}

int Graph::getVisitableCells() {
    // Description: Returns total number of visitable cells
    return visitableCells;
}

void Graph::animatePath(int animationSpeed) {
    // Description: Animates path from starting position to goal

    // Iterate through solution set in reverse order, excluding item at position 0 (treasure)
    for (int i = sequenceOfPositions.size() - 1; i > 0; i--) {
        // Prevent duplicate mazes
        moveCursor(0,5);

        // Update cell symbol to breadcrumb
        maze[sequenceOfPositions[i].X][sequenceOfPositions[i].Y] -> setSymbol('.');

        // Display new state of maze
        displayGraph();

        // Delay between frames for animation effect
        delayFrame(animationSpeed);
    }
}

Graph::~Graph() {
    // Description: Destructor for Graph object
}
