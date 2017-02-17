#include "stdafx.h"
#include "Game.h"
#include "Util.h"

// NB LockWindowUpdate(), GetConsoleWindow(), GetAsyncKeyState()
#pragma comment(lib, "user32.lib")

//Including stuff for FMOD
#pragma comment(lib, "fmodex_vc.lib")
#include <fmod.h>
#include <fmod.hpp> 

//Creating the FMOD system.
FMOD::System* sys;
FMOD_RESULT  result = FMOD::System_Create(&sys);

Game::Game(void) : ene(1), cell(0), missle()
{
	//Console::SetWindowSize(80, 28);
	//Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);

	//Seed RNG
	srand((unsigned int)(time(0))); 
	rand();

	//this to set up the array of missles from the sprite class. 
	//miss = new Sprite[100];
	//miss = Sprite( "Missle", mX, mY, ConsoleColor::Black, ConsoleColor::Yellow, "*");
	//miss[100].SetgraphicText("*");
	//miss[100].SetFG(ConsoleColor::Yellow);

	//Set default player name
	playerName = "Captain";
	Ask();
	
	//Set up the main player stuff 
	health = 200;
	score = 0; 

		x = rand() % (8 - 1 + 1) +1; 

	if( x == 1)
		song = "04-street.mp3";
	else if(x == 2)
		song = "06-chase.mp3";
	else if(x == 3)
		song = "07-machine-beat.mp3";
	else if(x == 4)
		song = "08-badlands.mp3";
	else if(x == 5)
		song = "12-factory.mp3";
	else if(x == 6)
		song = "15-confilct.mp3";
	else if(x == 7)
		song = "22-shudder.mp3";
	else
		song = "28-metempsychosis.mp3";
	
	// load sound
	FMOD::Sound* sound;
	sys->setOutput(FMOD_OUTPUTTYPE_DSOUND );
	sys->init(32, FMOD_INIT_NORMAL, 0); 
	result = sys->createSound(song.c_str(), FMOD_LOOP_NORMAL,NULL, &sound);

	//Initialize channel
	FMOD::Channel* channel = 0;
	
	// play sound
	result = sys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	sys->update();

	play = true;
	//Paste the images[2] setup here...
	//ifstream InFile("extra.txt");
	//if(InFile.is_open())
	//{
	//	unsigned int fg, bg, count;
	//	char last[100];

	//	InFile >> count;
	//	InFile.ignore(INT_MAX, '\n'); 
	//	InFile.get(last, sizeof last, '\t'); //This reads the first set of text.

	//	InFile.ignore(INT_MAX, '\t'); 
	//	InFile >> fg; //This reads the foreground number 
	//	InFile.ignore(INT_MAX, '\t'); 
	//	InFile >> bg; //This reads the background number
	//	InFile.ignore(INT_MAX, '\n'); 
	//	//player.resize(3);
	//	zwei = new Sprite( playerName, pX, pY, (System::ConsoleColor)fg, (System::ConsoleColor)bg, last);
	//	InFile.close();
	//}

	zwei = new Sprite( playerName, pX, pY, ConsoleColor::Blue, ConsoleColor::Black, "|0|");
	//create the enemy sprite here. 
	ene[0] = new Sprite("Opponent", eX, eY, ConsoleColor::Blue, ConsoleColor::Red, "[0]");
	
	int bgNum = (rand() % 6) * 2 + 10;

	for(decltype(bgNum) i = 0; i < bgNum; i++)
		cell.push_back(Cell<>(0, 0, ConsoleColor::White, ConsoleColor::Black, L'\x2E'));

	eX = rand() % (Console::WindowWidth) >> 1;
	eY = rand() % Console::WindowHeight >> 1;


	/*Console::SetCursorPosition(eX, eY);
	ene[0]->Show();*/

	pX = (Console::WindowWidth) >> 1;
	pY = Console::WindowHeight >> 1;
	
	//mX = 30;
	//mY = 30;

	//miss[100].SetLeft(mX);
	//miss[100].SetTop(mY); 
	
	mX = mY = 0;
	missleX = missleY = 0;

	showFPS = true; //We are now using showFPS to show seconds. 
}

