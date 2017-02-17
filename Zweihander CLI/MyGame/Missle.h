#ifndef MISSLE_H
#define MISSLE_H

#include "sprite.h"
class Missle : public Sprite
{
public:
	typedef signed char Delta; //Added to public section, as noted. 
	
private:
	valarray<Delta> missle;
public:
	Missle(char *name = "Gabe", int left = 0, int top = 0,
	ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black, 
	char* text = "[0]", Delta misslex = 0, Delta missley = 0);

	//Accessor
	void GetDelta(Delta &dX, Delta &dY);

	//Modifier
	void SetDelta(Delta &dX, Delta &dY);

	~Missle(void);
};

#endif
