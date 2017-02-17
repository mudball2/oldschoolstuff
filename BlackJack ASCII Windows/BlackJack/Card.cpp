#include "Card.h"
#include <iostream>
using namespace std; 

#include <Color.h>
using namespace FS;

#include<ctime>
	

CCard::CCard(void)
{
 
	
}

//Accessors
char CCard::GetSuit(void)
{
	//Must return a value for the suit
	return m_szSuits;
}

int CCard::GetFace(void)
{
	//Must return a value for the face
	return m_nCardValue;
}

int CCard::GetValue(void)
{
	if(m_nCardValue == 14)
	{
		
		return 11;
	
	} else if (m_nCardValue == 13 || m_nCardValue == 12 || m_nCardValue == 11){
		
		return 10;
	
	} else {
	
		return m_nCardValue;
	
	}
}
	
//Mutators
void CCard::SetSuit(int numNeeded)
{
	//Add more stuff here
	m_szSuits = numNeeded;
}

void CCard::SetFace(int facesNeeded)
{
	
	m_nCardValue = facesNeeded; 
	
}

CCard::~CCard(void)
{
	//Nothing to deallocate yet...
}

void CCard::Show(void)
{
	//char newValue;
	//Must return the total value of the card
	if (m_nCardValue == 11){
		cout << "J" << GetSuit();
	} else if (m_nCardValue == 12){ 
		cout << "Q" << GetSuit();
	} else if (m_nCardValue == 13){
		cout << "K" << GetSuit(); 
	} else if (m_nCardValue == 14) {
		cout << "A" << GetSuit(); 
	} else {
	//Display the card result
	cout << FS::BG_Gray << GetFace() << GetSuit();
	}
}