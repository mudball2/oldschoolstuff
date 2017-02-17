#include "StdAfx.h"
#include "Console.h"

namespace System
{

HANDLE Console::out = GetStdHandle(STD_OUTPUT_HANDLE);
WORD Console::defColors = Console::BackgroundColor() << 4 | Console::ForegroundColor();
HWND Console::hwnd = GetConsoleWindow();

void Console::Title(wchar_t const * const title)
{
	SetConsoleTitle(title);
}

WORD Console::ForegroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.wAttributes & 0x0F;
}

void Console::ForegroundColor(WORD attr)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleTextAttribute(out, info.wAttributes & 0xF0 | attr);
}

WORD Console::BackgroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return (info.wAttributes & 0xF0) >> 4;
}

void Console::BackgroundColor(WORD attr)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleTextAttribute(out, info.wAttributes & 0x0F | attr << 4);
}

void Console::ResetColor()
{
	SetConsoleTextAttribute(out, defColors);
}

int Console::WindowWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.X;
}

int Console::WindowHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.Y;
}

void Console::SetWindowSize(int columns, int rows)
{
	COORD c = GetLargestConsoleWindowSize(out);
	if (columns < 1 || columns > c.X)
		columns = c.X;
	if (rows < 1 || rows > c.Y)
		rows = c.Y;

	SMALL_RECT dim = { 0, 0, columns - 1, rows - 1 };
	SetConsoleWindowInfo(out, TRUE, &dim);
}

void Console::SetBufferSize(int columns, int rows)
{
	COORD c = { columns, rows };
	SetConsoleScreenBufferSize(out, c);
}

void Console::CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO curs;
	GetConsoleCursorInfo(out, &curs);
	if (curs.bVisible == TRUE && visible || curs.bVisible == FALSE && !visible)
		return;
	curs.bVisible = (visible) ? TRUE : FALSE;
	SetConsoleCursorInfo(out, &curs);
}

void Console::Clear()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);

	DWORD len = info.dwSize.X, num;
	COORD c = { 0, 0, };
	for (int i = 0; i < info.dwSize.Y; ++i)
	{
		c.Y = i;
		FillConsoleOutputAttribute(out, info.wAttributes, len, c, &num);
		FillConsoleOutputCharacter(out, ' ', len, c, &num);
	}

	SetCursorPosition(0, 0);
}

int Console::CursorLeft()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.X;
}

int Console::CursorTop()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.Y;
}

void Console::SetCursorPosition( int left, int top )
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);

	left = max(left, 0);
	left = min(left, info.dwSize.X - 1);
	top = max(top, 0);
	top = min(top, info.dwSize.Y - 1);

	COORD cp = { left, top, };
	SetConsoleCursorPosition(out, cp);
}

void Console::Write(wchar_t wc)
{
	DWORD dummy;
	WriteConsole(out, &wc, 1, &dummy, NULL);
}

bool Console::MousePos(int &x, int &y)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);

	RECT c;
	GetClientRect(hwnd, &c);
	int width = c.right, height = c.bottom;

	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height)
	{
		x = y = -1;
		return false;
	}

	x = static_cast<int>(p.x / static_cast<double>(width)  * WindowWidth());
	y = static_cast<int>(p.y / static_cast<double>(height) * WindowHeight());
	return true;
}

void Console::Lock(bool lock)
{
	LockWindowUpdate(lock ? hwnd : nullptr);
}

}