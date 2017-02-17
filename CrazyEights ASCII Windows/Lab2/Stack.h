#ifndef STACK_H_
#define STACK_H_


#include "stdafx.h" //Including stdafx.h so the compiler will shut up and leave me alone. 
#include "Card.h"  //Including the Card.h so that we can use a CCard typedef for the stack. 

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

//Change this into a CCard item for the game
//typedef CCard Item; // We no longer need this because now we're creating a template class 

// Linked lists and other data structures can also be called
// Abstract Data Types (ADTs)

//CREATING our template class...
template<typename Item>

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

	//WOULD put Copy Constructor and Assignment Operator here if need be...

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
	// But I'll let you guys write that one. [I guess that means I write code here] 
	int GetSize(void); //Declaring the accessor.
};

//WE move our .cpp definitions here for the class templating...
// Default constructor
// This will create an empty stack
template<typename Item>
CStack<Item>::CStack(void)
{
	// NULL is going to represent that we've got an empty stack
	// If you don't set top to NULL in the ctor (constructor), then
	// it will be pointing at garbage and bad things will happen.
	m_pTop = NULL;
	m_nCount = 0;
}

// Destructor
// Clean up our dynamic memory
template<typename Item>
CStack<Item>::~CStack(void)
{
	// Creating the pointer outside of the loop ensures
	// that the memory only gets allocated once.
	tNode* pTmp;

	for(int i = 0; i < m_nCount; ++i)
	{
		// In order to avoid a memory leak, we need a temporary ptr
		pTmp = m_pTop;
		// Now move the top down to its own next
		m_pTop = m_pTop->pNext;
		// Clean up the old memory
		delete pTmp;
	}
}

/* 
Warning: Don't make copies of this class.
It will break your program.
*/

// Add an Item to the top of the stack
// In:	info		The Item to add
// 
// Return: True, if the add was successful
template<typename Item>
bool CStack<Item>::Push(const Item& info)
{
	// There's no space upfront in a linked list.
	// If you want to add something, you have to dynamically
	// allocate the space for it.
	tNode* pNode = new tNode;

	// If new can't find a chunk of memory big enough to allocate
	// a node (or whatever datatype you're allocating), it will
	// return a NULL ptr
	if(NULL == pNode)
		return false;

	// Now that we have some space, we can copy over the data
	pNode->data = info;

	pNode->pNext = m_pTop;

	// Update the top pointer, because we added something new
	m_pTop = pNode;

	// Success
	++m_nCount;
	return true;
}

// Remove the top-most Item from the stack
// In:	info		A "blank" Item
// 
// Out:	info		The Item that was at the top
// Return: True, if something got removed
template<typename Item>
bool CStack<Item>::Pop(Item& info)
{
	// Check to see if the list is empty
	if(!m_pTop)
		return false;

	// Go ahead and grab the data from the top
	info = m_pTop->data;

	// Update the stack to show that we've removed a node
	
	// In order to avoid a memory leak, we need a temporary ptr
	tNode* pTmp = m_pTop;
	// Now move the top down to its own next
	m_pTop = m_pTop->pNext;
	// Clean up the old memory
	delete pTmp;

	// Success!
	--m_nCount;
	return true;
}

template<typename Item>
int CStack<Item>::GetSize(void)
{
	//Returns the count that increments and decrements based on the Pop() and Push() methods. 
	return m_nCount; 
}

#endif