Game::~Game(void)
{
	delete zwei; // Maybe delete images here? 
	delete ene[0];
	//delete[] miss;
	for( unsigned int i = 0; i < missles.size(); i++)
	{
		delete missles[i];
		missles.erase(missles.begin() + i--);
	}

	for( unsigned int i = 0; i < eMissles.size(); i++)
	{
		delete eMissles[i];
		eMissles.erase(eMissles.begin() + i--);
	}
}

void Game::Ask()
{
	system("cls");
	cout << "Please type in your name, pilot..." << endl;
	
	getline(cin, playerName); //The proper way to do a getline function
	cout << "Welcome, Captain " << playerName << ". Allow me to debrief you." << endl;

	System::Console::SetCursorPosition((Console::WindowWidth - 31) >> 1, Console::WindowHeight - 1);
	system("pause");
	Console::Clear(); 

		int response; 
	cout << "Would like a rundown of the controls? (Type in the corresponding number)" << endl; 
	cout << "1) Yes\n"
	     << "2) No\n";
	for(;;)
	{
		if(cin >> response && cin.good())
		{
			break;
		} else {
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			cout << "Type in the corresponding number please...";
		}
	}

	//Check to see if they're a beginner or a pro.
	if(response == 1)
	{
		Console::Clear(); 
		cout << "Keyboard controls:\n"
			 << "Move:\t W,A,S,D keys\n"
			 << "\n"
			 << "Shoot:\t SpaceBar\n"
			 << "\n\n"
			 << "XBOX 360 Controller controls:\n"
			 << "Move:\t D-Pad\n"
			 << "\n"
			 << "Shoot:\t X Button\n";
		
		System::Console::SetCursorPosition((Console::WindowWidth - 31) >> 1, Console::WindowHeight - 1);
		system("pause");
		Console::Clear();
	} else if (response == 2){
		System::Console::SetCursorPosition((Console::WindowWidth - 31) >> 1, Console::WindowHeight - 1);
		Console::Clear();
	} //endif
}

void Game::Run()
{
	Console::CursorVisible = false; //Remove Cursor visibility. 
	start = time(nullptr); // Have the time from ctime set to the start member.
	Util::EOLWrap(false);//Do not wrap the end of line.
	Util::FlushKeys(); //Remove any and all input. 
	
	for (frame = 0; play; ++frame)
	{
		//The game will play here and stuff. 
		Refresh(); //Refresh each frame.
		Input(); //Wait for input
		AI(); // Move enemies and such. 	
	}
	Util::FlushKeys(); //Remove input for good measure.
	Util::EOLWrap(true); // Wrap the end of line. 
	Console::CursorVisible = true; // Make the cursor visible again.
}

