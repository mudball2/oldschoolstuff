#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

//Include this file, just in case 
#include <iostream>
using namespace std; 

//Preprocessor define for the name
#define NAME_LEN 64

class CPlayer
{
private:
	CCard* m_ccardArr;
	const int m_nmaxHandSize; //Changing this variable into a const int as opposed to just an int
	int m_ncurrNumCards; 

	int m_nplayerScore; 
public:
	CPlayer(void);

	//This method will take in a card and add it to the array, only if there is an empty index. 
	//It will return a bool to indicate success or failure. 
	bool AddCard(CCard& newCard); 

	//This method takes in a card to remove. 
	void Discard( int cardToRemove); //Can return the card, but the array must be re-arranged. 

	//Accessors and mutators for the data members 
	int GetScore(void); //Just returns what the score is 
	//char GetName(void); //Just returns the name default if nothing else is written. 
	void SetScore(int nScore); //Takes in a paramter and sets the data member associated with that to whatever is entered.
	//void SetName(const char* szName); //Should somehow assign the character data member to "Default". 


	//This method sets the array back to 0. 
	void Clear(void); 

	//And now...we want to explicity write out the copy constructor and assignment operator for this class
	CPlayer& operator=( const CPlayer& rhs); // We use and address of the class for both the return type and parameter 
											 // for the assigment operator in this class...and most others. 

	CPlayer( const CPlayer& obj ); //And this is the correct way to prototype a Copy Constructor...as far as I know.

	//This method should be updated so that it can display the current amount of cards and show them 
	virtual void Show(void); //Making the show function virtual for polymorphism on the derived classes that also use it. 
	
	//Destructor
	virtual ~CPlayer(void) = 0;
};

#endif 