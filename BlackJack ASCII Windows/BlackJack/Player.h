//Header protection first 
#ifndef PLAYER_H
#define PLAYER_H

//Constant for character length
#define MAX_LEN 32

//Constant for card array
#define MAX_HAND 5 

class CPlayer
{
	//Set the private data members for the game 
private:
	//Lab 2- a new fixed-sized card array 
	int m_nCard[MAX_HAND];
	//Lab 2- a data member for the maximum size of hand
	int m_nMaxSizeHand;
	//Now a data member for the current number of cards in hand (Lab 2)
	int m_nCurrentHandSize;
	
public:
	//Default constructor
	CPlayer(void);

	//Overloaded constructor
	CPlayer( const char* , int); 

	//New methods for cards (Lab 2) 
	void AddCard(void);
	void Discard(void);


	//Class destructor
	~CPlayer(void);

	//Create the accessors here 
	//Use the const keyword to protect the data (invoking object) 
	int GetScore() const; 
	const char* GetName() const; 

	//New Clear method (Lab 2)
	void Clear(void); 

	//Our virtual Show() function 
	virtual void Show(void); 
};

#endif