void Game::Refresh()
{
	//Will be using the locking of the window because I was told it was better...
	LockWindowUpdate(GetConsoleWindow());
	Console::Clear(); // Also clear the screen to remove the last frames. 

	zwei->SetLeft(pX);
	zwei->SetTop(pY);
	Console::SetCursorPosition(pX, pY); //Set the cursor position the set data members.
	zwei->Show(); //Show the sprite.

	
	ene[0]->SetLeft(eX);
	ene[0]->SetTop(eY); 
	Console::SetCursorPosition(eX, eY);
	ene[0]->Show();

	for(decltype(cell.size()) i = 0; i < cell.size() ; i++)
	{	
		
		oX = rand() % Console::WindowWidth - 1;
		oY = rand() % Console::WindowHeight - 1;
		if(0 == frame % 2)
			cell[i].Show(oX, oY);
	}
	//Console::SetCursorPosition(mX,mY);
	//miss[100].Show();

	for( int i = 0; i < (int)missles.size(); i++)
	{
		//Missle::Delta missleX, missleY;
		dynamic_cast<Missle *>(missles[i])->GetDelta(mX, mY);
		if( mX || mY)
		{
			int missaddx = mX + missles[i]->GetLeft(), missaddy = mY + missles[i]->GetTop();
			if(missles[i]->OutOfBounds(missaddx, missaddy))
			{
				delete missles[i];
				missles.erase(missles.begin() + i);
			} else if (ene[0]->Collides(missaddx, missaddy, missles[i]->GetWidth(), missles[i]->GetHeight())){
				delete missles[i];
				missles.erase(missles.begin() + i);
				//Add score here.
				score += 10;
			} else {
				missles[i]->Show();
				missles[i]->SetLeft(missaddx);
				missles[i]->SetTop(missaddy);
			}
		}
	}

	for( int i = 0; i < (int)eMissles.size(); i++)
	{
		//Missle::Delta missleX, missleY;
		dynamic_cast<Missle *>(eMissles[i])->GetDelta(missleX, missleY);
		if( missleX || missleY)
		{
			int missaddx = missleX + eMissles[i]->GetLeft(), missaddy = missleY + eMissles[i]->GetTop();
			if(eMissles[i]->OutOfBounds(missaddx, missaddy))
			{
				delete eMissles[i];
				eMissles.erase(eMissles.begin() + i);
			} else if (zwei->Collides(missaddx, missaddy, eMissles[i]->GetWidth(), eMissles[i]->GetHeight())){
				delete eMissles[i];
				eMissles.erase(eMissles.begin() + i);
				//Decrease player health here.
				health--;
			} else {
				eMissles[i]->Show();
				eMissles[i]->SetLeft(missaddx);
				eMissles[i]->SetTop(missaddy);
			}
		}
	}

	if (showFPS) // Only do this while showing the frames per second is true. 
	{
		auto secs = time(nullptr) - start; // set seconds to the operation system's time.
		auto fps = 0 == secs ? 0 : frame / static_cast<double>(secs); //if seconds is == 0 then 0 else blah, blah.
		cout.precision(1); //a cout function for precision. 
		cout.setf(ios_base::showpoint); //a cout function to show the each point.
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout.width(6);
		Console::SetCursorPosition(0, Console::WindowHeight - 1);
		if( secs < 7)
		{
			if( x == 1)
				cout << "BGM: Street";
			else if(x == 2)
				cout << "BGM: Chase";
			else if(x == 3)
				cout << "BGM: Machine Beat";
			else if(x == 4)
				cout << "BGM: Badlands";
			else if(x == 5)
				cout << "BGM: Factory";
			else if(x == 6)
				cout << "BGM: Conflict";
			else if(x == 7)
				cout << "BGM: Shudder";
			else
				cout << "BGM: Metempsychosis";
		}
		Console::SetCursorPosition(0,0); //Sets the position of these words and stuff.
		cout << "Name:\t" << playerName << "\t" << "Score:\t" << score 
			<< "\t" << "Time:\t" << secs << "\t" << "Health:\t" << health;  
		savedSecs = (int)secs;
	}

	LockWindowUpdate(NULL); // Do not lock the window
	System::Threading::Thread::Sleep(10); //Sleep.
}

