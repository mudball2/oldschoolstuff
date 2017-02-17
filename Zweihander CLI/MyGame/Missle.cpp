#include "StdAfx.h"
#include "Missle.h"


Missle::Missle(char *name, int left, int top,
	ConsoleColor fg, ConsoleColor bg, char* text, Delta misslex, Delta missley) 
	: Sprite(name, left, top, fg, bg, text), missle(2)
{
	missle[0] = misslex;
	missle[1] = missley;
}

void Missle::GetDelta(Delta &dX, Delta &dY)
{
	dX = missle[0];
	dY = missle[1];
}


void Missle::SetDelta(Delta &dX, Delta &dY)
{
	missle[0] = dX;
	missle[1] = dY;
}

Missle::~Missle(void)
{
}
