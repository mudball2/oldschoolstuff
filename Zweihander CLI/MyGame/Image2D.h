//#pragma once //Replacing header protection for my sanity 
#ifndef IMAGE2D_H
#define IMAGE2D_H


#include "stdafx.h" // Including this header file for the console colors 

class Image2D
{
	//(Automatically Private section) I will put the data memebers here...
	ConsoleColor fg, bg; 
	string graphicText; //has-a
	unsigned short width, height; //For the text/spaceship
public:
	Image2D(ConsoleColor fore = ConsoleColor::White, ConsoleColor bore = ConsoleColor::Black, 
		string txt = "YO!"); //Default constructor 
										//prototype 

	//Inlined accessors for all the data members in this class..
	ConsoleColor GetFG(void) const { return fg; } //Putting the const keyword to protect the data members 
	ConsoleColor GetBG(void) const { return bg; }

	const char* GetgraphicText(void) const;

	unsigned short GetWidth(void) const { return width; }
	unsigned short GetHeight(void) const { return height; }

	//Modifiers for all but the width and height 
	void SetFG( ConsoleColor tempFG ); 
	void SetBG( ConsoleColor tempBG ); 

	void SetgraphicText( char* tempText );

	//this is for calculating width and height 
	void CalculateWidthAndHeight(void); 

	//Now some stuff for our Trilogy. 

#if 0
	//First the copy constructor 
	Image2D( Image2D const &img); 

	//Next, do the operator overloader
	Image2D& operator=(Image2D const &rhs); 
#elif 1
	//Finally, a Show() funtion 
	void Show(void) const; //Protect the invoking object 
#endif
	virtual ~Image2D(void); //It is virtual just in case it needs it...for now (It's also part of out Trilogy, so it good!! :D)
};

#endif