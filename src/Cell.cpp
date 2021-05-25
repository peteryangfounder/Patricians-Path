// Include Cell header file to flesh out member functions
#include "Cell.h"

Cell::Cell(char symbol):symbol(symbol), visitedStatus(false) {
    // Description: Initializes Cell object
}

char Cell::getSymbol() {
    // Description: Returns symbol of a particular cell
    return symbol;
}

void Cell::markVisited() {
    // Description: Sets visitedStatus to true
    visitedStatus = true;
}

bool Cell::getVisitedStatus() {
    // Description: Returns whether or not the cell has been visited before
    return visitedStatus;
}

void Cell::setSymbol(char newSymbol) {
    // Description: Sets symbol of cell
    symbol = newSymbol;
}

Cell::~Cell() {
    // Description: Destructor for Cell object
}
