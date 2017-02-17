#ifndef HUMAN_H
#define HUMAN_H

//Include the Player.h so that the derived class knows what the Base class is 
#include "Player.h" 

//Now publicly derive the class
class CHuman : public CPlayer 
{
private:
	//New data member for the name (since it is no longer located in the parent class).
	char* m_szHumName; 
public:
	CHuman(void);
	~CHuman(void);

	//Will probably need to add an accessor and modifier for the new data member 
	const char* GetName(void) const; // This will return the name with all it's might!
	void SetName( const char* szName); //This will take in an address paramter of a character...if that's right. 

	void Ask(void); //Declare a quick Ask() method for asking the name.

	//Create a show function for this derived class
	void Show(void); 
};

#endif 