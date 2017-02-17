#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std; 

class CCard
{
private: 
	char m_szCardSuit; //3-6, These are the numeric values for the characters that make card suits. 
	int m_nCardValue; //2-14, 14 being an ace. 
public:
	CCard(void);

	//Create the the accessors, they will return values based on what the mutator takes in.  
	char GetSuit();
	int GetFace(); //Will probably just stick with showing them in the show function as needed. 
	int GetValue(); 
	
	//Create the mutators, they will mess with the data members (take in arguements) and return their values. 
	void SetSuit( char szCardSuit ); 
	void SetFace( int nCardVal ); 

	//Now create a show function to show the card. 
	//This will simply show the card result 
	void Show(void) const;  //Has a const keyword, because nothing really changes in this method. 

	//Now set all six of the relational operators using operator overloading. (<,>,<=,>=,==,!=)
#define REL_OPERATORS(op)\
	bool operator op (const CCard& rhs) const\
	{\
	return ( this->m_nCardValue op rhs.m_nCardValue) ? true : false;\
	}

	REL_OPERATORS(>)
	REL_OPERATORS(<)
	REL_OPERATORS(<=)
	REL_OPERATORS(>=)
	REL_OPERATORS(==)
	REL_OPERATORS(!=)

	//Now that all of the relational operators are overloaded, just simply go about and create as a regular 
	//overloaded operator without having to #define all of it, because these next two don't necessarily do 
	//the same thing. 

	//Now prototype the overloaded insertion operator 
	friend ostream& operator<<( ostream& os, const CCard& rhs); //This is going to be friend function so that we may 
																//access the ouput stream's private data members 
	//Now prototype the overloaded addition operator 
	CCard& operator+( const CCard& rhs); //This may not even be entirely necessary for this game but we have it 
										// on here anyway because the directions said so. (Maybe favors BlackJack?) 

	~CCard(void);
};

#endif 