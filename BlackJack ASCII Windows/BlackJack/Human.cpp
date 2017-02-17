#include "Human.h"



CHuman::CHuman(void)
{
	m_szPlayerName = NULL;
	SetName("Player"); 
}


CHuman::~CHuman(void)
{
	//Deallocate the dynamic memory for the char pointer
	delete[] m_szPlayerName;
}

//Copy constructor
CHuman::CHuman(const CHuman& copy)
{
	m_szPlayerName = NULL;
	SetName(copy.m_szPlayerName);
}

const char* CHuman::GetName( void ) const
{
	return m_szPlayerName;
}

void CHuman::SetName( const char* szPlayerName)
{
	//Delete any existing memory
	delete[] m_szPlayerName; 

	//Call "new" on the char pointer because it is now dynamically allocated
	m_szPlayerName = new char [strlen(szPlayerName)+1]; 

	//Now copy the strings 
	strcpy_s(m_szPlayerName, strlen(szPlayerName)+1, szPlayerName); 
}

//Write out the Ask() function 
void CHuman::Ask(void)
{
	
	//Set up an array local to the function so we can set the name
	char szPlayerBuffer[MAX_LEN]; 
	//Write the stuff here...
	cout << "What's your name, friend? ______________\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

	//Use the array data member for the input and stuff 
	for( ; ; )
	{
		
		
		if(cin.get(szPlayerBuffer, MAX_LEN))
		{
			//Remove the extra input, if any
			cin.ignore(INT_MAX, '\n'); 
			break;
		}

		cin.clear();
		cin.ignore(INT_MAX, '\n'); 

		
		
	}

	SetName(szPlayerBuffer); 
		
	cout << "Welcome, " << m_szPlayerName << endl; 
}

void CHuman::Show(void)
{
	//Enter the stuff here

	//Having troubles using the virtual derived function of the class and such
	//CPlayer::Show(); 
	cout << FS::Green << m_szPlayerName << Default << BG_Default << endl; 

}
