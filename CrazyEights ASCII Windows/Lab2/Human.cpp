#include "Human.h"


CHuman::CHuman(void)
{
	//Initialize the data member and set a default name
	m_szHumName = NULL; 
	SetName("Player"); 
}


CHuman::~CHuman(void)
{
	//Nothing to deallocate here 
}

const char* CHuman::GetName(void) const// This will return the name with all it's might!
{
	//Stuff goes here.
	return m_szHumName; //Returns a random 0 for now...
}

void CHuman::SetName(const char* szName) //This will take in an address paramter of a character...if that's right. 
{
	//It is going to take in the name and then store or something...blah, blah...
	
	//Delete any existing memory for the string
	delete[] m_szHumName; 

	//Call "new" on the char pointer because it is now dynamically allocated
	m_szHumName = new char [strlen(szName)+1]; 

	//Now copy the strings 
	strcpy_s(m_szHumName, strlen(szName)+1, szName); 
}

void CHuman::Ask(void)
{
	
	//Set up an array local to the function so we can set the name
	char szPlayerBuffer[NAME_LEN]; 

	//Instruct the player
	cout << "Type in your name, por favor... ______________\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

	//Use the array data member for the input and stuff 
	for( ; ; )
	{	
		if(cin.get(szPlayerBuffer, NAME_LEN))
		{
			//Remove the extra input
			cin.ignore(INT_MAX, '\n'); 
			break;
		}

		cin.clear();
		cin.ignore(INT_MAX, '\n'); 	
	}//end for loop

	SetName(szPlayerBuffer); //Will use it when we have it. 
		
	cout << "Hello, " << m_szHumName << endl; 
}

void CHuman::Show(void)
{
	//Simply calls the base class's Show() function 
	CPlayer::Show(); 
	cout << m_szHumName << endl; //Will show what it needs to in player and show it's own member... 
}
