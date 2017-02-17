#ifndef SPRITE_H
#define SPRITE_H

#include "image2d.h"
class Sprite : public Image2D //is-a
{
private:
	int left, top; 
	string name; //has-a
public:
	Sprite(string name = "Gabe", int left = 0, int top = 0, ConsoleColor fg = ConsoleColor::White, 
		ConsoleColor bg = ConsoleColor::Black, string text = "[0]");

	//Writing the accessors for the data members
	const int GetLeft(void) const { return left; }
	const int GetTop(void) const { return top; }
	const char* GetName(void) const;

	//Now to write the prototypes for the modifiers for the data members 
	void SetLeft( int l ); 
	void SetTop( int t ); 
	void SetName(const char* n);	

	//Set the trilogy stuff here...
#if 0
	//First the copy constructor 
	Sprite( Sprite const &spr); 

	//Next, do the operator overloader
	Sprite& operator=(Sprite const &rhs); 
#endif
	//Adding the extra methods that this class is pretty much intended for... 
	bool OutOfBounds( int x, int y) const; 
	bool Collides( int x, int y, unsigned short w, unsigned short h ) const; 

	//Making us a virtual Show() function 
	void Show(void) const; //Using const to protect the invoking object. 

	virtual ~Sprite(void);
};

#endif