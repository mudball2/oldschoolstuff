#include "stdafx.h"
#include "Menu.h"

#include "BinaryData.h"

void playFunc()
{
	//cout << "Play!\n";

	//We shall probably put all of the play code inside of here.
	system("pause");
}

void highScoresFunc()
{
	system("cls");
	cout << "HighScores!\n";
	ifstream ifile;
	ifile.open("highScores.txt");
	string nme;
	int scre, tm;
	ifile >> nme; 
	ifile.ignore(INT_MAX,'\t');
	ifile >> scre; 
	ifile.ignore(INT_MAX,'\t');
	ifile >> tm;
	ifile.ignore(INT_MAX,'\n');
	cout << nme << ' ' << scre << ' ' << tm << '\n';
	ifile.close(); 
	cout << "\n\n";
	//in.open("scoresAndStuff.dat");
	ifstream in;
	in.open("scoresAndStuff.bin", ios_base::in | ios_base::binary); 
	
	if (!in.is_open())
	{
		cout << "It didn't work...";
	} else {

	// Determine how many records are in the binary file.

		if (in.good())
			in.seekg(0, ios_base::end); 
		int num = 0, fileSize = 0;
		if (in.good())
			fileSize = (int)in.tellg(); 
		num = fileSize / (sizeof BinaryData); 
		in.seekg(0);
		vector<BinaryData> all(num);
		BinaryData *everyone = new BinaryData[num];
		in.read((char *) everyone, fileSize); 

		if(num != 0)
		{
			delete[] everyone;
			num = 0;
		} else if (in.good()) {

			in.seekg(0); 
			in.read((char *) everyone, fileSize); 
		}
		in.close();
	}
	system("pause");
}

void creditsFunc()
{
	system("cls");
	//Temp credits
	System::Console::ForegroundColor = ConsoleColor::White;
	cout << "Created and Developed by:\n"
		 << "MUDBALL GAMES\n"
		 << "\n"
		 << "Inspired by \"Einhander\" from SquareSoft\n"
		 << "Programmer: Gabriel Islas\n"
		 << "Programmed in C++\n"
		 << "Also used FMOD API\n"
		 << "\n\n"
		 << "Music: Kenichiro Fukui\n"
		 << "\n"
		 << "Producer: Arthur Johnson\n"
		 << "\n\n"
		 << "Special Thanks:\n"
		 << "Tyler Hemingway\n"
		 << "Hunter Hayes\n"
		 << "Arthur Johnson\n"
		 << "Jessica Lynn Dery\n"
		 << "\n\n";
	//System::ConsoleColor::ForegroundColor = ConsoleColor::Red;
	cout << "THANKS FOR PLAYING!";
	Console::ResetColor();
	system("pause");
}

void exitFunc()
{
	cout << "Exit!\n";
	//system("pause"); //No pause, so it should let us out of the game immediately. 
}

void Menu::load()
{
	char* itemNames[NUM_ITEMS] = { "Play", "Scores", "Credits", "Exit", };

	void(*FuncArr[4])() =
	{
		playFunc,
		highScoresFunc,
		creditsFunc,
		exitFunc
	};

	for( int i = 0; i < 4; i++)
	{
		m_items[i].set(itemNames[i],(*FuncArr[i]));
	}

}

void Menu::display() const
{
	LockWindowUpdate(GetConsoleWindow());
	system("cls");
	cout << "MAIN MENU:\n";
	for(int i = 0; i < NUM_ITEMS; ++i)
	{
		if(m_index == i)
			cout << "	-->";
		cout << '\t' << m_items[i].getName() << '\n';
	}
	LockWindowUpdate(0);
	Sleep(1);
}

void Menu::input()
{
	if(GetAsyncKeyState('S') & 1)
	{
		m_index = m_index + 1 < NUM_ITEMS ? m_index + 1 : 0;
	}
	else if(GetAsyncKeyState('W') & 1)
	{
		m_index = m_index - 1 >= 0 ? m_index - 1 : NUM_ITEMS - 1;
	}
	else if(GetAsyncKeyState(VK_RETURN) & 1)
	{
		m_items[m_index].execute();
	}
}