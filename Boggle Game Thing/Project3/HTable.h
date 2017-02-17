#ifndef H_TABLE_H
#define H_TABLE_H

#include "SLList.h"
#include <fstream>

template<typename Type>
class HTable
{

	unsigned int numBuckets;
	SLList<Type>* arr;
	SLList<Type>* theTable;
	unsigned int (*hFunc)(const Type& v);
public:
	/////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function
	//                          for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int (*hFunction) (const Type &v));

	/////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys a hash table
	/////////////////////////////////////////////////////
	~HTable();

	/////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////
	HTable<Type>& operator=(const HTable<Type>& assign);

	/////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////
	HTable(const HTable<Type>& copy);

	/////////////////////////////////////////////////////
	// Function : insert
	// Parameters : v - the item to insert into the hash table
	/////////////////////////////////////////////////////
	void insert(const Type& v);

	/////////////////////////////////////////////////////
	// Function : findAndRemove
	// Paramters : v - the item to remove(if it is found)
	/////////////////////////////////////////////////////
	bool findAndRemove(const Type& v);

	/////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the hash table
	/////////////////////////////////////////////////////
	void clear();

	/////////////////////////////////////////////////////
	// Function : find
	// Paramters : v - the item to look for
	// Return : the bucket we found the item in or -1 if we
	//          didn't find the item.
	/////////////////////////////////////////////////////
	int find(const Type& v) const;


};

/////////////////////////////////////////////////////
// Function : Constructor
// Parameters : numOfBuckets - the number of buckets
//              hFunction - pointer to the hash function
//                          for this table
// Notes : constructs an empty hash table
/////////////////////////////////////////////////////
template<typename Type>
HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int (*hFunction) (const Type &v))
{
	
	numBuckets = numOfBuckets;
	arr = new SLList<Type>[numBuckets];
	hFunc = hFunction;
}

/////////////////////////////////////////////////////
// Function : Destructor
// Notes : destroys a hash table
/////////////////////////////////////////////////////
template<typename Type>
HTable<Type>::~HTable()
{
	for(unsigned int i = 0; i < numBuckets; i++)
	{
		arr[i].clear();
	}
	delete [] arr;
}

/////////////////////////////////////////////////////
// Function : Assignment Operator
/////////////////////////////////////////////////////
template<typename Type>
HTable<Type>& HTable<Type>::operator=(const HTable<Type>& assign)
{
	if( this != &assign)
	{
		//Clearing our array.
		this->clear();
		delete [] arr;

		if(assign.numBuckets == 0) //Checking if number of buckets is equal to 0.
			return *this;
		
		arr = new SLList<Type>[assign.numBuckets]; // Creating array again.

		numBuckets = assign.numBuckets; //Setting class's number of buckets to assign's.

		this->hFunc = assign.hFunc; //Setting the invoking object's hFunc to assign's. 

		for(unsigned int i = 0; i < numBuckets; i++)
		{
			arr[i] = assign.arr[i]; // Setting our class array to assign's array.
		}

	}
	return *this;
}

/////////////////////////////////////////////////////
// Function : Copy Constructor
/////////////////////////////////////////////////////
template<typename Type>
HTable<Type>::HTable(const HTable<Type>& copy)
{
	//Set data members to null.
	arr = nullptr;

	*this = copy;
}

/////////////////////////////////////////////////////
// Function : insert
// Parameters : v - the item to insert into the hash table
/////////////////////////////////////////////////////
template<typename Type>
void HTable<Type>::insert(const Type& v)
{
	int temp = hFunc(v); // Catching with a temporary variable. 

	arr[temp].addHead(v); // Adding a head to our array's index from the temporary variable. 
}

/////////////////////////////////////////////////////
// Function : findAndRemove
// Paramters : v - the item to remove(if it is found)
/////////////////////////////////////////////////////
template<typename Type>
bool HTable<Type>::findAndRemove(const Type& v)
{
	int temp = find(v); //Catch value with a temporary varaible. 

	if(temp == -1)
		return false; //Return false if it's a bad find.

	SLLIter<Type> iter(arr[temp]); //Creating an iterator.
	iter.begin(); //Call begin on the iterator

	while( !iter.end())
	{
		if(v == iter.current()) //If v is equal to the current index.
		{
			arr[temp].remove(iter); //Remove at the index.
			return true; //return true
		}
		else
		{
			++iter; //Else, increment the iterator.
		}
	}
	return false; //Return false to be on the safe side.
}

/////////////////////////////////////////////////////
// Function : clear
// Notes : clears the hash table
/////////////////////////////////////////////////////
template<typename Type>
void HTable<Type>::clear()
{
	for(unsigned int i = 0; i < numBuckets; i++)
	{
		arr[i].clear();
	}
}

/////////////////////////////////////////////////////
// Function : find
// Paramters : v - the item to look for
// Return : the bucket we found the item in or -1 if we
//          didn't find the item.
/////////////////////////////////////////////////////
template<typename Type>
int HTable<Type>::find(const Type& v) const
{
	int temp = hFunc(v); //Creating temporary integer to return from hash function's return.
	SLLIter<Type> iter(arr[temp]); //Setting up iterator object. 
	iter.begin();//Starting at the head.

	while( !iter.end()) 
	{
		if(v == iter.current()) //If v is equal to the current index.
			return temp; //Return our temporary integer. 
		else
			++iter; //Increment the iterator. 
	}

	return -1; //Return this if it fails. 
}

#endif