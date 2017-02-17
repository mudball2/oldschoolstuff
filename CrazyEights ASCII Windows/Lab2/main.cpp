//New game for PG2 - Crazy Eights 
//Gabriel Islas 
//1429863

#include <fstream>
#include <iostream>
#include <string> 
using namespace std;

#include <Color.h>
using namespace FS;

#include "stdafx.h"

//Including the game header file 
#include "Game.h"



int main( void )
{
	//Change the color for the splash screen at the start of the application here in main. 
	cout << FS::BG_Blue; 
	cout << FS::Green;
	//Prepare ASCII art for the splash screen of this game 
	cout << "MUDBALL GAMES PRESENTS...";
	cout << endl; 
	cout << " .--.                            .--.  _       .-.   .-.      .-. \n"
		 << ": .--'                          : .--':_;      : :  .' `.     : : \n"
		 << ": :   .--.  .--.  .---. .-..-.  : `;  .-. .--. : `-.`. .'.--. : : \n"
		 << ": :__ : ..'' .; ; `-'_.': :; :  : :__ : :' .; :: .. :: :`._-.':_; \n"
		 << "`.__.':_;  `.__,_;`.___;`._. ;  `.__.':_;`._. ;:_;:_;:_;`.__.':_; \n"
		 << "			 .-. :            .-. :  \n"
		 << "			`._.'            `._.'   \n";
	
	cout << Default << BG_Default; 
	system("pause");
	system("cls"); 
	

	//Create a menu system with switch statements. 
	//Will use number input, and maybe later will have a cursor to select a menu item. 
	int choice; 

	//Main menu setup:
	cout << "MAIN MENU: (Enter the corresponding number of your choice)\n"
		 << "\n\n"
		 << "1) Start Game\n"
		 << "2) How to Play\n"
		 << "3) High Scores\n"
		 << "4) Credits\n"
		 << "0) Exit Game\n";

	for( ; ; )
	{
		cout << "Please enter your choice:";
		cin >> choice;

		if(cin.good() && choice >= 0 && choice < 5)
		{
			break;
		} else {
			cout << "Please enter your choice:";
			cin >> choice;
		}

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	
	switch(choice)
	{
	case 1:
		{
		//Have the test code here. 
		system("cls");
		
		Beep(1000, 100);
		Game game;
		game.Run(); 
		break;
		}
	case 2:
		{
			system("cls");
			Beep(1000, 100);
	//Have a more interesting color to read for the instructions here...
	cout << FS::BG_Dark_Red; 
	//Write the instructions for Crazy Eights here. 

	
		
	cout << "	WELCOME TO CRAZY EIGHTS!!\n"
		 << "   =========================\n"
		 << "This \"uno-like\" card game is simple enough to play, and you don't have to worry about betting this time!\n"
		 << "Isn't that fantastic news?! Here's the gist of how to play the game:\n"
		 << "\n\n"
		 << " How to Play\n"
		 << " ===========\n"
		 << "Each player gets dealed some cards and then the remaining cards in the deck\n"
		 << "are left to the side for later drawing. The goal of the game is to get rid of   all of your cards. There will be an\n"
		 << "initial card placed in the middle. You have to only place a card with the same  suit or same value on that pile. If\n"
		 << "you do not have such a card in your deck, then you must continue to draw a card until you do. The first player to\n"
		 << "lose their cards wins!! :D\n"
		 << '\n'
		 << "	--\"Eights\" are a wild card (hence the name \"Crazy Eights\") ! Whichever  player places an eight, must name the suit of what the next cards should\n"
		 << "	be!\n"
		 << '\n'
		 << "That\'s really just about it! It\'s very straight-forward. Now all you have to do is get in there and play! Have fun!\n"
		 << '\n';
	
		cout << Default << BG_Default; 
		system("pause");
		system("cls"); 
		main(); //Explicitly call main to return the beginning...
		break;
		}
	case 3:
		{
			system("cls");
			Beep(1000, 100);
		//Have the high scores here. (Try using C++ File input/output if not with LUA files).

			//So guess, what? We're going to try the C++ file stream to save these high scores and such.
			//The game should write back the scores to here and take in the string of the name of the character
			//That they typed in...I'm on a serious venture here... 

			string name;
			string name2;
			string name3;
			int score;
			int score2;
			int score3;
			ifstream infile;
			infile.open("SavedScores.txt");
			infile >> name; 
			infile >> score;
			cout << "1) " << name << score << endl;  
			infile >> name2;
			infile >> score2;
			cout << "2) " << name2 << score2 << endl;
			infile >> name3;
			infile >>score3;
			cout << "3) " << name3 << score3 << endl;
			infile.close();

			system("pause");
			system("cls"); 
		main(); //Explicitly call main to return the beginning...
		break;
		}
	case 4:
		{
			system("cls");
			Beep(1000, 100);
		//Here are the credits. 
		cout << FS::White; 
		cout << "CREATED AND DEVELOPED BY\n"
			 << "========================\n"
			 << '\n'
			 << "MUDBALL GAMES!\n"
			 << '\n'
			 << "Programmer: Gabriel Islas\n"
			 << "Programmed in C++\n" 
			 << "(Also used FMOD API)\n"
			 << "\n\n" 
			 << "Producer: Justin Tackett (Yeap, AGAIN!) :]\n"
			 << "\n\n"
			 << "Special Thanks:\n"
			 << "Justin and the labbies!\n"
			 << "Coffee and the like!\n"
			 << "C++ for Dummies, because I'm a dummie. :P\n"
			 << "Mr. Stephen Prata\n"
			 << "Jessica Lynn Dery\n"
			 << "\n\n\n"
			 << FS::Yellow 
			 << "THANKS FOR PLAYING!"
			 << Default << BG_Default << endl; 
		system("pause");
		system("cls");
		main(); //Explicitly call main to return the beginning...
		break;
		}
	case 0:
		Beep(1000, 100);
		system("cls");
		break;
	} //End of switch statement 


	cout << Default << BG_Default << endl;
	//system( "pause" ); //This might help our little "exit recursion problem" with Main()
	return 0;
}
