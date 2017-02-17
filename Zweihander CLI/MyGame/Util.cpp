#include "stdafx.h"
#include "Util.h"

void Util::Pause()
{
	System::Console::SetCursorPosition((Console::WindowWidth - 31) >> 1,
		Console::WindowHeight - 1);
	system("pause");
}

void Util::EOLWrap(bool on)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(out, &mode);
	if (on)
		mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	else
		mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(out, mode);
}

void Util::FlushKeys()
{
	for (int i = 0; i < 256; ++i) GetAsyncKeyState(i);
	while (Console::KeyAvailable) Console::ReadKey(true);
}

