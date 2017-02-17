#include "Stack.h"


// Default constructor
// This will create an empty stack
CStack::CStack(void)
{
	// NULL is going to represent that we've got an empty stack
	// If you don't set top to NULL in the ctor (constructor), then
	// it will be pointing at garbage and bad things will happen.
	m_pTop = NULL;
	m_nCount = 0;
}

// Destructor
// Clean up our dynamic memory
CStack::~CStack(void)
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
bool CStack::Push(const Item& info)
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
bool CStack::Pop(Item& info)
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