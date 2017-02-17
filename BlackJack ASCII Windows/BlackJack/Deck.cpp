#include "Deck.h"
#include "Card.h" 
#include "Stack.h" 

#include <iostream>
using namespace std;

#include <Color.h>
using namespace FS;

#include <ctime>

CDeck::CDeck(void)
{
	/*
		The easiest way to do this is by using a nested for loop (a for loop inside of another for loop).  
		Use the outer loop as your “suits” loop (3-6), and the inner one as your “faces” loop (2-14).  
		Inside of the inner loop, call your SetFace and SetSuit modifiers for the current card, and give 
		them the looping variables.  You’ll also need a “counter” variable, since neither loop runs 0-51.
	*/
	//srand(unsigned int (time(0))); 

	//Initialize the counter variable for the stack
	c = 0; //This is my counter variable

	int count = 0;
	for( int j = 3; j <= 6; j++)
	{
		for( int i = 2; i <= 14; i++)
		{	
			b.SetSuit(j); 
			b.SetFace(i);
			m_nArrDeck[count]= b;
			
			count++; 
		
		}

	} 

	hideCard = false; 
	
}


CDeck::~CDeck(void)
{
	//Nothing to deallocate yet...
}


//Set up the other methods

//This method pushes on to the stack
void CDeck::Shuffle(void)
{ 
	srand(unsigned int (time(0))); 
	for( int i = 0; i < 52; i++)
	{
			int rCard = rand()%52; 
			int rCard2 = rand()%52; 

			b = m_nArrDeck[rCard];
			m_nArrDeck[rCard] = m_nArrDeck[rCard2];
			m_nArrDeck[rCard2] = b;
			//b.GetValue(); 
			
	}


	for( int i = 0; i < 52; i++)
	{
		stk.Push(m_nArrDeck[i]); //CCard object gets the random card, which gets a random value	
		c++;
	}
 
}

//This method returns the top most card
int CDeck::Draw(void) 
{
	stk.Pop(b); 
	
	if( hideCard == false)
		cout << FS::BG_Gray << FS::White; 
	else
		cout << FS::BG_Gray << FS::Gray;
	b.Show();
	cout << BG_Default;
	cout << " "; 
	return b.GetValue(); 
	--c; 
}

//This method will return true if they are no cards left in the deck
bool CDeck::IsEmpty(void)
{
	if( c == 0){
		return true;
	}

	//return false
	return false;
}

//The method will return the number of cards left
void CDeck::CardsLeft(void)
{
	cout << c; 
}
