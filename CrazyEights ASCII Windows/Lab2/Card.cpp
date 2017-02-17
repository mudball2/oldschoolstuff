#include "Card.h"

//including some files, just in case 
#include <iostream>
#include <ctime>

using namespace std;

CCard::CCard(void)
{
	//For now, the constructor here will just seed a random number generator to display a random card.
	srand(unsigned int (time(0))); 
	//For now, the random assignment will be in the constructor until the methods below become 
	m_nCardValue = rand()%(14-2+1)+2; 
	m_szCardSuit = rand()%(6-3+1)+3; 
}

//Now we put some of the other methods here. 
//Create the the accessors, they will return values based on what the mutator takes in.  

int CCard::GetFace()
{
	// Nothing yet. May just show faces as needed in the Show() method.
	return 0; // Just returns 0 for now. 
}
	
//Create the mutators, they will mess with the data members (take in arguements) and return their values. 
void CCard::SetSuit(char szCardSuit)
{
	//szCardSuit = rand()%(6-3+1)+3; // Getting rid of these now because now the Shuffle() method in Deck will take care of it. 
	CCard::m_szCardSuit = szCardSuit; 
}

void CCard::SetFace(int nCardVal)
{
	//First have the integer take in a card value 
	//nCardVal = rand()%(14-2+1)+2; // Getting rid of these now because now the Shuffle() method in Deck will take care of it.
	CCard::m_nCardValue = nCardVal; 
}

int CCard::GetValue()
{
	//Should just return a value 
	return m_nCardValue; 
}

char CCard::GetSuit()
{
	return m_szCardSuit;
}

//Now we define the overloaded insertion operator
ostream& operator<<( ostream& os, const CCard& rhs)
{
	//Will define as needed for certain objects
	//
	//Would look like:
	// os << rhs.anyMethod(); 
	return os; 
}

//Now create a show function to show the card. 
//This will simply show the card result 
void CCard::Show(void) const
{
	//Check the card value, and display it with a character instead of a number
	if ( m_nCardValue == 11) 
		cout << 'J' << m_szCardSuit << " ";
	else if ( m_nCardValue == 12)
		cout << 'Q' << m_szCardSuit << " ";
	else if ( m_nCardValue == 13 )
		cout << 'K' << m_szCardSuit << " ";
	else if ( m_nCardValue == 14 )
		cout << 'A' << m_szCardSuit << " ";
	else 
		cout << m_nCardValue << m_szCardSuit << " "; 
}


CCard::~CCard(void)
{
	//Nothing to deallocate yet... 
}
