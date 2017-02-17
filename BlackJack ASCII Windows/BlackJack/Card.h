#ifndef CARD_H
#define CARD_H

class CCard
{
	//Add data members for the card class 
private:
	char m_szSuits;
	//enum FACES { J=11, Q=12, K=13, A=14}; 
	int m_nCardValue;
public:
	CCard(void);

	//Accessors
	char GetSuit(void);
	int GetFace(void); 
	int GetValue(void);
	
	//Mutators
	void SetSuit(int numNeeded);
	void SetFace(int facesNeeded);

	//Destructor
	~CCard(void);

	//The Show method for card.h
	void Show(void); 
};

#endif