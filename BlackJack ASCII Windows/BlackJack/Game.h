#include <iostream>
using namespace std;

// Enum of gamestates, you can add and remove from this if you need additional ones (examples include: GAME_TITLE, GAME_MENU, GAME_OPTIONS, etc).
enum GAMESTATE { GAME_INIT, GAME_TITLE, GAME_PLAY, GAME_END, };

class Game
{
	// GAMESTATE object to store the game's current state.
	GAMESTATE m_state;
	
	
	int playerVal; //Receives value of the card
	int playerVal2; 
	int playerVal3; 
	int playerVal4;
	int totPlayerVal; 

	//Receives value for the dealer
	int dealerVal;
	int dealerVal2;
	int dealerVal3;
	int dealerVal4;
	int totDealerVal; 

	int dealerMoney; //Money for the dealer
	int playerMoney; //Money for the player
	
	int betTotal; //The "pot" 

	bool insured; // for insurance
public:


	Game();

	// The main function of the game, this loops until a certain gamestate is set.
	void Run();

	// Modifier for the gamestate data member.
	inline void SetState(GAMESTATE _state) { m_state = _state; }
};