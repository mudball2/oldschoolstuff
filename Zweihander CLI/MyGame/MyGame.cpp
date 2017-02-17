//MyGame.cpp : main project file.

#include "stdafx.h"

//using namespace System; //May not need it since it is already in the stdafx.h 

//We include the class file
#include "Image2D.h" 
#include "Sprite.h"
#include "Menu.h"
#include "Game.h"
#include "DList.h"
#include "BinaryData.h"
#pragma comment(lib, "user32.lib") // Including the library file that holds special key commands and such.

int main()
{
	//Memory leak detection code
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetBreakAlloc(-1L); 


	//Setting up the main window for the game. 
	System::Console::SetWindowSize(140,48); 
	System::Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight); 
	System::Console::BackgroundColor = ConsoleColor::DarkBlue;

	cout << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::~===?IIIIIIIIIII?=::::,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::::::\n"
         << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::~=+??IIIIIIIII??+=:::,,,,,,,,,,,,,,,,,,,,,,:,::::::::::~::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::~=?IIIIIIIIIII?+==~~::,,,,,,,,,,,,,,,,,,,,,,,,.............::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:,:==???IIIIIIIIII?==~~~,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::=++???IIIIIIIIIII?=~~~:,,,,,,,,,,,,,,,,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::++????IIIIIIIIIIII?+~~~:,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::~=??IIIIIIIIIIIIIIII?=~~~:,,,,,,,,,,,,,,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:,::~+?IIIIIIIIIIIIIIIIIII?~~::,,,,,,,,,,,,,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:,::~~+III7IIIIII7IIII7IIIII?~~:,:,,,,,,,,,,,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::~~~+IIIIIIIIIIIIIIIIIIIIII+~~::,,,,,,,,,,,,,,,,,,,,,,,:::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::~~+++IIIII????IIIIII7IIIIII+~~::::,:,,,,,,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::~~~++=+IIII??????IIIIII7IIIII?~:::::::,,:,,,,,,,,,,,:,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::~~++++++I????????IIIIIIIII7III+~:::,,,,,,,,,,,,,,,,,,,,:::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::~+++++++=+??????IIIIIIII77IIIII?~~::,::,,,,,,,,,,,,,,:::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::=+++++?~~==++?????IIIIIIIII77III+~~::::,:,,,,,,,,,,,,:::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::=+++++?~~~~~===+???????II777IIIIII?~:::::::,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::~==+++?~~~~~~~===++?????III7I7IIIII?+~~:::::,,,,,,,,,,,,::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::~~===+++:::~~::~~===+?????III77IIIIII?+~~:::::,,,,,,,,,::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::======~~::::::::~~~==++?++??I777IIIIII?=~~:::::,,,,,,,,::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::~====~=~::::::::::~~~==++++?I77IIIIIII??=~~::::,,,,,,,:::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,::::+++=~~::::::::,::::~~==++++IIII7IIIIII?+~::::::,,,,,,,::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,:::~=?~~::::::,,,,,,,,,,::~~====?7777777II7I+=::::::,::,,,,,:::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,::::::~~:::,,,,,,,,,,,,,,,:~~~==?I7777III7I?+=::::::::,,,,:::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::::::::,,,,::::,,,,,,,,:::~=?7I77III777I?~:~:::::::,:::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,::,~::::::,,,,::,,,,,,:::::::::~~?IIII??II777I+:::::::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,::~:::::,,,::,,,,,,,,,,,,,,,::::+???????I77II+~~:::::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,:::~~~::,,,::,,,,,,,,,,,,,,,,,:::~+????++?I77I?=~~::::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,:~~~~~:,,,:,,,,,,,,,,,,,,,,,,,:::~+??+++?I777?+=~~:::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,~~~~::,,,:,,,,,,,,,,,,,,,,,,,,:::::?++==?I77II??:~:::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,==~~:::,,:,,,,,,,,,,,,,,,,,,,,:::::~~~:~=?77I7I?=~~::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,:,:~==~:::,::,,,,,,,,,,,,,,,,,,,,:::::~:~:~=??7777I?~~::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,:,:~~~~:::,::,,,,,,,,,,,,,,,,,,,::::::::::~=??I7777I=~::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,::::::::::::,,,,,,,,,,,,,,:::::::::~~::~:::~+??7777I?~::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,:::::::::::,,,,,,,,,,,:::::,::::::::::::::~+??I7777I~::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,:::::::,::,,,,,,,,,,::,,,,,,:::::::::::::::=??77777I=::::::::::::::::::::::\n"
		 << "\t\t,,,,,,,,,,,,,,,,,,,,,,,,,::::::,,::,,,,,,,,,,::,::::,::::::::,,,,,::~?I77777I=::::::::::::::::::::::\n"
		 << "\t\t:,,,,,,,,,,,,,,,,,,,,,,,::::::,,::,,,,,,,,,,,,:::::::::::::,,,,,:::::+I77I77?~::::::::::::::::::::::\n"
		 << "\t\t::,,,,,,,,,,,,,,,,,,,,,,::::::,::,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::==?II777?~::::::::::::::::::::::\n"
		 << "\t\t:::,,,,,,,,,,,,,+,,,,,,,,:::::::,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::~~=?+?I7I+:::::::::::::::::::::::\n"
		 << "\t\t:::,,,,,,=,,,,,,=,,,,,,,,,,:::,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::::::=~=~==??I?+:::::::::::::::::::::~:\n"
		 << "\t\t:::,,,,,,MUDBALL GAMES PRESENTS...,,,,,,,,,,,,,,,,,,,,,,:::::::::~~~::~=I?I+=:::::::::::::::::::::::\n"
		 << "\t\t::::,,,, ______            _ _                     _              :::::=???=~::::::::::::::::::::::~\n"
		 << "\t\t::::,,,,|___  /           (_) |                   | |          ::::::::+??+=~::::::::::::::::::::::~\n"
		 << "\t\t::::,,,,   / /_      _____ _| |__   __ _ _ __   __| | ___ _ __ :::::::=+?=+=::::::::::::::::::::::::\n"
		 << "\t\t::::,,,,  / /\\ \\ /\\ / / _ \\ | '_ \\ / _` | '_ \\ / _` |/ _ \\ '__|~:::::~=+===~:::::::::::::::::::::::~\n"
		 << "\t\t::::,,,, / /__\\ V  V /  __/ | | | | (_| | | | | (_| |  __/ |   +=~=~~::::::::::::::::::::::::\n"
		 << "\t\t::::,,,,/_____|\\_/\\_/ \\___|_|_| |_|\\__,_|_| |_|\\__,_|\\___|_|   ::~~~==::~~~::::::::::::::::::::::~~\n";
	

	system("pause");
	Console::Clear();
	Console::ResetColor(); 
	System::Console::SetWindowSize(120,32); 
	System::Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight); 