void Game::Input() // Waits for input
{
	if ((GetAsyncKeyState(VK_ESCAPE) & 1) || (health <= 0)) //Escape key ends the game.
	{
		Console::Clear();
		cout << "Name:\t" << playerName << "\tScore:\t" << score << "\tTime:\t" << savedSecs << endl;
		//SaveHighScores();
		
		/*ofstream out;
		out.open("scoresAndStats.bin", ios_base::out | ios_base::app | ios_base::binary);

		if(!out.is_open())
		{
			cerr << "File did not open!";
		} else {

			BinaryData bin;
			strncpy_s(bin.name, sizeof bin.name, playerName.c_str(), _TRUNCATE);
			bin.score = score;
			bin.time = savedSecs;
			out.write(reinterpret_cast<const char *>(&bin), sizeof bin);
		}*/

		//out.close();
		system("pause");
		play = false;
	}

	if (GetAsyncKeyState(VK_BACK)) //Backspace key resets frames
	{
		// Reset!
		frame = 0;
		start = time(nullptr);
	}

	if (GetAsyncKeyState(VK_F1) & 1) // f1 shows the frames per second.
		showFPS = !showFPS;
	
	if (GetAsyncKeyState(VK_SPACE) & 1)
	{
		if( mX || mY)
		{
			//Now setting up the necessary things for the missle. 
			missle = new Missle( "Missle", 
				(zwei->GetLeft() + (zwei->GetWidth() >> 1)), 
				(zwei->GetTop() + (zwei->GetHeight() >> 1)), ConsoleColor::Blue, ConsoleColor::Black, "*",
				mX, mY);

			missles.push_back(missle);
		}
		Console::Beep(500, 50);
		mY--;
	}

	int dX, dY;
	dX = dY = 0;
	if (GetAsyncKeyState('W')) --dY;
	if (GetAsyncKeyState('A')) --dX;
	if (GetAsyncKeyState('S')) ++dY;
	if (GetAsyncKeyState('D')) ++dX;

	//dX = rand() % 3 - 1;
	//dY = rand() % 3 - 1;

	// GamePad
	// References... Add New Reference... .NET "Microsoft.Xna.Framework"
#if 0
	using namespace Microsoft::Xna::Framework;
	using namespace Microsoft::Xna::Framework::Input;
	auto gps = GamePad::GetState(PlayerIndex::One);
	auto hasGP = gps.IsConnected;
	if (hasGP)
	{
		if (ButtonState::Pressed == gps.Buttons.Back)
			play = false;
		if (ButtonState::Pressed == gps.Buttons.A)
			Console::Beep(500, 250);
		auto dp = gps.DPad;
		if (ButtonState::Pressed == dp.Down) ++dY;
		if (ButtonState::Pressed == dp.Left) --dX;
		if (ButtonState::Pressed == dp.Right) ++dX;
		if (ButtonState::Pressed == dp.Up) --dY;
		auto ts = gps.ThumbSticks;
		auto v = ts.Left;
		auto const Zero = .25;
		if (v.X < -Zero) --dX;
		if (v.X > Zero) ++dX;
		if (v.Y < -Zero) ++dY;
		if (v.Y > Zero) --dY;
	}
	if (hasGP)
		GamePad::SetVibration(PlayerIndex::One, 0.0, 0.0); // 1.0
#endif

	if (dX || dY) //For collision
	{
		int newX = pX + dX, newY = pY + dY;

		if (newX < 0 || newY < 0 ||
			newX > Console::WindowWidth - zwei->GetWidth()  ||
			newY >= Console::WindowHeight - zwei->GetHeight() || 
			ene[0]->Collides(newX, newY, zwei->GetWidth(), zwei->GetHeight()) == true )
		{
			//Do nothing.
		}else{
			pX = newX;
			pY = newY;
		}
		if(ene[0]->Collides(newX, newY, zwei->GetWidth(), zwei->GetHeight()) == true)
			health -= 10;
	}
}

void Game::AI()
{
	//LockWindowUpdate(GetConsoleWindow());
	//Console::Clear();
	
	if (0 == frame % 5)
	{
		//Move the enemy around randomly for now.
		int deltaX, deltaY;
		//deltaX = deltaY = 0;
		deltaX = rand() % 3 - 1;
		deltaY = rand() % 3 - 1;

		missleY = rand() % 3 - 1;
		missleX = rand() % 3 - 1;

		if (deltaX || deltaY) //For collision
		{
			int neweX = eX + deltaX, neweY = eY + deltaY;

			if (neweX >= 0 && neweY >= 0 &&
				neweX <= Console::WindowWidth - 1  &&
				neweY <= Console::WindowHeight - 1 &&
				!zwei->Collides(neweX, neweY, ene[0]->GetWidth(), ene[0]->GetHeight()) == true)
			{
				eX = neweX;
				eY = neweY; 
				
				if( missleX || missleY)
				{
					//Now setting up the necessary things for the missle. 
					eMissle = new Missle( "Missle", 
						(ene[0]->GetLeft() + (ene[0]->GetWidth() >> 1)), 
						(ene[0]->GetTop() + (ene[0]->GetHeight() >> 1)), ConsoleColor::Red, ConsoleColor::Black, "+",
						missleX, missleY);

					eMissles.push_back(eMissle);
				}
			}else{
				//Do nothing.	
			}
		}
	}
}
