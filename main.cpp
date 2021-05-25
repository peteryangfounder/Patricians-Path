/*
    Name: Peter Yang
    Date: May 25, 2021
    Description: This program reads in the contents of a maze from an external text file (maze.txt) and, starting at position (1,1),
                 outputs a valid path to the goal if the maze is navigable. Otherwise, it will indicate that no path is available.
*/

// Built-in header files
#include <algorithm>
#include <conio.h>
#include <map>
#include <string>
#include <iomanip>

// Custom header file for maze (contains some standard header files)
#include "Graph.h"

using namespace std;

void throwError(HANDLE hConsole) {
    // Description: Outputs error message to user
    SetConsoleTextAttribute(hConsole, 12); // Use red font
    cout<<"\nERROR: Invalid entry. Please try again.\n"<<endl;
    SetConsoleTextAttribute(hConsole, 15); // Use white text colour for user input
}

void askAgain(HANDLE hConsole, string &answer, vector<string> optionNums) {
    // Description: Continually prompts user until input is valid

    // While user input is not in vector of possible answers
    while(find(optionNums.begin(), optionNums.end(), answer) == optionNums.end()) {
        // Display error message
        throwError(hConsole);

        // Get new input from user
        getline(cin, answer);
    }
    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
}

void askQuestion(string question, vector<string> options, string &answer, HANDLE hConsole) {
    // Description: Asks user a specified question, showing possible answers, and updates userAnswer variable (found in main) with user's choice of answer

    // Output question to user
    cout<<question<<endl;

    // Switch to white font
    SetConsoleTextAttribute(hConsole, 15);

    // Construct vector of answer numbers
    vector<string> answerNums;

    // Loop through options vector
    for (unsigned int i = 0; i < options.size(); i++) {
        // Output each option
        cout<<i<<" - "<<options[i]<<endl;

        // Push index to answerNums vector
        answerNums.push_back(to_string(i));
    }

    // Line break to separate options from input
    cout<<endl;

    // Update answer variable
    getline(cin, answer);

    // Empty options vector indicates that user has free reign over the input, so data validation can be skipped
    if (options.empty()) {
        // If input is blank, change name to Moist Von Lipwig
        if (answer == "")
            answer = "Moist Von Lipwig";

        SetConsoleTextAttribute(hConsole, 14); // Use yellow font

        // Skip data validation
        return;
    }

    // While answer is invalid, ask again
    askAgain(hConsole, answer, answerNums);
}

void pressToContinue(HANDLE hConsole, bool isEnd = false) {
    // Description: Instructs user to press any key to continue and listens for key press

    SetConsoleTextAttribute(hConsole, 15); // Use white font

    // Spacing...
    cout<<endl<<endl;

    // If end of program, then tell user to exit
    if (isEnd)
        cout<<"Press any key to exit.";
    // Otherwise, user can keep going
    else
        cout<<"Press any key to continue.";

    // Wait for key press
    getch();

    // Clear screen
    system("cls");

    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
}