#pragma region Some of the early lab practice stuff
	//Now, we test the code! Yay! 
	/*
	Image2D thing; 
	thing.Show(); 
	*/

	Image2D card( ConsoleColor::Red, ConsoleColor::White, "+---+\n|A  |\n| \x3 |\n|  A|\n+---+\n"); 
	Image2D dice( ConsoleColor::Black, ConsoleColor::White, "* *\n * \n* *\n"); 

	//Should let me create a sprite object here. 
	Sprite spr("Gabe", 0, 0, ConsoleColor::Gray, ConsoleColor::Gray, "-O-");

#if 0 //There is no real need for displaying this code since it works. 
	cout << "Before: \n";
	card.Show(); cout << endl;
	dice.Show(); cout << endl; 

	Image2D temp = card; 
	card = dice; 
	dice = temp; 

	cout << "After:\n";
	card.Show(); cout << endl;
	dice.Show(); cout << endl; 

	//The result is no working for the color but everything else is still going pretty well...
#endif

	//Now we're creating the spaceship 
	Image2D ship(ConsoleColor::DarkGray, ConsoleColor::Black, "|O|" ); 

#if 0
	//A temp variable for the input...
	int shipAmt = 0; 
	//Asking the user how many ships they would like...
	for(;;)
	{
		cout << "How many ships do you want?";
		if(cin >> shipAmt && cin.good() )
		{
			break;
		} else {
			cin.clear();
			cin.ignore(INT_MAX, '\n'); 
		}
	}
	//Now display the little buggers 
	for( int i = 0; i < shipAmt; i++)
	{
		ship.Show(); 
		cout << endl; 
	}

#endif

#pragma endregion
	//Now that there is some 2D images, we're going to write them to a text file and stuff... 
	//(We don't quite know the result of the height and width yet. ASK ABOUT IT SOON!)

#pragma region Writing and Reading to files here
	//Start by opening the text file and stuff.
