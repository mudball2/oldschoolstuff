#include "Player.h"


CPlayer::CPlayer(void) : m_nmaxHandSize(8) // Using the member initializer list to make max hand size 8. 
{
	//Try to default the scores and names and such
	m_ccardArr = new CCard[5]; //We use 'new' to dynamically allocate the pointer, so it can be treated as 
							   //an array. We give it a fixed size of 5. (NOTE: Crazy Eights should be eight.)
	m_nplayerScore = 10; 
}

//This method will take in a card and add it to the array, only if there is an empty index. 
//It will return a bool to indicate success or failure. 
bool CPlayer::AddCard(CCard& newCard)
{
	//Add the stuff here and return true for now...
	for(int i = 0; i < m_nmaxHandSize; i++)
	{
		m_ccardArr[i] = newCard;

		//Success!
		++m_ncurrNumCards; 
		return true;
	}
	return false; 
}


//This method takes in a card to remove. 
void CPlayer::Discard( int cardToRemove) //Can return the card, but the array must be re-arranged. 
{
	m_ccardArr[cardToRemove]; //Will set whatever card we need to go away to NULL.

	--m_ncurrNumCards; //Decrease the current amount of cards. 
}

//Accessors and mutators for the data members
void CPlayer::SetScore(int nScore)
{
	m_nplayerScore = nScore;  
}

int CPlayer::GetScore(void)
{
	return m_nplayerScore; 
}

//This method sets the array back to 0. 
void CPlayer::Clear(void)
{
	delete[] m_ccardArr;
	m_ccardArr = NULL;
}

CPlayer::~CPlayer(void)
{
	//Nothing to deallocate yet...
}

//And now...we want to explicity write out the copy constructor and assignment operator for this class
CPlayer& CPlayer::operator=( const CPlayer& rhs) // We use and address of the class for both the return type and parameter 
{										// for the assigment operator in this class...and most others. 
	//Do some deep copies
	if( this != &rhs)
	{
		
		m_ccardArr = rhs.m_ccardArr;

		//m_nmaxHandSize = rhs.m_nmaxHandSize; Seems it does not need to be here anymore since it isn't modifiable. 
		m_ncurrNumCards = rhs.m_ncurrNumCards;
		m_nplayerScore = rhs.m_nplayerScore;

	}

	return *this; //Then we return a this dereference...
}

CPlayer::CPlayer( const CPlayer& copy ) : m_nmaxHandSize(8) //And this is the correct way to prototype a Copy Constructor...as far as I know.
{                                         //^-- We are initializing the max hand size here as well (So the compiler will shut up). 
	//We just do deep copies of all the data members...
	
	m_ccardArr = NULL;
	m_ccardArr = copy.m_ccardArr;

	//m_nmaxHandSize = copy.m_nmaxHandSize; Seems it does not need to be here anymore since it isn't modifiable.
	m_ncurrNumCards = copy.m_ncurrNumCards;
	m_nplayerScore = copy.m_nplayerScore;
}

void CPlayer::Show(void)
{
	//Display the name, score, and the cards that are being displayed in the hand. 
	cout << "Name:\t "; //m_szplayerName << "\t\tScore:\t" << GetScore() << endl; 
}