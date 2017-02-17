#ifndef COMPUTER_H
#define COMPUTER_H

//Make sure the child class knows who the parent is 
#include "Player.h" 

//Now publicly derive the class 
class CComputer : public CPlayer 
{
private:
	//Now we create a fixed size char array for computer name
	char* m_szcomName;  //For now, it will be a char pointer, but might need to change back into char with index...
public:
	CComputer(void);
	~CComputer(void);

	//We create a modifier or accessor for the computer name data member
	void SetName(const char* szName);
	char GetName(void); 

	//Make a show function for the computer class 
	void Show(void); 
};

#endif