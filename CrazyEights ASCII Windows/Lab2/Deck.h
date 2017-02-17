#ifndef DECK_H
#define DECK_H

//Probably want to include the card class for this sucker and the stack
#include "Card.h"
#include "Stack.h" 

class CDeck
{
private:
	CCard deckArray[52]; //An array of 52 cards
	//We will have our stack working us as well (no, I don't have a multi-personality disorder, I'm just crazy.)
	CStack<CCard> stack; //We are using CCard type items for the stack, so it MUST be defined...(Because it is Templated).
public:
	//Default constructor
	CDeck(void);	//Will create our deck for us. 

	//Adding the other methods and such here... 
	void Shuffle(void); //Cleans out the stack, mixes the values of the array and pushes all the values onto the stack...he's a busy guy.

	CCard Draw(void); // Will return the topmost card from the stack. 

	bool IsEmpty(void); //Returns true if there is nothing in the stack. When drawing a card, make sure it isn't empty first. 

	int CardsLeft(void); //Returns the number of cards left in the deck (probably could be used for IsEmpty() method). 

	~CDeck(void);	//Will probably delete any dynamic memory when it comes to it. 
};

#endif