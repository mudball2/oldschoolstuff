////////////////////////////////////////////////////////////////////////////////////////////////
// File :			MemoryFunctions.cpp
// Author :			Rodney Stoeffler
// Created :		03.24.08
// Last Modified :	10.29.09
// Purpose :		Implementation of graphics and timer functions for the Memory Game
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "MemoryFunctions.h"
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	empty
// Notes :		draws an empty memory game board
////////////////////////////////////////////////////////////////////////////////////////////////
void empty()
{
   system("cls");
   cout << "             *             " << endl;
   cout << "           *   *           " << endl;
   cout << "         *       *         " << endl;
   cout << "       *           *       " << endl;
   cout << "     *   *       *   *     " << endl;
   cout << "   *       *   *       *   " << endl;
   cout << " *           *           * " << endl;
   cout << "   *       *   *       *   " << endl;
   cout << "     *   *       *   *     " << endl;
   cout << "       *           *       " << endl;
   cout << "         *       *         " << endl;
   cout << "           *   *           " << endl;
   cout << "             *             " << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	drawUp
// Notes :		draws a memory game board with the upper cell highlighted
////////////////////////////////////////////////////////////////////////////////////////////////
void drawUp()
{
	Beep(500, 200);
   system("cls");
   cout << "             *             " << endl;
   cout << "           *****           " << endl;
   cout << "         *********         " << endl;
   cout << "       *************       " << endl;
   cout << "     *   *********   *     " << endl;
   cout << "   *       *****       *   " << endl;
   cout << " *           *           * " << endl;
   cout << "   *       *   *       *   " << endl;
   cout << "     *   *       *   *     " << endl;
   cout << "       *           *       " << endl;
   cout << "         *       *         " << endl;
   cout << "           *   *           " << endl;
   cout << "             *             " << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	drawDown
// Notes :		draws a memory game board with the lower cell highlighted
////////////////////////////////////////////////////////////////////////////////////////////////
void drawDown()
{
	Beep(600, 200);
   system("cls");
   cout << "             *             " << endl;
   cout << "           *   *           " << endl;
   cout << "         *       *         " << endl;
   cout << "       *           *       " << endl;
   cout << "     *   *       *   *     " << endl;
   cout << "   *       *   *       *   " << endl;
   cout << " *           *           * " << endl;
   cout << "   *       *****       *   " << endl;
   cout << "     *   *********   *     " << endl;
   cout << "       *************       " << endl;
   cout << "         *********         " << endl;
   cout << "           *****           " << endl;
   cout << "             *             " << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	drawLeft
// Notes :		draws a memory game board with the left cell highlighted
////////////////////////////////////////////////////////////////////////////////////////////////
void drawLeft()
{
	Beep(700, 200);
   system("cls");
   cout << "             *             " << endl;
   cout << "           *   *           " << endl;
   cout << "         *       *         " << endl;
   cout << "       *           *       " << endl;
   cout << "     *****       *   *     " << endl;
   cout << "   *********   *       *   " << endl;
   cout << " *************           * " << endl;
   cout << "   *********   *       *   " << endl;
   cout << "     *****       *   *     " << endl;
   cout << "       *           *       " << endl;
   cout << "         *       *         " << endl;
   cout << "           *   *           " << endl;
   cout << "             *             " << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	drawRight
// Notes :		draws a memory game board with the right cell highlighted
////////////////////////////////////////////////////////////////////////////////////////////////
void drawRight()
{
	Beep(800, 200);
   system("cls");
   cout << "             *             " << endl;
   cout << "           *   *           " << endl;
   cout << "         *       *         " << endl;
   cout << "       *           *       " << endl;
   cout << "     *   *       *****     " << endl;
   cout << "   *       *   *********   " << endl;
   cout << " *           ************* " << endl;
   cout << "   *       *   *********   " << endl;
   cout << "     *   *       *****     " << endl;
   cout << "       *           *       " << endl;
   cout << "         *       *         " << endl;
   cout << "           *   *           " << endl;
   cout << "             *             " << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	delay
// Parameters :	milliSeconds - the number of milliseconds to delay
// Notes :		delays for the specified number of milliseconds
////////////////////////////////////////////////////////////////////////////////////////////////
// A Delay Function.
void delay(const unsigned int milliSeconds)
{
   unsigned int start = clock();
   while ((clock() - start) < milliSeconds) {}
}