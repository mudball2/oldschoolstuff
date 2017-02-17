#include "StdAfx.h"
#include "Image2D.h"


Image2D::Image2D(ConsoleColor fore, ConsoleColor bore, string txt) : graphicText(txt) //No longer need assignments in .cpp! 
{
	this->fg = fore;
	this->bg = bore;

	this->width = 0;
	this->height = 0; 

	CalculateWidthAndHeight();
}

//Modifiers for all but the width and height 
void Image2D::SetFG( ConsoleColor tempFG )
{
	fg = tempFG; 
}
void Image2D::SetBG( ConsoleColor tempBG )
{
	bg = tempBG;
}

void Image2D::SetgraphicText( char* tempText )
{
	graphicText = tempText; 
}

//Call this when you create a new image or copy a new image. 
void Image2D::CalculateWidthAndHeight(void)
{
	for(int i = 0; i < static_cast<int>(strlen(this->graphicText.c_str())); i++)
	{
		if( graphicText[i] == '\n')
			height++;
		else if (graphicText[i] != '\n')
			width++;
	}

	height = height+1;
	width = width/height;
}

//Now some stuff for our Trilogy. 
#if 0
//First the copy constructor 
Image2D::Image2D( Image2D const &img)
{
	//Deep copy and stuff goes here...
	graphicText = _strdup(img.graphicText); //strdup basically does all the fancy multi-line stuff for us.
}

//Next, do the operator overloader
Image2D& Image2D::operator=(Image2D const &rhs)
{
	//Stuff goes here. 

	//First and foremost, we do a paranoid check
	if ( this != &rhs )
	{
		delete [] graphicText;
		graphicText = _strdup(rhs.graphicText); 
	}

	return *this;
}
#endif

const char* Image2D::GetgraphicText(void) const 
{ 
	return graphicText.c_str(); 
}

//Show function 
void Image2D::Show(void) const 
{
	System::Console::ForegroundColor = fg; 
	System::Console::BackgroundColor = bg;
	cout << graphicText; 
	System::Console::ResetColor(); 
}

Image2D::~Image2D(void)
{
	//Keeping an empty destructor. 
}
