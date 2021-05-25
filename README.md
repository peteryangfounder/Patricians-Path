# Patrician's Path — External Documentation
*A fantasy-based maze solver for exploring depth first search (DFS).*

## Overview
This program reads in the contents of a maze from an external text file (maze.txt) and, starting at position (1,1), outputs a valid path to the goal if the maze is navigable. Otherwise, it will indicate that no path is available.

## List of Enhancements
* Path visualization with the ability to change animation speed
* Riveting storytelling with a hint of choose-your-own-adventure
* Vibrant colours for a lively and engaging user experience
* Dedicated main menu to explain the program's operation
* Epic background music to capture the spirit of adventure
* Additional maze metrics, including path length and percentage/fraction of cells visited
* Custom maze themes, including: Jungle, Arctic Tundra, Nether
* Hero settings, such as name and role—Mage, Warrior, Vampire, Elf
* Diverse selection of treasures (and the freedom to customize treasure colour):
    * Mercenary Coins ($)
    * Enchanted Ring (@)
    * Sword of a Fallen King (!)
    * Necromancer's Potion (&)
    * Star of David (*)
    * Cross of Healing (+)
    * Paladin's Shield (#)
    * Grim Reaper's Scythe (r)

## Setup: How to Get Patrician's Path Up and Running
Follow the instructions below to get up and running in no time:
1. Ensure you are on Windows OS, as Patrician's Path leverages Windows-specific dependencies
2. Download the ZIP Patricians-Path-main.zip and save the inner Patricians-Path-main folder on your computer. Check that the text file is named maze.txt
3. Open up Patrician's Path.cbp in Code Blocks
4. Download soundtrack.wav from https://drive.google.com/file/d/112_JqmKZgUK53YtQfjMBcJIBuvnfnCgN/view?usp=sharing or use your own music. Note that it must be a WAV file and named soundtrack.wav
5. Save audio file in the same directory as main.cpp
6. In order for the music to play, go to Settings → Compiler... → Linker settings → Other linker options → -lwinmm → OK
7. Build and run

## Figma Mockups
In addition to pseudocode, the prototyping tool Figma was used to help design the program: https://www.figma.com/file/niU6fUwriHStboUeI37Lwa/Patrician-s-Path-Mockups?node-id=0%3A1
