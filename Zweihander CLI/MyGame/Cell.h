#ifndef CELL_H
#define CELL_H

//Defining our custom types
//#define Offset unsigned char
//#define Symbol wchar_t //This is a wide character data type. 

template<typename Offset = signed char, typename Symbol = wchar_t>
struct Cell //A struct, so that everything is already public. 
{
	Offset oX, oY;
	ConsoleColor fg, bg;
	Symbol sym;

	Cell() { }
	Cell(Offset oX, Offset oY, ConsoleColor fg, ConsoleColor bg, Symbol sym);

	bool Show(int left, int top) const;
	
	Offset & operator[](int index);

	Offset const & operator[]( int index) const;
};


template<typename Offset, typename Symbol>
Cell<Offset, Symbol>::Cell(Offset oX, Offset oY, ConsoleColor fg, ConsoleColor bg, Symbol sym)
{
	this->oX = oX;
	this->oY = oY;

	this->fg = fg;
	this->bg = bg;

	this->sym = sym; 
}

template<typename Offset, typename Symbol>
bool Cell<Offset, Symbol>::Show( int left, int top) const
{
		if(left + oX > 0 && top + oY > 0 &&
			left + oX < Console::WindowWidth &&
			top + oY <= Console::WindowHeight)
	{		
		Console::SetCursorPosition(left + oX, top + oY);
		Console::ForegroundColor = fg;
		Console::BackgroundColor = bg;
		Console::Write(sym); //displays better unicode than wcout.
		Console::ResetColor();
		return true;
	} else {
		
		return false;
	}
}

template<typename Offset, typename Symbol>
Offset & Cell<Offset, Symbol>::operator[](int index)
{
	if(index == 0)
		return oX;
	else if(index == 1)
		return oY;
	else
	{
		cerr << "Not a valid index, bro.";
		exit(1);
	}
}

template<typename Offset, typename Symbol>
Offset const & Cell<Offset, Symbol>::operator[]( int index) const
{
	if(index == 0)
		return oX;
	else if(index == 1)
		return oY;
	else
	{
		clog << "Not a valid index, dude.";
		exit(1);
	}
}

#endif