int main() {
    // Play music asynchronously (Windows-only)
    PlaySound("soundtrack.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

    // Handle in order to colour text (Windows-only)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // ***** Main Menu *****

    // Introduce user to Patrician's Path
    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
    cout<<"PATRICIAN'S PATH - a fantasy-based maze solver for exploring depth first search (DFS)."<<endl;

    // Display copyright notice
    SetConsoleTextAttribute(hConsole, 12); // Use red font
    cout<<"Copyright 2021. All Rights Reserved."<<endl;

    // Horizontal line separator
    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Explain how program works from a high-level
    SetConsoleTextAttribute(hConsole, 10); // Use green font
    cout<<"HOW IT WORKS (It's Quite Amazing)"<<endl;
    cout<<"1. Give us a maze to solve. If you're reading this, it means you've completed this step."<<endl;
    cout<<"2. Follow steps to customize your experience with theme selection, path visualization, and more!"<<endl;
    cout<<"3. Watch as your hero valiantly traverses the maze, finding a path to the lost riches (if possible!)"<<endl;
    cout<<"4. Seal your hero's fate: Will he return the riches to his gracious patrician or keep them for himself?\n"<<endl;

    // Link to external documentation in case user needs help
    cout<<"Need help? Visit the Scrolls of External Documentation:\nhttps://github.com/peteryangfounder/Patricians-Path"<<endl;

    // Horizontal line separator
    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Declare userAnswer variable
    string userAnswer;

    // Ask user if they are ready to begin
    string question = "Ready to begin?\n";
    vector<string> options{ "Anything for my dear patrician!", "Flee" };
    askQuestion(question, options, userAnswer, hConsole);

    // If answer is 1, exit program
    if (userAnswer == "1")
        return 0;

    // Clear screen
    system("cls");

    // ***** Transition to Settings *****
    cout<<"The Patrician of Ankh-Morpork is pleased upon hearing your decision. The consequence of disobedience, after all, is death. Before your hero sets off on his journey, you will have the chance to configure settings in the following slides."<<endl;

    // Press any key to continue...
    pressToContinue(hConsole);

    // Construct map for storing settings
    map<string, string> settings;

    // ***** Algorithmic Settings *****
    cout<<"ALGORITHMIC SETTINGS"<<endl;

    // Horizontal line separator
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Ask user if they would like to see the length of the path
    question = "1. Would you like to see the length of the path?\n";
    options = { "Yes", "No" };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map
    settings["lengthOfPath"] = options[stoi(userAnswer)];

    // Ask user if they would like to see the percentage and number of cells visited
    question = "\n2. Would you like to see the percentage and fraction of cells visited?\n";
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map
    settings["cellsVisited"] = options[stoi(userAnswer)];

    // Ask user what animation speed they would like
    question = "\n3. What animation speed would you like?\n";
    options = { "Fast", "Normal", "Slow" };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map (in terms of milliseconds)...
    int answer = stoi(userAnswer);

    // Delay lengths: Fast = 250 milliseconds, Normal = 500 milliseconds, Slow = 750 milliseconds
    settings["animationSpeed"] = to_string((answer + 1) * 250);

    // Clear screen
    system("cls");

    // ***** Theme Settings *****
    cout<<"THEME SETTINGS"<<endl;

    // Horizontal line separator
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Prompt user to pick a theme
    question = "Pick a theme for your adventure. This changes the colour palette of the maze.\n";
    options = { "Jungle", "Arctic Tundra", "Nether" };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map, converting to associated SetConsoleTextAttribute value
    if (userAnswer == "0")
        settings["theme"] = "10"; // Jungle is green
    else if (userAnswer == "1")
        settings["theme"] = "11"; // Arctic Tundra is cyan
    else
        settings["theme"] = "12"; // Nether is red

    // Clear screen
    system("cls");

    // ***** Hero Settings *****
    cout<<"HERO SETTINGS"<<endl;

    // Horizontal line separator
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Ask user for their hero's name
    question = "1. In Ankh-Morpork, many heroes inhabit the land, but only a few are destined to be great. What is your hero's name? (Leave blank for Moist Von Lipwig.)";
    options = {}; // Empty options vector
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map
    settings["name"] = userAnswer;

    // Ask user for their hero's role
    question = "\n2. What is your hero's role?\n";
    options = { "Mage", "Warrior", "Vampire", "Elf" };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map
    settings["role"] = options[stoi(userAnswer)];

    // Clear screen
    system("cls");

    // ***** Treasure Settings *****
    cout<<"TREASURE SETTINGS"<<endl;

    // Horizontal line separator
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Let user decide treasure being searched for
    question = "1. A demon emerges from the shadows. Confident that your hero will not find his way, he mockingly reveals the nature of the treasure. What is it?\n";
    options = {
                "$ Mercenary Coins",
                "@ Enchanted Ring",
                "! Sword of a Fallen King",
                "& Necromancer's Potion",
                "* Star of David",
                "+ Cross of Healing",
                "# Paladin's Shield",
                "r Grim Reaper's Scythe"
              };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map
    settings["treasure"] = options[stoi(userAnswer)];

    // Ask user for treasure colour
    question = "\n2. What is the colour of the treasure?\n";
    options = { "Cyan", "Magenta", "Gold" };
    askQuestion(question, options, userAnswer, hConsole);

    // Save setting to map, converting to associated SetConsoleTextAttribute value
    if (userAnswer == "0")
        settings["treasureColour"] = "11"; // Cyan is 11
    else if (userAnswer == "1")
        settings["treasureColour"] = "13"; // Magenta is 13
    else
        settings["treasureColour"] = "14"; // Gold is 14

    // Clear screen
    system("cls");

    // ***** The Journey Begins *****
    cout<<"THE JOURNEY BEGINS..."<<endl;

    // Horizontal line separator
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Caption for storytelling effect
    cout<<settings["name"]<<" the "<<settings["role"]<<" enters the maze in search of "<<settings["treasure"]<<".\n"<<endl;

    // Initialize constant variable to store name of text file
    const string FILE_NAME = "maze.txt";

    // Initialize constant variables for starting coordinates
    const int START_X = 1;
    const int START_Y = 1;

    // Instantiate Graph class, passing in relevant settings
    Graph maze(settings["treasure"][0], stoi(settings["treasureColour"]), stoi(settings["theme"]));

    // Load maze from external text file
    maze.loadGraph(FILE_NAME);

    // Change colour of maze according to selected theme
    if (settings["theme"] == "Arctic Tundra")
        SetConsoleTextAttribute(hConsole, 11); // Blue
    else if (settings["theme"] == "Jungle")
        SetConsoleTextAttribute(hConsole, 10); // Green
    else
        SetConsoleTextAttribute(hConsole, 12); // Red (Nether)

    // Traverse maze!
    bool pathExists = maze.depthFirstSearch(START_X, START_Y);

    // If path exists, then show animated solve states of maze
    if (pathExists)
        maze.animatePath(stoi(settings["animationSpeed"]));
    // If path does not exist, then show unsolvable maze
    else
        maze.displayGraph();

    // Horizontal line separator
    SetConsoleTextAttribute(hConsole, 14); // Use yellow font
    cout<<"______________________________________________________________________________________"<<endl<<endl;

    // Display maze data...

    // Path
    cout<<"Path: ";
    vector<COORD> path = maze.getSolutionSet();

    // If vector is empty, then no path is available
    if (path.empty()) {
        cout<<"Unavailable"<<endl;
    } else {
        // Otherwise, output path in order of starting position to goal
        for (int i = path.size() - 1; i >= 0; i--) {
            // Output ordered pair at each index
            cout<<"("<<path[i].X<<","<<path[i].Y<<") ";
        }
        cout<<endl;
    }

    // Output length of path if user chose to see it
    if (settings["lengthOfPath"] == "Yes") {
        cout<<"\nLength of Path: ";
        path.empty() ? cout<<"Unavailable" : cout<<path.size()<<" Cells";
        cout<<endl;
    }

    // Output cells visited as both fraction and percentage if user chose to see it
    if (settings["cellsVisited"] == "Yes") {
        cout<<"\nCells Visited: ";

        double numerator = maze.getCellsVisited();
        int denominator = maze.getVisitableCells();

        // Fraction
        cout<<numerator<<"/"<<denominator<<" ";

        // Percentage
        cout<<"("<<fixed<<setprecision(0)<<numerator/denominator*100<<"%)"<<endl;
    }

    // Press any key to continue...
    pressToContinue(hConsole);

    // ***** The Journey Ends / The Hero's Fate *****
    // If treasure is found, then ask user what their hero should do with it
    if (pathExists) {
        cout<<"THE JOURNEY ENDS..."<<endl;

        // Horizontal line separator
        cout<<"______________________________________________________________________________________"<<endl<<endl;

        question = "Hoorah, the treasure has been found! What does your hero do with it?\n";
        options = { "Returns it to the patrician as a loyal servant", "Steals it and flees the land" };
        askQuestion(question, options, userAnswer, hConsole);

        // Clear screen
        system("cls");

        // Hero's fate varies depending on selected answer...
        cout<<"THE HERO'S FATE..."<<endl;

        // Horizontal line separator
        cout<<"______________________________________________________________________________________"<<endl<<endl;

        // Fate 1: Returns it to the patrician
        if (userAnswer == "0") {
            cout<<settings["name"]<<" the "<<settings["role"]<<" greets the Patrician of Ankh-Morpork with the newfound treasure.\n\n"

                  "Pleased with your hero's courage and sacrifice, the Patrician orders 2 guards to handcuff your\n"
                  "hero and see him hanged. It is only just that the Patrician himself receives credit for the\n"
                  "achievement while your hero is left unnamed and unremembered. In time, the plebeians will\n"
                  "celebrate the Patrician as a bold and lionhearted leader; meanwhile, your hero's existence will\n"
                  "be erased from all records, his family savagely slaughtered, and his possessions donated to\n"
                  "the estate of the Patrician.\n\n"

                  "After all, who is he to argue? Does he think his one heroic action will clear him of all his years\n"
                  "of conniving, cheating, and theft? Do not forget that the Patrician sees all."<<endl;

        // Fate 2: Steals it and flees the land
        } else {
            cout<<"A thief who starts is always a thief at heart. Does the prophesized treasure not belong to\n"
                  "he who risks his life in pursuit of it? Why should the Patrician, in his comfortable throne\n"
                  "and lavish clothes, be entitled to such a fortune when it is the hero who has toiled so\n"
                  "tirelessly for it?\n\n"

                  <<settings["name"]<<" the "<<settings["role"]<<", enraged, buries the treasure beneath his armour.\n\n"

                  "He sneaks out of Ankh-Morpork, finding refuge in the neighbouring city-state. After\n"
                  "a night of disturbed sleep at the local tavern, he awakes to find himself choked by iron\n"
                  "shackles. Before him he sees his house set aflame, his wife beheaded, and his children\n"
                  "drowned in pools of ale, their limbs planted upright in the damp earth below. To his right,\n"
                  "he sees the Patrician of Ankh-Morpork gripping a dense brown book, its pages crumpled\n"
                  "at the edges and its spine held together by patches of coagulated blood. \"So the prophecy\n"
                  "goes,\" whispers the Patrician. Without missing a beat, he thrusts an arrow through your\n"
                  "hero's armour, piercing his heart and revealing the hidden treasure.\n\n"

                  "\"So it goes,\" chuckles the Patrician."<<endl;
        }

    // If treasure is not found, then display corresponding fate of hero
    } else {
        cout<<"THE HERO'S FATE..."<<endl;

        // Horizontal line separator
        cout<<"______________________________________________________________________________________"<<endl<<endl;

        cout<<"The Patrician of Ankh-Morpork waits expectantly in his royal office, gazing out the window\n"
              "at an endless stretch of plebeian-tended wheat fields.\n\n"

              "Suddenly, your hero, "<<settings["name"]<<" the "<<settings["role"]<<", enters the room with an air of guilt.\n\n"

              "Beads of sweat trickle down his forehead; his feet dance in a spiral motion. After a prolonged\n"
              "silence, your hero delivers the despicable news: that he was unable to obtain the treasure.\n"
              "This failure of duty, he knew, was almost certainly punishable by death. No matter what\n"
              "justification was given, no matter how passionately he begged, the prospect of hanging\n"
              "seemed inevitable and imminent.\n\n"

              "The Patrician arises from his crystal-adorned throne and locks eyes with your hero. He pulls\n"
              "from under his lavish robe a pointed, shiny object, capable of cutting the human flesh.\n"
              "Understanding what is to come, your hero closes his eyes and readies his final breath. At last,\n"
              "the Patrician strikes with a powerful blow, forcefully planting a badge of honour onto your\n"
              "hero's left breast. \"This is for your courage and honesty,\" the Patrician assures. \"The axe will\n"
              "come when you least expect it.\""<<endl;
    }

    // Press any key to exit
    pressToContinue(hConsole, true);

    return 0;
}
