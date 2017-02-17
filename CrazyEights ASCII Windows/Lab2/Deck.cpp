#include "Deck.h"

//Including the files so we can use certain methods and such 
#include "Card.h"
#include <ctime> // This will be for the randomness and such....if we need it, because the cards already have it. 

CDeck::CDeck(void)
{
	//We will create the deck here with the card commands and such... 

	//Seeding RNG
	srand(unsigned int (time(0))); 

	//By doing this we shall create a nested loop, because we know it works... 
	//And don't forget to creates a counter variable for this little guy.
	int c = 0; 
	for(int i = 3; i <= 6; i++ )
	{
		for( int j = 2; j <= 14; j++)
		{
			//Set up the deck using the array and stuff. 
			deckArray[c].SetSuit(i); 
			deckArray[c].SetFace(j); 
			//deckArray[c].Show(); // This is to test to see if it works. (Trying it in main)
			c++;
		}
	} // end of for loop 
}

//Adding the other methods and such here... 
void CDeck::Shuffle(void) //Cleans out the stack, mixes the values of the array and pushes all the values onto the stack...he's a busy guy.
{
	//So now we will create a random deck. 
	for(int i = 0; i < 100; i++)
	{
		int randIndex1 = rand()%52; //According to this nut next to me, we need one only. 
		int randIndex2 = rand()%52;
		swap(deckArray[randIndex1], deckArray[randIndex2]); 
	} // end for loop 

	for(int i = 0; i < 52; i++)
	{
		stack.Push(deckArray[i]); //Pushing all values onto the stack and stuff...
		//deckArray[i].Show(); 
	}

}

CCard CDeck::Draw(void) // Will return the topmost card from the stack. 
{
	for(int i = 0; i < 52; i++)
	{
		//Return the topmost card now.
		stack.Pop(deckArray[i]);
		//deckArray[i].Show(); 
		return deckArray[i];
	} 
}

bool CDeck::IsEmpty(void) //Returns true if there is nothing in the stack. When drawing a card, make sure it isn't empty first. 
{
	//Will check if the stack is equal to NULL and will return true if it is. Otherwise, return false.
	if( stack.Peek() == NULL)
		return true;
	else 
		return false;
}

int CDeck::CardsLeft(void) //Returns the number of cards left in the deck (probably could be used for IsEmpty() method). 
{
	//This will use the stack's accessor that we write and return the current size. 
	return stack.GetSize(); 
}

CDeck::~CDeck(void)
{
	//Seems that there's nothing to deallocate in this particular class. 
}
