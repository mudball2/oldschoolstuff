#pragma once

namespace System
{

// Day #1
enum ConsoleColor
{
	Black		= 0,
	DarkBlue	= FOREGROUND_BLUE,
	DarkGreen	= FOREGROUND_GREEN,
	DarkCyan	= FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkRed		= FOREGROUND_RED,
	DarkMagenta	= FOREGROUND_RED | FOREGROUND_BLUE,
	DarkYellow	= FOREGROUND_RED | FOREGROUND_GREEN,
	Gray		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkGray	= FOREGROUND_INTENSITY,
	Blue		= FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Green		= FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Cyan		= FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Red			= FOREGROUND_RED | FOREGROUND_INTENSITY,
	Magenta		= FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Yellow		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	White		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

class Console
{
	// Day #1
	static HANDLE out;
	static WORD defColors;
	// Day #2
	static HWND hwnd;

public:
	// Day #1
	static WORD ForegroundColor();
	static void ForegroundColor(WORD color);
	static WORD BackgroundColor();
	static void BackgroundColor(WORD attr);
	static void ResetColor();

	// Day #2
	static int WindowWidth();
	static int WindowHeight();
	static void SetWindowSize(int columns, int rows);
	static void SetBufferSize(int columns, int rows);
	static int CursorLeft();
	static int CursorTop();
	static void SetCursorPosition(int left, int top);
	static void Clear();
	static void CursorVisible(bool visible);
	static void Lock(bool lock);
//	Threading::Thread::Sleep()	Sleep()

	// Day #4
//	Environment::TickCount		GetTickCount()

	// Day #5
	static void Write(wchar_t wc);

	// Day #8
//	Media::SystemSounds			PlaySound((LPCTSTR)SND_ALIAS_SYSTEMSTART, NULL, SND_ALIAS_ID);
	static bool MousePos(int &x, int &y);

	// Day #9
//	Media::SoundPlayer			PlaySound(L"c:\\sounds\\tada.wav", NULL, SND_FILENAME | SND_ASYNC);

	// Day #?
	static void Title(wchar_t const * const title);
//	FlushKeys()?
};

}