#if 1
	ofstream outfile;
	outfile.open("pictures.txt");
	//Now write to the file.
	outfile << card.GetgraphicText() << '\t' << static_cast<unsigned int>(card.GetFG())
		<< '\t' << static_cast<unsigned int>(card.GetBG()) << '\n'; //Will write the card image.
	outfile << dice.GetgraphicText() << '\t' << static_cast<unsigned int>(dice.GetFG()) 
		<< '\t' << static_cast<unsigned int>(dice.GetBG()) << '\n'; //Will write the dice image.
	/*outfile << ship.GetgraphicText() << " " << static_cast<unsigned int>(ship.GetFG()) 
	<< " " << static_cast<unsigned int>(ship.GetBG()) << '\n';*/ //And finally...should write the ship image. 
	//Now we should close the outfile and such.
	outfile.close(); 

	ofstream outFile; 
	outFile.open("extra.txt");
	outFile << 3 << '\n';
	outFile << ship.GetgraphicText() << '\t' << static_cast<unsigned int>(ship.GetFG()) 
		<< '\t' << static_cast<unsigned int>(ship.GetBG()) << '\n'; 
	outFile.close(); 

	//For now, I'm going to write to some highscores here with text files and binary. 
	//This is only because I have no real gameplay yet at this point and this is mostly 
	//to test....
	ofstream ofile;
	ofile.open("highScores.txt");
	ofile << spr.GetName() << '\t' << 1000 << '\t' << 10 << '\n';
	ofile.close(); 

	//Start binary here (single)

	//string BinaryFile = "scoresAndStuff.bin";


	ofstream out; 
	out.open("scoresAndStuff.bin", ios_base::out | ios_base::app | ios_base::binary);
	
	if (!out.is_open())
	{
		cout << "It didn't work...";
	} else {
		
		BinaryData bin;
		strncpy_s(bin.name, sizeof bin.name, "Gabe", _TRUNCATE);
		bin.score = 1000;
		bin.time = 10;
		out.write(reinterpret_cast<const char*>(&bin), sizeof bin); 
	}

	out.close();

	

	//Creating one more txt for sprites that holds enemy ships and such. 
	ofstream outputfile;
	outputfile.open("otherSprites.txt");

	outputfile.close(); 

#elif 0
	vector<Sprite*> images; 
	//Yay!! Now it's time to read the file!! 
	ifstream infile; 
	infile.open("pictures.txt"); 

	//Now we should check some conditions before continuing with the process
	if(infile.is_open())
	{
		//Put the stuff in here.

		///We shall start by creating the necessary variables with the correct data types to read with. 
		unsigned int FG; //This will read the foreground number
		unsigned int BG; //This will read the background number

		
		char text[100];

		for(int i = 0; i < 2; i++)
		{
			infile.get(text, sizeof text, '\t'); //This reads the first set of text.
			infile.ignore(INT_MAX, '\t'); 
			infile >> FG; //This reads the foreground number 
			infile.ignore(INT_MAX, '\t'); 
			infile >> BG; //This reads the background number
			infile.ignore(INT_MAX, '\n'); 
			images.resize(i + 1);
			images[i] = new Sprite( "Gabe", 0, 0, (System::ConsoleColor)FG, (System::ConsoleColor)BG, text);
		}

		infile.close();
	}

	


#if 0
	//We no longer need to show all of these image now that it has been proved that works.
	for (decltype(images.size()) x = 0; x < images.size(); x++)
	{
		images[x]->Show();
		System::Console::ResetColor(); 
	}

	for(decltype(images.size()) i = 0; i < images.size(); i++)
	{
		delete images[i];
	}

#endif

#endif

#pragma endregion 

#pragma region Game Loop Starts here


	//So we can NOW...FINALLY start writing the game and make it out with a good passing grade. Yay! :D

	//Setting up the main menu for the game. 
	Menu menu;
	menu.load();

	for(;;)
	{
		menu.display();
		menu.input();
		if(GetAsyncKeyState(VK_RETURN) & 1)
			break;
	}
	 
	
	//Creating a string for name input.
	//string playerName; 


	//Used to have the ask sequence for the player's name here.

	//Now a quick test to see if we can get the sprite through images
	//images[2]->Show(); 
#if 1

	Game g;
	g.Run(); 

#elif 0
	typedef DList<char> OurDList;
	OurDList testDList;
	testDList.push_front('#');
	testDList.push_back('@');
	testDList.clear();
	testDList.push_back('i');
	testDList.push_front('r');
	testDList.push_front('h');
	testDList.push_back('s');
	testDList.push_front('t');
	testDList.erase(2);
	testDList.erase(0);
	testDList.erase(2);
	for (OurDList::size_type i = 0; i < testDList.size(); i++)
		cout << testDList[i];
	testDList.erase(0);
	testDList.erase(0);
	testDList.push_front('!');
	testDList.push_back('\"');
	testDList.erase(1);
	for (OurDList::size_type i = 0; i < testDList.size(); i++)
		cout << testDList[i];
	cout << flush << endl;
	system("pause");
#endif
#pragma endregion 
	System::Console::ResetColor();
	System::Console::SetCursorPosition((Console::WindowWidth - 31) >> 1, Console::WindowHeight - 1);
	system("pause"); 
	return 0;
}

