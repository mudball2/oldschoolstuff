#ifndef GAME_H
#define GAME_H

//#include "StdAfx.h"
#include "Sprite.h"
#include "Missle.h" //this for our missle. 
#include "Cell.h"

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	void Ask(void);
	
	virtual void Run();

protected:
	virtual void Refresh();
	virtual void Input();
	virtual void AI();

private:
	bool play;
	Sprite* zwei;
	vector<Sprite *>ene;
	int pX, pY;
	int eX, eY;
	time_t start;
	unsigned long long frame;
	bool showFPS;
	
	string song;//For FMOD songs

	//Missle stuff
	vector<Missle *>missles;
	vector<Missle *>eMissles; //enemy

	//Now, to create a missle.
	Missle * missle; 
	Missle * eMissle; //enemy
	
	Missle::Delta mX, mY; //Player's global missle variables.
	Missle::Delta missleX, missleY; //enemy


	//For a little bit of ingame data 
	int score; 
	int health, x; //Health and random song.
	int count; //Will count the amount of bad dudes on screen. 
	int savedSecs;
	string playerName;

	//The Cell allocation.
	vector<Cell<>> cell;
	int oX, oY;

	Game(Game const &);
	Game & operator =(Game const &);
};

#endif