// Lab 1 

#include <iostream>
using namespace std;

//Now include the header files for the "children" classes (Derived/Inherited Classes)  
#include "Computer.h"
#include "Human.h"

//Now include generic classes
#include "Card.h"
#include "Deck.h"
#include "Game.h"
#if 0
#pragma comment(lib, "Winmm.lib" ) // This is how you include a library file in Visual Studio
//This library file is no longer necessary
#endif

#include "Console.h" 
#if 0
#include "Windows.h"
#endif

//AND NOW, we shall get the song running. 
#pragma comment(lib, "fmodex_vc.lib")
#include <fmod.h>
#include <fmod.hpp>

//Create a sound system...
FMOD::System* sys; 
FMOD_RESULT result = FMOD::System_Create(&sys); 

#include <Color.h>
using namespace FS;




int main( void )
{
#if 0
	PlaySound(TEXT("theEntertainer.wav"), NULL, SND_FILENAME | SND_LOOP);
	//We no longer need this method because of FMOD API
#endif
	
	
	//Seed RNG
	srand(unsigned int (time(0))); 
	//Intro to the game:
	cout << FS::White << "MUDBALL GAMES PRESENTS!!!!!!!" << endl; 
	cout << endl; 
	cout << "A game I made at Full Sail...." << endl;
	cout << Default << BG_Default; 
	system("pause"); 
	system("cls"); 
	

	cout << FS::Red << endl; 
	cout << "##### ##   "    <<"###     "   <<"                          " <<"  /        " << endl;			
	cout << "######  /##"       <<" ###    "<<"                          " <<"#/         " << endl;   
	cout << "  /#   /  / ##   " <<"  ##    "<<"                     " <<"##         " << endl; 
	cout << " /    /  /  ##   " <<"  ##    "<<"                     " <<"##         " << endl;
	cout <<"      /  / /    "   <<"  ##    "<<"                      " <<"##         " << endl;
	cout <<"   ## ##  /     "   <<"  ##    "<<"   /###    " <<"   /###    " <<"##  /##    " << endl;
	cout <<"   ## ## /      "   <<"  ##    "<<"  / ###  / " <<"  / ###  / " <<"## / ###   " << endl;
	cout <<"   ## ##/       "   <<"  ##    "<<" /   ###/  " <<" /   ###/  " <<"##/   /    " << endl;
	cout <<"   ## ## ###    "   <<"  ##    "<<"##    ##   " <<"##         " <<"##   /     " << endl;
	cout <<"   ## ##   ###  "   <<"  ##    "<<"##    ##   " <<"##         " <<"##  /      " << endl;
	cout <<"   #  ##     ## "   <<"  ##    "<<"##    ##   " <<"##         " <<"## ##      " << endl;
	cout <<"      /      ## "   <<"  ##    "<<"##    ##   " <<"##         " <<"######     " << endl;
	cout <<"  /##/     ###  "   <<"  ##    "<<"##    /#   " <<"###     /  " <<"##  ###    " << endl;
	cout <<" /  ########    "   <<"  ### / "<<" ####/ ##  " <<" ######/   " <<"##   ### / " << endl;
	cout <<"/     ####      "   <<"   ##/  "<<"  ###   ## " <<"  #####    " <<" ##   ##/ " << endl;

	cout << Default << BG_Default;
	system ( "pause" ); 
	system ( "cls" ); 
	
	cout << FS::Green << endl; 
	cout <<"        ##### ##   " << endl;
	cout <<"     ######  /### /" << endl;
	cout <<"    /#   /  / ###/ " << endl;
	cout <<"   /    /  /   ##  " << endl;
	cout <<"       /  /                                 " <<"  /        " << endl; 
	cout <<"      ## ##                                 " <<"#/         " << endl;
	cout <<"      ## ##                                 " <<"##         " << endl; 
	cout <<"    /### ##                                 " <<"##         " << endl; 
	cout <<"   / ### ##                                 " <<"##         " << endl; 
	cout <<"      ## ##        " <<"   /###     " <<"    /###     " <<"##  /##    " << endl; 
	cout <<"      ## ##        " <<"  / ###  /  " <<"  / ###  /   " <<"## / ###   " << endl; 
	cout <<"      ## ##        " <<" /   ###/   " <<" /   ###/    " <<"##/   /    " << endl;
	cout <<"      ## ##        " <<"##    ##    " <<"##           " <<"##   /     " << endl; 
	cout <<"      #  #         " <<"##    ##    " <<"##           " <<"##  /      " << endl; 
	cout <<"  ##     /         " <<"##    ##    " <<"##           " <<"## ##      " << endl;
	cout <<" ####   /          " <<"##    ##    " <<"##           " <<"######     " << endl; 
	cout <<" /  # #/           " <<"##    /#    " <<"###     /    " <<"##  ###    " << endl; 
	cout <<"/    ##            " <<" ####/ ##   " <<" ######/     " <<"##   ### / " << endl;
	cout <<"     #             " <<"  ###   ##  " <<"  #####      " <<" ##   ##/  " << endl;

	cout << Default << BG_Default;
	system( "pause"); 
	system( "cls"); 

	
	int choice; 
	//Main Menu 
	cout << "\t\tMAIN MENU:" << endl; 
	cout << "\t\t(Type in the corresponding number)" << endl; 
	cout << endl; 
	cout << FS::White; 
	cout << "\t\t1) Play BlackJack" << endl; 
	cout << "\t\t2) How to Play"    << endl; 
	cout << "\t\t3) Credits"        << endl; 
	cout << "\t\t0) Leave Game"     << endl;  

	for( ; ; )
	{
		
		cout << "Type in your choice: ";
		cin >> choice;
		
		if ( cin.good() && (choice == 1 || choice == 2 || choice == 3 || choice == 0))
			break;
		else
			cin >> choice; 

		cin.clear(); 
		cin.ignore(INT_MAX,'\n');
			
	}
	switch(choice)
	{
	case 1:
		{
		system( "cls");

		Beep(500, 1000);

		//Now load the music
		FMOD::Sound* sound;
		sys->setOutput(FMOD_OUTPUTTYPE_DSOUND);
		sys->init(32, FMOD_INIT_NORMAL, 0);
		result = sys->createSound("theEntertainer.wav", FMOD_LOOP_NORMAL, NULL, &sound);

		//Initializing the channel object
		FMOD::Channel* channel = 0; 

		
		//Now play the music...
		result = sys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
		sys->update(); 

		
		Game gamestate; 
		gamestate.SetState(GAME_PLAY); 
		
		gamestate.Run(); 

		 
		
		cout << Default << BG_Default << endl; 
		system("pause"); 
		break;
		}
	case 2:
		{
		system("cls");
		Beep(500, 100);
		cout << "WELCOME TO BLACKJACK!\n" ;
		cout << "======================\n";
		cout << '\n';
		cout << "This very popular card game is simple enough. Your goal is to get the highest hand\n ";
		cout << "of all of your opponents! Be warned though, if your cards add up to more than \"21\",\n ";
		cout << "you just lost! 21 is the highest value possible. If you have 21, it's an automatic win!\n ";
		cout << "(This is why the game is also known as 21).\n ";
		cout << '\n';
		cout << "Here are the values of each card:\n";
		cout << "Aces- are 11.\n";
		cout << "2 through 10- are the same value based on the card's number (i.e. a nine of hearts is \"9\").\n";
		cout << "Jacks, Queens, and Kings- are all 10. \n";
		cout << '\n';
		cout << "How to play:\n";
		cout << "Now that you know the goal of the game and values of each card, you are ready to play BlackJack!\n";
		cout << '\n';
		cout << "You will start the game with two cards, and you will have your initial value of these two cards. \n";
		cout << "You will be given two choices: Hit and Stand. If you decide to \"Hit,\" you have another card added to\n";
		cout << "your hand. The new card will add up to your first two cards, so be careful when deciding to \"Hit.\"\n";
		cout << "Otherwise, if you decide to \"Stand,\" you stay with your initial value and see if your hand beats any\n";
		cout << "of your opponents. The game ends when all players decide to \"Stand,\" and the winner is decided by which\n";
		cout << "hand is highest or if someone's hand adds to \"21.\"\n";
		cout << '\n';
		cout << "Advanced Rules\n";
		cout << "===============\n";
		cout <<'\n';
		cout << "Double Down: In mid-game, you can decide to bet double of the starting bet. (You must take a\n ";
		cout << "card if you decide to Double Down). Your turn also ends once you Double Down. \n";
		cout << '\n';
		cout << "Split Hand: If you have two cards with a value of \"10,\" you can decide to split your hand into \n";
		cout << "two seperate hands. That way, you have more than one shot at winning. \n";
		cout << '\n';
		cout << "Insurance: If the dealer's card shows an Ace, there's a possiblity he might have \"21.\" If you get \n";
		cout << "insurance, and his hand turns out to be 21, then you will each split the bet evenly. \n";
		cout <<'\n';
		cout <<'\n';
		cout << "That's it! Easy, right? Now lets have some fun! \n";
		main(); 
		break;
		}
	case 3:
		system( "cls" ); 
		Beep(500, 100);
		cout << FS::Red << "\t CREDITS\n";
		cout << "\t=========\n";
		cout << Default << BG_Default; 
		cout << '\n';
		cout << '\n';
		cout << FS::White << "\tCreated and Developed by Mudball Games\n";
		cout << "\t======================================\n";
		cout << '\n';
		cout << "Programmer: Gabriel Islas";
		cout << '\n';
		cout << "Programmed in Visual Studio 2010 using C++";
		cout << "(Also used FMOD API and Lua)";
		cout << '\n';
		cout << "Producer: Justin Tackett";
		cout << '\n';
		cout << Default << BG_Default;
		cout << FS::Cyan << "Special Thanks: Justin Tackett\n"
			 << "\t\tMy Parents\n"
			 << "\t\tJessica Lynn Dery (for maintaining my sanity)\n"
			 << "\t\tAll the labby guys\n"
			 << "\t\tAny company that makes caffeinated beverages\n";
		cout <<"\n\n";
		cout << Default << BG_Default;
		cout << FS::White << "THANKS FOR PLAYING!" << endl;
		cout << Default << BG_Default; 
		main(); 
		break; 
	case 0:
		
		break; 
	}
		
	//Although, it will display crap, just test the function calls for the Show() functions 
	//Declare the objects for each class 
	/*
		CComputer comp;
		comp.Show();

		CHuman dude;
		dude.Show(); 
	*/ // No need for these tests for now.
	
	//system( "cls");
	//cout << Default << BG_Default;
	//system( "pause" );
	
	return 0;
}
