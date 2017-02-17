#include <iostream>
using namespace std; 

#include <ctime> 

#include "Player.h"

class CComputer : public CPlayer
{
private:
	int m_nComputerScore;
	//char* m_szComputerName[5];

public:
	//Default constructor for this child
	CComputer(void);

	//Destructor
	~CComputer(void);


	//This is the Show function for the parent
	void Show(void); 
};

