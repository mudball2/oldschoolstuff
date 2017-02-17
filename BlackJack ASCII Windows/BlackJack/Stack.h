#ifndef STACK_H_
#define STACK_H_

#include "stdafx.h"
#include "Card.h"
/*
	// A fixed-size array would work for something like (Ms.) Pac-Man
	CGhost ghosts[4];
	
	int nNumRacers;
	// Somehow figure out how many racers there are, and then
	// allocate that many.
	CForzaCar *pRacers = new CForzaCar[nNum];

	// How could you handle the enemies in Geometry Wars?
	CEnemy* pEnemies = new CEnemy[100];


	Arrays
	=========
	- Fixed-size
	+ Contiguous memory (this makes them fast)
	+ Random-access iteration (via [] indexing or ptr arithmetic)

	Linked lists
	============
	+ Variable in size (can grow or shrink)
	- Non-contiguous memory (not as fast)
	- No [] indexing or ptr arithmetic
*/

/*
	Stack ordering is First In, Last Out (FILO), or
					  Last In, First Out (LIFO)

	Examples:
			Vending Machine
			PEZ dispensers
			Pringles
			Bullets in a magazine (deadlier PEZ)
			Plates at a buffet
			A deck of cards
*/

// We need to keep the code inside the list generic
// A typedef is basically an alias for a datatype
// Similar to #define Item int
typedef CCard Item;

// Linked lists and other data structures can also be called
// Abstract Data Types (ADTs)

// A stack using a singly linked list
class CStack
{
private:

	// Only the stack class has access to the node struct.
	// When you create a new datatype inside of a class or struct
	// (like our node), this is known as nesting (kind've like
	// nested for loops)

	// A linked list is basically a series of nodes tied
	// together with pointers
	struct tNode	// a struct is basically a class with a default
	{				// access type of public (at least in C++)
		Item data;		// The thing we're storing
		tNode* pNext;	// This points to the next node in the list
	};

	tNode* m_pTop;	// This will point to the most recently added node

	int m_nCount;	// Number of nodes currently allocated

public:

	// Default constructor
	// This will create an empty stack
	CStack(void);
	
	// Destructor
	// Clean up our dynamic memory
	~CStack(void);

	/* 
		Warning: Don't make copies of this class.
		It will break your program.
	*/

	// Add an Item to the top of the stack
	// In:	info		The Item to add
	// 
	// Return: True, if the add was successful
	bool Push(const Item& info);

	// Remove the top-most Item from the stack
	// In:	info		A "blank" Item
	// 
	// Out:	info		The Item that was at the top
	// Return: True, if something got removed
	bool Pop(Item& info);

	// Take a look at the Item on the top of the stack
	//
	// Return: The pointer to the Item at the top
	const Item* Peek() const
	{
		// If there's something there,
		// return the address of the Item at the top
		if(m_pTop)
			return &m_pTop->data;
		// Otherwise, return a NULL ptr
		return NULL;
	}

	// An accessor to get the count
	// But I'll let you guys write that one.
};

#endif