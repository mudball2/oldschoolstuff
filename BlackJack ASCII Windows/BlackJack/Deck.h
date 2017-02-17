#ifndef DECK_H
#define DECK_H

//Include the stack.h....because a labby said that's how it should be done 
#include "Stack.h" 


#include "Card.h" 
class CDeck
{
	//Set up the private data members
private:
	//Set up the array of cards(52)[0->51]
	CCard m_nArrDeck[52];
	CCard b; 
public:
	bool hideCard;
private:
	int c; //This is my counter variable
	//Set up the stack class
	CStack stk;
	/*
	struct tDeckOrder
	{
		//Setup the linked list by creating the "top". 
		CCard theCard; 
		tDeckOrder* theNext;
	};
	tDeckOrder* theTop; 
	*/ // We HAVE a pre-set linked list through the stack class. We simply include the stack class. 
public:
	CDeck(void);
	~CDeck(void);

	//Set up the other methods
	void Shuffle(void);
	int Draw(void);
	bool IsEmpty(void);
	void CardsLeft(void);
};

#endif