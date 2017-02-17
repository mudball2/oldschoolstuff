#include "Player.h"
#include "Computer.h" 
#include "Human.h" 
#include <iostream>
using namespace std; 

#include <ctime>

#include "Color.h" 
using namespace FS; 

//Defaut Constructor
CPlayer::CPlayer(void)
{
	//Start writing the method for the constructor
	//strcpy_s( m_szPlayerName, MAX_LEN, "Default");

	//m_nPlayerScore = 20; 
	

}

//Creating an overloaded Constructor so there is something to display
CPlayer::CPlayer( const char*, int)
{
	//Get the values for the data members 
}


//New methods for cards (Lab 2) 
void AddCard(void)
{
	//Add the stuff here
}

void Discard(void)
{
	//No need for a discard function in Blackjack....lo siento!! 
}

//Destructor
CPlayer::~CPlayer(void)
{
	//Nothing to deallocate at this point. 
}

//Define the accessors and stuff
int GetScore() 
{
	//Enter the stuff here (return a value only)
	return 0; //Returns 0 for now...
}

const char* GetName()
{
	return 0; 
}


//New Clear method (Lab 2)
void Clear(void)
{
	//Add the stuff here 
}

//Virtual Show() function 
void CPlayer::Show() 
{
	cout << White << endl; 
	//cout << "Name: " << CHuman::szPlayerName << endl; 

	cout << Blue << endl; 
	//cout << m_szPlayerName << " Value: " << m_nPlayerScore << endl; 
	cout << endl; 
}
