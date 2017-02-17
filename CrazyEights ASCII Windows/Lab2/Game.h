#include <iostream>
using namespace std;

// Enum of gamestates, you can add and remove from this if you need additional ones (examples include: GAME_TITLE, GAME_MENU, GAME_OPTIONS, etc).
enum GAMESTATE { GAME_INIT, GAME_TITLE, GAME_PLAY, GAME_END, };

class Game
{
	// GAMESTATE object to store the game's current state.
	GAMESTATE m_state;

public:
	Game();

	// The main function of the game, this loops until a certain gamestate is set.
	void Run();

	// Modifier for the gamestate data member.
	inline void SetState(GAMESTATE _state) { m_state = _state; }
};