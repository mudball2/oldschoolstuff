
#include "Player.h"

//Have iostream ready for the name and such 
#include <iostream>
using namespace std; 

#include "Color.h"
using namespace FS;

class CHuman : public CPlayer
{
private:
	int m_nPlayerScore;
	char* m_szPlayerName;

public:
	//Default Constructor for this child
	CHuman(void);

	//Destructor
	~CHuman(void);

	//A copy constructor to help handle the dynamic memory 
	CHuman( const CHuman& copy );

	//Mutator for dynamic name
	void SetName( const char* szPlayerName ); 

	//Accessor for the dynamic name
	const char* GetName( void ) const; 

	//Create an Ask() function for the player's name 
	void Ask(void); 

	//This is the Show function from the Player.h
	void Show(void);
};

