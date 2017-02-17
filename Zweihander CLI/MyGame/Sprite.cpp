#include "StdAfx.h"
#include "Sprite.h"


Sprite::Sprite(string name, int left, int top, ConsoleColor fg, 
	ConsoleColor bg, string text) : Image2D(fg, bg, text) /*, name(name)*/
{

	//Going to set up the data members' values right at this spot 
	this->name = name;
	//The we set up the int values of left and top to 0
	this->left = left;
	this->top = top; 
}

void Sprite::SetLeft( int l )
{
	//Will set left to whatever I want! :D
	left = l; 
}

void Sprite::SetTop( int t )
{
	//Set the Top
	top = t;
}

void Sprite::SetName(const char* n)
{
	name = n; 
}


const char* Sprite::GetName(void) const 
{
	return name.c_str(); 
} 

#if 0
Sprite::Sprite( Sprite const &spr) : Image2D(spr) //Calling the parent's copy constructor here. 
{
	//This is the main copy of focus
	//char* temp;
	//this->name = memcpy(name, temp, strlen(temp)+1);
	//^Forget variety, I'm sticking with the _strdup

	this->name = _strdup(spr.name); //This will take care of most of things for us. 

	//These are the shallow copies 
	this->top = spr.top; 
	this->left = spr.left;
}

Sprite& Sprite::operator=(Sprite const &rhs) //Can't use member initializer here, so put necessary code in definintion
{
	//First do the paranoid check before anything else 
	if ( this != &rhs )
	{
		//Put the necessary code here. 
		Image2D::operator=(rhs); //Calling the parent's assignment operator 
		delete[] name; 
		this->name = _strdup(rhs.name); 

		//Regular shallow copies. 
		this->top = rhs.top;
		this->left = rhs.left; 
	}
	return *this; 
}

#endif
 
bool Sprite::Collides(int x, int y, unsigned short w,
       unsigned short h) const
{
	 if((x <= left + GetWidth() - 1) && (x + w - 1 >= left)
		&& (y <= top + GetHeight() - 1) && (y + h -1 >= top))
		{
			return true;
		}else{
			return false;
		}
}


bool Sprite::OutOfBounds(int x, int y) const
{
	if(x < 0 || y < 0 ||
			x > Console::WindowWidth - this->GetWidth()  ||
			y >= Console::WindowHeight - this->GetHeight())
	{
		return true;

	} else {
		return false;
	}

	return false;
}

void Sprite::Show() const
{
	//Image2D::Show(); 
	//System::Console::ResetColor(); 
	System::Console::ForegroundColor = Image2D::GetFG();
	System::Console::BackgroundColor = Image2D::GetBG();
	const char * const text = Image2D::GetgraphicText();
	int size = 0;
	for(int i = 0; text[i] != '\0'; i++, size++);
	Console::SetCursorPosition(left, top); 
	int tempTop = top;
	for(int i = 0; i < size; i++) 
	{
		if(text[i] == '\n')
		{
			Console::SetCursorPosition(left, ++tempTop);
			continue; //Like a break, excepts loops back. (More like Return keyword). 
		}
		cout << text[i];
	}
	System::Console::ResetColor(); 
}

Sprite::~Sprite(void)
{
	//Deallocate the memory here...
	//There is no longer anything to deallocate since we're using the string class. 
}
