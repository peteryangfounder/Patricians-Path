#ifndef CELL_H
#define CELL_H

class Cell {
    // Public behaviours
    public:
        Cell(char symbol); // Constructor
        virtual ~Cell(); // Destructor
        char getSymbol();
        void setSymbol(char newSymbol);
        bool getVisitedStatus();
        void markVisited();

    // Private attributes
    private:
        char symbol; // Cell symbol
        bool visitedStatus; // Indicates whether the cell has been visited before
};

#endif // CELL_H
